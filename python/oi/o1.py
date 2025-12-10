import sys

lines = sys.stdin.read().splitlines()
it = iter(lines)

def getInput():
    try:
        return next(it).split()
    except StopIteration:

        return None

def StrToInt(arr):
    return [int(i) for i in arr]

def In():
    line = getInput()
    if line is None:
        return None
    return StrToInt(line)

if __name__ == "__main__":
    arr = In()  
    
    if arr is None or len(arr) < 2:
        print("输入错误：请提供两个正整数")
        exit(1)
    
    n, m = arr[0], arr[1] 
    

    Stu = list(range(1, n + 1))
    
    index = 0  
    while len(Stu) > 1:
        index = (index + m - 1) % len(Stu)
        Stu.pop(index)
    
    for ele in Stu:
        print(ele, end="")