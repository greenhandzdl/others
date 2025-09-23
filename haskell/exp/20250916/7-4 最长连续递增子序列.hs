type Sequence a = [a]

parseSequence :: String -> Maybe (Sequence Int)
parseSequence s =
    let fields = words s
    in if null fields
       then Nothing
       else Just (map read fields)

longestContinuousIncreasingSubsequence :: Sequence Int -> Sequence Int
longestContinuousIncreasingSubsequence [] = []
longestContinuousIncreasingSubsequence seq =
    let (_, _, longest) = foldl step ([], [], []) seq
    in longest
  where
    step :: (Sequence Int, Sequence Int, Sequence Int) -> Int -> (Sequence Int, Sequence Int, Sequence Int)
    step (current, longest, maxSeq) x
        | null current || x > last current =
            let newCurrent = current ++ [x]
            in if length newCurrent > length longest
               then (newCurrent, newCurrent, newCurrent)
               else (newCurrent, longest, maxSeq)
        | otherwise =
            let newCurrent = [x]
            in (newCurrent, longest, maxSeq)

main :: IO ()
main = do
    sLength <- getLine
    sSeq <- getLine

    let lengthResult = reads sLength :: [(Int, String)]
    let declaredLength = case lengthResult of
            [(length, "")] -> Just length
            _ -> Nothing

    let seqResult = parseSequence sSeq
    let seqLength = fmap length seqResult

    if declaredLength /= seqLength || declaredLength == Nothing || seqLength == Nothing
    then do
        putStrLn "输入格式错误"
        return ()
    else do
        let Just seq = seqResult
        let result = longestContinuousIncreasingSubsequence seq
        putStrLn (unwords (map show result))