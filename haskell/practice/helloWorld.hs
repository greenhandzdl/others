-- ghc --make helloworld  
main = do
    putStrLn "What is your name?"
    name <- getLine
    putStrLn (name ++ ",Hello World!")