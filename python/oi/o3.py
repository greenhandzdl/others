import sys

lines = sys.stdin.read().splitlines()
it = iter(lines)

def getInput():
    try:
        return next(it).split()
    except StopIteration:
        return None

def StrListToIntList(arr):
    return [int(i) for i in arr]

def In():
    line = getInput()
    if line is None:
        return None
    return StrListToIntList(line)

class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)
    
    def update(self, idx, delta):
        while idx <= self.n:
            self.tree[idx] += delta
            idx += idx & (-idx)
    
    def query(self, idx):
        res = 0
        while idx > 0:
            res += self.tree[idx]
            idx -= idx & (-idx)
        return res
    
    def range_query(self, l, r):
        return self.query(r) - self.query(l - 1)

if __name__ == "__main__":
    arr = In()  
    length = arr[0]

    fenwick = FenwickTree(length)

    arr = In()
    while arr is not None:
        match arr[0]:
            case 0:
                # s t o y : (s,t)区间 o: 0偶数 1奇数 y: 统一加的数
                s, t, o, y = arr[1:]
                mod_val = 2 + o  # o=0时mod_val=2(偶数位置)，o=1时mod_val=3(奇数位置)
                

                start_pos = s - 1  
                end_pos = t - 1    
                
                pos = start_pos
                if pos % mod_val != 0:
                    pos += (mod_val - pos % mod_val)
                
                while pos <= end_pos:
                    fenwick.update(pos + 1, y)  
                    pos += mod_val
                    
            case 1:
                # s t : 查询 s t 区间和
                s, t = arr[1:]
                print(fenwick.range_query(s, t))
            case _:
                print("输入错误：未知的操作类型")
                exit(1)
        arr = In()