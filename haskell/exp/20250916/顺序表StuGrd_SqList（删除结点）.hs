infixl 1 `StuGrade`

data StuGrade = 
        StuGradeInit
    |   StuGrade {
        stuId :: String,
        name :: String,
        mathGrade :: Int,
        chineseGrade :: Int,
        phyGrade :: Int,
        totalGrade :: Int
} deriving (Eq)

instance Show StuGrade where
    show StuGradeInit = "学号    姓名    数学  语文  物理  总成绩"
    show (StuGrade stuId name mathGrade chineseGrade phyGrade totalGrade) =
        stuId ++ "     " ++ name ++ "   " ++ show mathGrade ++ "    " ++ show chineseGrade ++ "    " ++ show phyGrade ++ "    " ++ show totalGrade

printStuGradeList :: [StuGrade] -> IO ()
printStuGradeList stuGradeList = do
    mapM_ print stuGradeList


initializeStuGrade :: [StuGrade]
initializeStuGrade =
    [ StuGrade { stuId = "A001", name = "张一", mathGrade = 90, chineseGrade = 85, phyGrade = 95, totalGrade = 270 }
    , StuGrade { stuId = "A002", name = "王二", mathGrade = 80, chineseGrade = 85, phyGrade = 90, totalGrade = 255 }
    , StuGrade { stuId = "A003", name = "李三", mathGrade = 95, chineseGrade = 91, phyGrade = 99, totalGrade = 285 }
    , StuGrade { stuId = "A004", name = "赵四", mathGrade = 70, chineseGrade = 84, phyGrade = 86, totalGrade = 240 }
    ]

isValidIndex :: [StuGrade] -> Int -> Bool
isValidIndex stuGradeList index =
    let listLength = length stuGradeList
    in index >= 1 && index <= listLength

deleteStuGrade :: [StuGrade] -> Int -> Maybe [StuGrade]
deleteStuGrade stuGradeList index =
    if isValidIndex stuGradeList index
        then Just (take (index - 1) stuGradeList ++ drop index stuGradeList)
        else Nothing

main :: IO ()
main = do
    sIndex <- getLine
    let index = read sIndex
    case deleteStuGrade initializeStuGrade index of
        Nothing -> putStrLn "删除位置无效"
        Just newList -> do
            print(StuGradeInit)
            printStuGradeList(newList)
