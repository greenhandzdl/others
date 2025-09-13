-- 文件:maximum.hs
import Data.Maybe (listToMaybe)


maximum' :: (Ord a) => [a] -> a
maximum' xs = case xs of
    [] -> error "maximum of empty list"
    [x] -> x
    (x:xs) | x > maxTail -> x
           | otherwise -> maxTail
           where maxTail = maximum' xs

maximum'' :: (Ord a) => [a] -> a
maximum'' xs = case listToMaybe xs of
    Nothing -> error "maximum of empty list"
    Just x  -> foldl max x xs

-- foldr 函数主要用于从[]到整体处理。

-- fold1:假设从第一个元素开始，然后从左到右处理列表，将每个元素与下一个元素进行操作，直到列表结束。
maximum''' :: (Ord a) => [a] -> a
maximum'''  = foldl1 max  