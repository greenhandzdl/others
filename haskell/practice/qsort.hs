-- 文件名: qsort.hs

qsort :: (Ord a) => [a] -> [a]
qsort xs = case xs of
    [] -> []
    (x:xs) -> let smallerSorted = qsort [a | a <- xs, a <= x]
                  largerSorted = qsort [a | a <- xs, a > x]
                in smallerSorted ++ [x] ++ largerSorted