-- 类似于InterActWith.hs

import System.Environment (getArgs)

opCW customFunction inputFile outputFile = do 
    input <- readFile inputFile
    writeFile outputFile (customFunction input)


main = mainWith customFunction
    where
        mainWith function = do
            args <- getArgs
            case args of
                [input,output] -> opCW function input output
                _ -> putStrLn "error: exactly two arguments needed"
        customFunction = id