-- 文件: ch04/myFoldl.hs

-- myFoldl 是一个自定义的左折叠函数
-- 它接受一个二元函数 f，一个初始值 z，和一个列表 xs
-- 并通过从左到右应用函数 f 到列表元素上，累积结果
--
-- 参数:
-- @f@ 是一个接受两个参数的函数，第一个参数是累积结果类型，第二个参数是列表元素类型
-- @z@ 是累积的初始值
-- @xs@ 是将被折叠的列表
-- 返回值是累积的最终结果，类型与初始值相同
myFoldl :: (a -> b -> a) -> a -> [b] -> a

-- myFoldl 的实现利用了 foldr 来实现左折叠的效果
-- 它通过定义一个 step 函数，以及一个初始的函数 id
-- 并将累积过程通过函数 g 传递下去
-- 最终应用到初始值 z 上
myFoldl f z xs = ( foldr (step) (id) (xs) ) z
    where
      -- step 函数是关键，它定义了如何将当前元素 x
      -- 和剩余列表的累积结果结合到一起
      -- 它接受当前列表元素 x，一个累积函数 g，和当前的累积结果 a
      -- 并返回一个新的累积结果
      step x g a = g (f a x)

-- foldr step zero xs