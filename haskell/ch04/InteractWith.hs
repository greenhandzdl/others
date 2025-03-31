-- 文件名：ch04/InteractWith.hs
-- 编译命令：ghc --make InteractWith

-- 导入处理命令行参数的模块
import System.Environment (getArgs)

-- interactWith 函数负责读取输入文件，应用给定函数处理内容，然后将结果写入输出文件
-- 参数:
--   function: 用于处理输入内容的函数
--   inputFile: 输入文件的路径
--   outputFile: 输出文件的路径
interactWith function inputFile outputFile = do
  input <- readFile inputFile
  writeFile outputFile (function input)

-- main 函数是程序的入口点
-- 它通过 mainWith 函数来调用 interactWith，并处理命令行参数
main = mainWith myFunction
  where mainWith function = do
          args <- getArgs
          case args of
            [input,output] -> interactWith function input output
            _ -> putStrLn "error: exactly two arguments needed"

        -- 将 "id" 替换为我们的函数名
        myFunction = id