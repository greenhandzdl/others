# fillArea.py
"""
PolyFill: 多边形栅格填充（ET/AET 实现）
- 支持浮点顶点坐标
- 基于扫描线，构造 Edge Table (ET) 和 Active Edge Table (AET)
- 提供交互式用户输入接口、返回栅格 (numpy array) 与 matplotlib 可视化
"""

from typing import List, Tuple, Optional
import math

try:
    import numpy as np
except Exception:
    np = None  # numpy 可选，但强烈建议安装

try:
    import matplotlib.pyplot as plt
except Exception:
    plt = None

class Edge:
    __slots__ = ("ymax", "x", "inv_slope")
    def __init__(self, ymax: int, x: float, inv_slope: float):
        self.ymax = ymax  # scanline index where edge is no longer active (exclusive)
        self.x = x        # current x intersection with current scanline
        self.inv_slope = inv_slope  # dx/dy

    def __repr__(self):
        return f"Edge(ymax={self.ymax}, x={self.x:.3f}, inv_slope={self.inv_slope:.3f})"


class PolyFill:
    def __init__(self, vertices: Optional[List[Tuple[float, float]]] = None,
                 width: int = 80, height: int = 60):
        """
        vertices: list of (x, y) tuples. Coordinates in the same unit as scanlines.
                  By default y increases downwards (screen coordinates). If你想
                  使用数学坐标系（y 向上），在输入时转换或在可视化时翻转。
        width, height: raster grid size (pixels)
        """
        self.vertices = vertices or []
        self.width = width
        self.height = height

    def get_user_input(self):
        """
        交互式读取用户顶点和栅格大小（命令行）。
        顶点输入格式：依次输入顶点个数，然后每行输入 "x y"（支持浮点）。
        """
        n = int(input("请输入多边形顶点数量 (n >= 3): ").strip())
        verts = []
        print("请按顺序输入每个顶点的 x y（以空格分隔，可以是浮点数）:")
        for i in range(n):
            while True:
                raw = input(f"顶点 {i} (x y): ").strip()
                parts = raw.split()
                if len(parts) >= 2:
                    try:
                        x = float(parts[0])
                        y = float(parts[1])
                        verts.append((x, y))
                        break
                    except ValueError:
                        print("坐标格式不正确，请重新输入")
                else:
                    print("请输入两个数字，用空格分隔")
        self.vertices = verts
        w = input(f"栅格宽度 (默认 {self.width}): ").strip()
        h = input(f"栅格高度 (默认 {self.height}): ").strip()
        if w:
            self.width = int(w)
        if h:
            self.height = int(h)
        print(f"已读取顶点: {self.vertices}")
        print(f"栅格大小: {self.width} x {self.height}")

    def _build_et(self):
        """
        构造 Edge Table (ET).
        返回 (ET dict, y_min_scan, y_max_scan)
        ET: dict[int_scanline_y] -> list[Edge]
        扫描线以整数 y 为单位。对输入的浮点 y：
         - ymin_scan = ceil(ymin)
         - ymax_scan = ceil(ymax)  (edge 不在 scanline == ymax_scan 时活动)
         - 初始 x = x_at_ymin + (ymin_scan - ymin) * inv_slope
        水平边（y1 == y2）被忽略。
        """
        if not self.vertices or len(self.vertices) < 3:
            raise ValueError("顶点数量不足以构成多边形")

        verts = self.vertices
        n = len(verts)
        edges_raw = []

        min_y = float("inf")
        max_y = float("-inf")
        for (x1, y1), (x2, y2) in zip(verts, verts[1:] + verts[:1]):
            if y1 == y2:
                # 忽略水平边（常规做法）
                continue
            # normalize so ymin < ymax
            if y1 < y2:
                ymin_f, ymax_f = y1, y2
                x_at_ymin = x1
                dx = x2 - x1
                dy = y2 - y1
            else:
                ymin_f, ymax_f = y2, y1
                x_at_ymin = x2
                dx = x1 - x2
                dy = y1 - y2

            inv_slope = dx / dy  # dx/dy
            edges_raw.append((ymin_f, ymax_f, x_at_ymin, inv_slope))
            min_y = min(min_y, ymin_f)
            max_y = max(max_y, ymax_f)

        if not edges_raw:
            raise ValueError("没有非水平边，无法填充")

        # integer scanline bounds
        y_min_scan = math.ceil(min_y)
        y_max_scan = math.ceil(max_y)

        ET = {}  # map scanline -> list of Edge
        for ymin_f, ymax_f, x_at_ymin, inv_slope in edges_raw:
            ymin_scan = math.ceil(ymin_f)
            ymax_scan = math.ceil(ymax_f)  # exclusive
            # initial x at scanline ymin_scan
            x_init = x_at_ymin + (ymin_scan - ymin_f) * inv_slope
            e = Edge(ymax=ymax_scan, x=x_init, inv_slope=inv_slope)
            ET.setdefault(ymin_scan, []).append(e)

        return ET, y_min_scan, y_max_scan

    def rasterize(self) -> List[List[int]]:
        """
        执行栅格化（扫描线填充），返回一个 height x width 的二维列表（0/1）。
        y = 0 对应网格的顶行（向下增加）。如果你的坐标系不同，需要在输入时转换。
        """
        grid = [[0 for _ in range(self.width)] for __ in range(self.height)]
        ET, y_min_scan, y_max_scan = self._build_et()

        AET: List[Edge] = []

        # clamp scanlines to raster bounds
        scan_start = max(0, y_min_scan)
        scan_end = min(self.height, y_max_scan)  # exclusive upper bound

        for y in range(scan_start, scan_end):
            # 1. 将 ET 中当前 scanline 的边加入 AET
            if y in ET:
                AET.extend(ET[y])

            # 2. 移除在此 scanline 不再活动的边（y >= ymax）
            AET = [e for e in AET if e.ymax > y]

            # 3. 按当前交点 x 排序
            AET.sort(key=lambda e: e.x)

            # 4. 两两配对填充
            i = 0