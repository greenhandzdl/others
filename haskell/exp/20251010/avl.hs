{-# LANGUAGE GADTs #-}
{-# LANGUAGE StandaloneDeriving #-}
{-# LANGUAGE FlexibleInstances #-}

-- AVL 树
-- printf "5
-- 88 70 61 96 120
-- " | runhaskell avl.hs

import Control.Monad (foldM)

-- | AVL 树的定义
-- Empty 表示空树；Node 使用记录语法保存左右子树、节点值和节点缓存的高度（nodeHeight）
-- | AVL 树定义（使用 GADT 在 Node 上要求元素类型为 Ord）
-- 注意：这会让对 Node 的模式匹配处可用 Ord a 约束
data AVLTree a where
    Empty :: AVLTree a
    Node  :: Ord a => { left       :: AVLTree a
                       , val        :: a
                       , right      :: AVLTree a
                       , nodeHeight :: Int
                       } -> AVLTree a

-- standalone deriving for GADT with constrained constructors
deriving instance Eq a => Eq (AVLTree a)

-- | 简洁的 Show 实现：将树按中序转换为列表并单行显示，形如 "AVL[...values...]"
toList :: Ord a => AVLTree a -> [a]
toList Empty = []
toList (Node l x r _) = toList l ++ [x] ++ toList r

instance (Show a, Ord a) => Show (AVLTree a) where
    show t = "AVL" ++ show (toList t)

-- | height: 读取节点保存的高度；空树高度为 0
height :: AVLTree a -> Int
height t = case t of
    Empty                -> 0
    Node _ _ _ nodeHeight -> nodeHeight

mkTree :: Ord a => a -> AVLTree a
mkTree x = Node Empty x Empty 1

-- | mkNode: 根据左右子树构造一个节点，并且自动计算并保存节点高度
-- 保证在构造新节点时高度是正确的，便于平衡计算
mkNode :: Ord a => AVLTree a -> a -> AVLTree a -> AVLTree a
mkNode l x r = Node l x r h
    where
        h = 1 + max (height l) (height r)

-- | printTree: 外部使用的打印接口，按层次输出树结构（使用制表符缩进）
printTree :: (Show a, Ord a) => AVLTree a -> String
printTree t = printTree' 0 t

-- | printTree': 内部递归打印函数。
-- 参数 d 表示当前缩进深度（每层缩进一个 '\t'），输出每个节点的高度和值，
-- 并分别展示左/右子树（用 L: 和 R: 标识）。空子树用 "." 表示。
printTree' :: (Show a, Ord a) => Int -> AVLTree a -> String
printTree' d Empty = replicate d '\t' ++ "."
printTree' d (Node l x r h) =
    let indent = replicate d '\t'
        childIndent = replicate (d + 1) '\t'
        leftStr = case l of
                    Empty -> childIndent ++ "L: ."
                    _     -> childIndent ++ "L:\n" ++ printTree' (d + 1) l
        rightStr = case r of
                    Empty -> childIndent ++ "R: ."
                    _     -> childIndent ++ "R:\n" ++ printTree' (d + 1) r
    in indent ++ "[H:" ++ show h ++ "] " ++ show x ++ "\n"
       ++ leftStr ++ "\n"
       ++ rightStr

printNode :: (Show a, Ord a) => AVLTree a -> String
printNode Empty = "."
printNode (Node _ x _ _) = show x

-- | 右旋：对以 y 为根，左子树为 x 的子树做单次右旋
--   结构：      y                x
--             / \     ->      /   \
--            x   C            A     y
--           / \                      / \
--          A   B                    B   C
-- | rotateRight: 单次右旋操作。
-- 对形如 (y (x A B) C) 的子树进行右旋，返回新的子树根 x（并修正高度）
rotateRight :: Ord a => AVLTree a -> AVLTree a
rotateRight (Node (Node a x b _) y c _) =
    -- 先重建子节点，确保高度正确
    mkNode a x (mkNode b y c)
rotateRight _ = error "rotateRight: invalid tree structure"

-- | 左旋：对以 x 为根，右子树为 y 的子树做单次左旋
--   结构：    x                   y
--            / \     ->        /   \
--           A   y             x     C
--              / \           / \
--             B   C         A   B
-- | rotateLeft: 单次左旋操作。
-- 对形如 (x A (y B C)) 的子树进行左旋，返回新的子树根 y（并修正高度）
rotateLeft :: Ord a => AVLTree a -> AVLTree a
rotateLeft (Node a x (Node b y c _) _) =
    mkNode (mkNode a x b) y c
rotateLeft _ = error "rotateLeft: invalid tree structure"

-- | 基于通用旋转实现四种常见旋转：LL, LR, RL, RR
-- LL: 左子树失衡（Left-Left），对应对根做右旋
-- | rotateLL: 左左失衡时的修正（等价于对根做一次右旋）
rotateLL :: Ord a => AVLTree a -> AVLTree a
rotateLL = rotateRight

-- RR: 右子树失衡（Right-Right），对应对根做左旋
-- | rotateRR: 右右失衡时的修正（等价于对根做一次左旋）
rotateRR :: Ord a => AVLTree a -> AVLTree a
rotateRR = rotateLeft


-- LR: 先左旋左子树，再右旋
-- | rotateLR: 左右失衡的修正：先对左子树做左旋，再对根做右旋
rotateLR :: Ord a => AVLTree a -> AVLTree a
rotateLR (Node l x r _) = rotateRight (mkNode (rotateLeft l) x r)
rotateLR _ = error "rotateLR: invalid tree structure"
-- RL: 先右旋右子树，再左旋
-- | rotateRL: 右左失衡的修正：先对右子树做右旋，再对根做左旋
rotateRL :: Ord a => AVLTree a -> AVLTree a
rotateRL (Node l x r _) = rotateLeft (mkNode l x (rotateRight r))
rotateRL _ = error "rotateRL: invalid tree structure"

-- | 计算平衡因子 = 左子树高度 - 右子树高度
-- | balanceFactor: 计算节点的平衡因子 = 左子树高度 - 右子树高度
-- 正值表示左重，负值表示右重
balanceFactor :: Ord a => AVLTree a -> Int
balanceFactor Empty = 0
balanceFactor (Node l _ r _) = height l - height r


-- | balance: 根据平衡因子选择合适的旋转使子树平衡
--   返回新的子树根（高度已维护）
-- | balance: 对给定子树进行局部平衡调整
-- 根据平衡因子选择 LL/LR/RR/RL 中的一种旋转（或无需旋转），并返回新的子树根
balance :: Ord a => AVLTree a -> AVLTree a
balance Empty = Empty
balance t@(Node l x r _)
    | bf > 1 && balanceFactor l >= 0 = rotateRight t                 -- LL
    | bf > 1                         = rotateRight (mkNode (rotateLeft l) x r) -- LR
    | bf < -1 && balanceFactor r <= 0 = rotateLeft t                 -- RR
    | bf < -1                        = rotateLeft (mkNode l x (rotateRight r)) -- RL
    | otherwise                      = mkNode l x r
    where bf = balanceFactor t


-- | 插入一个值并保持 AVL 平衡（如果已存在则不插入重复值）
-- | insert: 向 AVL 树中插入一个值并保持平衡。重复值将被忽略。
-- 使用递归插入到适当子树，然后对回溯路径上的每个节点做 balance
insert :: Ord a => a -> AVLTree a -> AVLTree a
insert x Empty = mkTree x
insert x t@(Node l y r _)
    | x < y     = balance (mkNode (insert x l) y r)
    | x > y     = balance (mkNode l y (insert x r))
    | otherwise = t  -- 相等时不插入重复元素


-- 简单的演示入口：构建一个树、插入几个数并打印结果
-- | main: 从标准输入读取数字序列并逐步插入，同时在每次插入后打印当前树状态
-- 输入格式：第一行一个整数 n（可忽略），接下来若干行包含空格分隔的整数
-- 示例： printf "5\n88 70 61 96 120\n" | runhaskell avl.hs
-- main :: IO ()
-- main = do
--     -- 从标准输入读取：第一行数字数量（可忽略），第二行为空格分隔的数字序列
--     input <- getContents
--     let ls = lines input
--     case ls of
--       (_:rest) -> do
--           let nums = concatMap words rest
--               xs = map read nums :: [Int]
--           -- 逐步插入并在每一步打印当前树状态
--           let step acc x = do
--                 let t' = insert x acc
--                 putStrLn $ "after insert " ++ show x ++ ":"
--                 putStrLn $ "height: " ++ show (height t') ++ ", root bf: " ++ show (balanceFactor t')
--                 putStrLn $ printTree t'
--                 return t'
--           _ <- foldM step Empty xs
--           return ()
--       _ -> putStrLn "expected input: n\nlist_of_numbers"



main :: IO ()
main = do
    -- 从标准输入读取：第一行数字数量（可忽略），第二行为空格分隔的数字序列
    input <- getContents
    let ls = lines input
    case ls of
      (_:rest) -> do
          let nums = concatMap words rest
              xs   = map read nums :: [Int]
              -- 累积构建最终的 AVL 树
              finalTree = foldl (\acc x -> insert x acc) Empty xs
          -- 打印最后根结点的值
          putStrLn (printNode finalTree)
      _ -> putStrLn "expected input: n\nlist_of_numbers"