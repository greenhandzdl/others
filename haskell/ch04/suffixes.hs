-- file: ch04/suffixes.hs
-- as mode

suffixes :: [a] -> [[a]]
suffixes xs@(_:xs') = xs : suffixes xs'
suffixes [] = []