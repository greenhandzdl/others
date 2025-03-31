-- 文件: ch04/oddList.hs

-- oddList 函数过滤并返回一个仅包含奇数的整数列表
-- 参数:
--   - [Int]: 输入的整数列表
-- 返回值:
--   - [Int]: 仅包含奇数的整数列表
oddList :: [Int] -> [Int]

-- 当列表非空时，检查头部元素
-- 如果头部元素是奇数，则将其包含在结果列表中，并递归处理剩余列表
-- 如果头部元素不是奇数，则直接递归处理剩余列表
oddList (x:xs) | odd x     = x : oddList xs
               | otherwise = oddList xs

-- 当列表为空时，返回空列表
oddList []                 = []