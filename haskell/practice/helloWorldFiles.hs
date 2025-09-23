import System.IO

main = do
    handle <- openFile "helloWorld.txt" ReadMode
    contents <- hGetContents handle
    putStrLn contents
    hClose handle

main' = do withFile "helloWorld.txt" ReadMode (\handle -> do
    --         hSetBuffering handle $ BlockBuffering (Just 2048)  
    contents <- hGetContents handle
    putStrLn contents)

main'' = do
    contents <- readFile "helloWorld.txt"
    putStrLn contents