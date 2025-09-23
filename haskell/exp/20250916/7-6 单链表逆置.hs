import Text.Read (readMaybe)
import Data.Maybe (fromJust)
import System.Exit (exitWith, ExitCode(..))


printList :: Show a => [a] -> IO ()
printList  = putStrLn . unwords . map show 

main :: IO ()
main = do
    sSize <- getLine
    sList <- getLine
    let mSize = readMaybe sSize :: Maybe Int
        mList = sequence $ fmap readMaybe $ words sList :: Maybe [Int]
    if mSize == Nothing || mList == Nothing
    then do
        putStrLn "输入格式错误"
        return ()
    else do
        let size = fromJust mSize
            list = reverse $ fromJust mList
        if size /= length list
        then do
            putStrLn "输入的列表长度与长度不符"
            return ()
        else do
            printList list
            return ()
    
    exitWith ExitSuccess  -- 返回状态码 0 表示成功
