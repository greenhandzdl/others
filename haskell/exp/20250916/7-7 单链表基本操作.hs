{-# LANGUAGE NamedFieldPuns #-}

import Text.Read (readMaybe)
import Data.Maybe (fromJust)
import System.Exit (exitWith, ExitCode(..))

printList :: Show a => [a] -> IO ()
printList = (>> putStrLn " ") . putStr . unwords . map show

operateList :: Int -> [Int] -> IO [Int]
operateList num list = operateListHelper num list
  where
    operateListHelper :: Int -> [Int] -> IO [Int]
    operateListHelper 0 finalList = return finalList
    operateListHelper remainingOps currentList = do
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
                in do
                    operateListHelper (remainingOps - 1) newList

handleInsert :: [Int] -> [Int] -> [Int]
handleInsert [_, k, d] list
    | k == 0    = d : list
    | k < length list = take k list ++ [d] ++ drop k list
    | otherwise = list

handleDelete :: [Int] -> [Int] -> [Int]
handleDelete [_, k] list
    | k <= 0 || k > length list = list
    | otherwise = take (k - 1) list ++ drop k list

main :: IO ()
main = do
    sSize <- getLine
    sList <- getLine
    let mSize = readMaybe sSize :: Maybe Int
        mList = sequence $ fmap readMaybe (words sList) :: Maybe [Int]
    if mSize == Nothing || mList == Nothing || fromJust mSize /= length (fromJust mList)
    then exitWith (ExitFailure 0)
    else do
        let size = fromJust mSize
            list = fromJust mList
        sOpNum <- getLine
        let mOpNum = readMaybe sOpNum :: Maybe Int
        if mOpNum == Nothing
        then exitWith (ExitFailure 0)
        else do
            let opNum = fromJust mOpNum
            results  <- operateList opNum list
            printList results


    exitWith ExitSuccess