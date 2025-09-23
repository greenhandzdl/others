{-# LANGUAGE NamedFieldPuns #-}
{-# LANGUAGE BangPatterns #-}

import Text.Read (readMaybe)
import Data.Maybe (isNothing, fromJust) -- 确保导入 fromJust
import System.Exit (exitWith, ExitCode(..))
import qualified Data.Sequence as Seq
import Data.Foldable (toList)

-- 打印列表
printList :: Show a => [a] -> IO ()
printList = (>> putStrLn " ") . putStr . unwords . map show

-- 操作列表
operateList :: Int -> Seq.Seq Int -> IO (Seq.Seq Int)
operateList num list = operateListHelper num list
  where
    operateListHelper :: Int -> Seq.Seq Int -> IO (Seq.Seq Int)
    operateListHelper 0 !finalList = return finalList
    operateListHelper !remainingOps !currentList = do
        sOpSeq <- getLine
        let mOpSeq = sequence $ map readMaybe (words sOpSeq) :: Maybe [Int]
        case mOpSeq of
            Nothing -> operateListHelper (remainingOps - 1) currentList
            Just opSeq ->
                let newList =
                        if length opSeq == 3 && head opSeq == 0
                        then handleInsert opSeq currentList
                        else if length opSeq == 2 && head opSeq == 1
                             then handleDelete opSeq currentList
                             else currentList
                in operateListHelper (remainingOps - 1) newList

-- 插入操作
handleInsert :: [Int] -> Seq.Seq Int -> Seq.Seq Int
handleInsert [_, k, d] !list
    | k == 0    = d Seq.<| list -- 正确使用中缀操作符
    | k < Seq.length list = Seq.insertAt k d list
    | otherwise = list

-- 删除操作
handleDelete :: [Int] -> Seq.Seq Int -> Seq.Seq Int
handleDelete [_, k] !list
    | k <= 0 || k > Seq.length list = list
    | otherwise = Seq.deleteAt (k - 1) list

-- 主函数
main :: IO ()
main = do
    sSize <- getLine
    sList <- getLine
    let mSize = readMaybe sSize :: Maybe Int
        mList = sequence $ fmap readMaybe (words sList) :: Maybe [Int]
    if isNothing mSize || isNothing mList || fromJust mSize /= length (fromJust mList)
    then exitWith (ExitFailure 0)
    else do
        let size = fromJust mSize
            list = Seq.fromList (fromJust mList) -- 使用 Sequence 替代普通列表
        sOpNum <- getLine
        let mOpNum = readMaybe sOpNum :: Maybe Int
        if isNothing mOpNum
        then exitWith (ExitFailure 0)
        else do
            let opNum = fromJust mOpNum
            results <- operateList opNum list
            printList (toList results) -- 将 Sequence 转回列表打印
            exitWith ExitSuccess