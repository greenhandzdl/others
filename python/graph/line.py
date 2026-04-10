def draw(x  ,y ):
	print(f"Plotting point at ({x}, {y})")


def lineDDA(x1, y1, x2, y2):
    dx, dy = x2 - x1, y2 - y1
    steps = max(abs(dx), abs(dy))
    if steps == 0:
        draw(x1, y1)
        return
    xInc, yInc = dx / steps, dy / steps
    x, y = x1, y1
    for _ in range(steps + 1):
        draw(round(x), round(y))
        x += xInc
        y += yInc


def lineBresenham(x1, y1, x2, y2):
    # 支持浮点输入：将端点四舍五入为整数
    x1, y1, x2, y2 = int(round(x1)), int(round(y1)), int(round(x2)), int(round(y2))
    
    # delta_x/delta_y: 目标线段在 x/y 方向上的绝对长度
    delta_x, delta_y = abs(x2 - x1), abs(y2 - y1)
    # step_x/step_y: x/y 方向的移动方向（+1 或 -1）
    step_x = 1 if x2 >= x1 else -1
    step_y = 1 if y2 >= y1 else -1
    # err: 当前的误差值（决策变量）
    err = delta_x - delta_y
    
    # 当前绘制点，从起点开始
    current_x, current_y = x1, y1
    
    while True:
        draw(current_x, current_y)
        # 到达终点则结束
        if current_x == x2 and current_y == y2:
            break
        # double_err 用于比较，避免浮点运算
        double_err = 2 * err
        # 如果满足条件，在 x 方向上移动一步并调整误差
        if double_err > -delta_y:
            err -= delta_y
            current_x += step_x
        # 如果满足条件，在 y 方向上移动一步并调整误差
        if double_err < delta_x:
            err += delta_x
            current_y += step_y

def _LineMiddle_Ass(x , y ,slope , y_intersection):
    return (y+0.5) - slope * (x) - y_intersection

def LineMiddle(x1, y1, x2, y2):
    pass

		
if __name__ == "__main__":
	lineDDA(0,0,10,10)