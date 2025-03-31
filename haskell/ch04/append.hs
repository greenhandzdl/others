append::[a] -> [a] -> [a]
append xs ys = foldr (:) ys xs
-- foldr op1_for_existed op2_for_null xs