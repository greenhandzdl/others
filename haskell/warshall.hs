-- Warshall算法函数，接收布尔矩阵，返回传递闭包后的布尔矩阵
warshall :: [[Bool]] -> [[Bool]]
-- 实现Warshall算法的主要函数
warshall adj =
  -- 获取矩阵的大小（假设为n×n矩阵）
  let n = length adj
      -- 定义一个辅助函数，用于更新矩阵中通过顶点k的路径
      -- k是当前考虑的中间顶点
      -- matrix是当前的邻接矩阵
      updateK k matrix =
        -- 对于每一行i
        [ [ matrix !! i !! j || (matrix !! i !! k && matrix !! k !! j)
          -- 对于每一列j，更新i到j的路径是否存在
          -- 新的路径存在当且仅当原来i到j有路径，或者i到k有路径且k到j有路径
          | j <- [0..n-1] ]
          | i <- [0..n-1] ]
      -- 使用foldl迭代应用updateK函数，对于每个可能的中间顶点k（从0到n-1）
      -- 初始矩阵是原始邻接矩阵adj
      final = foldl (\acc k -> updateK k acc) adj [0..n-1]
  -- 返回最终计算出的传递闭包矩阵
  in final

-- 测试数据：表示有向图的邻接矩阵
-- 例如：graph1表示4个顶点的有向图
graph1 :: [[Bool]]
graph1 = [ [False, True,  False, False],  -- 顶点0到顶点1有边
           [False, False, True,  False],  -- 顶点1到顶点2有边
           [False, False, False, True ],  -- 顶点2到顶点3有边
           [False, False, False, False] ] -- 顶点3没有出边

-- 另一个测试数据
graph2 :: [[Bool]]
graph2 = [ [True,  False, True ],
           [False, True,  False],
           [False, True,  True ] ]

-- 打印矩阵的辅助函数
printMatrix :: [[Bool]] -> IO ()
printMatrix [] = return ()
printMatrix (row:rows) = do
    putStrLn $ unwords $ map (\b -> if b then "1" else "0") row
    printMatrix rows

main :: IO ()
main = do
    putStrLn "原始图1的邻接矩阵:"
    printMatrix graph1
    putStrLn "图1的传递闭包:"
    printMatrix $ warshall graph1
    putStrLn ""  -- 空行分隔
    
    putStrLn "原始图2的邻接矩阵:"
    printMatrix graph2
    putStrLn "图2的传递闭包:"
    printMatrix $ warshall graph2
