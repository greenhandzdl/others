cDrop :: [a] -> Int -> [a]


cDrop arr num = if (num <=0 ) || (null arr)
    then arr
    else cDrop (tail arr) (num - 1)