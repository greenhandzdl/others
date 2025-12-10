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

if __name__ == "__main__":
    arr = In()
    n = arr[0]
    k = arr[1]

    data = In()
    
    min_diff = float('inf')

    for i in range(1, n - k): 
        j = n - k - i
        if j >= 1:  
            detected = data[:i] + data[n-j:]
            diff = max(detected) - min(detected)
            min_diff = min(min_diff, diff)
    
    print(min_diff)