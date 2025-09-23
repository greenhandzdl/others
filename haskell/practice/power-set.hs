powerset :: [a] -> [[a]]  
powerset xs = filterM (\x -> [True, False]) xs 