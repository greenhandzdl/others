-- 文件名: reverse.hs

reverse' :: [a] -> [a]
reverse'  = foldl (flip (:)) [] 