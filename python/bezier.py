import numpy as np
from typing import List

def calc(arr: np.ndarray, t: float) -> List[np.ndarray]:
    pts = np.asarray(arr, dtype=float)
    if pts.ndim != 2:
        raise ValueError("arr must be a 2D array with shape (n, d)")
    n, d = pts.shape
    if n < 2:
        raise ValueError("arr must contain at least 2 control points")
    if not isinstance(t, (int, float)):
        raise TypeError("t must be a float in [0, 1]")
    if not (0.0 <= float(t) <= 1.0):
        raise ValueError("t must be within [0, 1]")

    stages: List[np.ndarray] = []
    current = pts.copy()
    count: int = n - 1

    while count > 0:
        stages.append(current.copy())
        next_pts = np.empty((current.shape[0] - 1, d), dtype=float)
        for i in range(current.shape[0] - 1):
            next_pts[i] = (1.0 - float(t)) * current[i] + float(t) * current[i + 1]
        current = next_pts
        count -= 1

    stages.append(current.copy())
    return stages

if __name__ == "__main__":
    pts = np.array([[0, 0], [5, 5], [10, 0]])
    ts = [0.0, 0.4, 0.8, 1.0]

    for t in ts:
        stages = calc(pts, t)
        print(f"t = {t}")
        for i, s in enumerate(stages):
            print(f" stage {i} (count={s.shape[0]}):")
            print(s)
        print(" final point:", stages[-1][0])
        print("-" * 40)