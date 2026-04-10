from enum import Enum


class CircleAlgo(Enum):
    MIDPOINT = 1
    BRESENHAM = 2


def draw_point(x, y):
    print(f"Plotting point at ({x}, {y})")


def _plot_symmetry(cx, cy, x, y):
    # 绘制八个对称点
    pts = [
        (cx + x, cy + y),
        (cx - x, cy + y),
        (cx + x, cy - y),
        (cx - x, cy - y),
        (cx + y, cy + x),
        (cx - y, cy + x),
        (cx + y, cy - x),
        (cx - y, cy - x),
    ]
    for px, py in pts:
        draw_point(px, py)


def circle_bresenham(radius, cx=0, cy=0):
    """
    Bresenham 算法画圆（适合整数坐标）
    画出整个圆，通过对称性只计算八分之一并绘制对称点。
    """
    x, y = 0, radius
    d = 3 - 2 * radius
    while x <= y:
        _plot_symmetry(cx, cy, x, y)
        if d < 0:
            d += 4 * x + 6
        else:
            d += 4 * (x - y) + 10
            y -= 1
        x += 1

def circle_bressenham_without_dp(radius, cx=0, cy=0):
	'''
	Bresenham 算法画圆（适合整数坐标）
    画出整个圆，通过对称性只计算八分之一并绘制对称点。
    这个没有使用d= 3 - 2 * radius的这个递推式，但是仍然依赖于上一步状态。
	'''
	x, y = 0, radius
	while x <= y:
		_plot_symmetry(cx, cy, x, y)
		fPointT = (x+1)**2 + (y)**2 - radius**2
		fPointS = (x+1)**2 + (y-1)**2 - radius**2
		d = fPointT + fPointS
		x,y = x+1, y+1 if d < 0 else y


def circle_midpoint(radius, cx=0, cy=0):
    """
    中点圆算法（midpoint circle algorithm）
    """
    x, y = 0, radius
    d = 1 - radius
    while x <= y:
        _plot_symmetry(cx, cy, x, y)
        if d < 0:
            d += 2 * x + 3
        else:
            d += 2 * (x - y) + 5
            y -= 1
        x += 1

def circle_midpoint_without_dp(radius, cx=0, cy=0):
    x, y = 0, radius
    while x <= y:
        _plot_symmetry(cx, cy, x, y)
        fPoint = (x+1)**2 + (y-0.5)**2 - radius**2
        x,y = x+1, y+1 if fPoint < 0 else y

def draw_circle(radius, method=CircleAlgo.BRESENHAM, cx=0, cy=0):
    """
    根据枚举选择算法画圆
    """
    if method == CircleAlgo.BRESENHAM:
        circle_bresenham(radius, cx, cy)
    elif method == CircleAlgo.MIDPOINT:
        circle_midpoint(radius, cx, cy)
    else:
        raise ValueError("Unsupported circle drawing method")
