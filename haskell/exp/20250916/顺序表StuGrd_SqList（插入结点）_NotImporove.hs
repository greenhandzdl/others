{-# LANGUAGE NamedFieldPuns #-}
import System.IO

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

instance Read StuGrade where
    readsPrec _ s =
        let fields = words s
        in case fields of
            (stuId : name : mathGradeStr : chineseGradeStr : phyGradeStr : _) ->
                let mathGrade = read mathGradeStr
                    chineseGrade = read chineseGradeStr
                    phyGrade = read phyGradeStr
                    totalGrade = sum [mathGrade, chineseGrade, phyGrade]
                in [(StuGrade { stuId, name, mathGrade, chineseGrade, phyGrade, totalGrade }, "")]
            _ -> error "输入格式错误，请确保输入包含学号、姓名和三科成绩！"

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

addStuGrade :: [StuGrade] -> Int -> StuGrade -> [StuGrade]
addStuGrade stuGradeList listIndex addon =
    let (left, right) = splitAt (listIndex-1) stuGradeList
    in left ++ [addon] ++ right

-- 不纯函数：获取用户输入的学生信息
getUserInput :: IO StuGrade
getUserInput = do
    -- putStrLn "请输入学生信息（格式：学号 姓名 数学成绩 语文成绩 物理成绩）："
    input <- getLine
    return (read input :: StuGrade)

-- 不纯函数：获取用户输入的插入位置
getInsertPosition :: IO Int
getInsertPosition = do
    -- putStrLn "请输入要插入的位置（从1开始）："
    positionStr <- getLine
    return (read positionStr :: Int)


-- 校验插入位置是否有效
validateInsertPosition :: Int -> Int -> Bool
validateInsertPosition listLength pListIndex =
    pListIndex >= 1 && pListIndex <= listLength + 1

-- 执行插入并返回新列表（如果位置无效则返回原列表）
performInsertion :: [StuGrade]  -> StuGrade -> IO [StuGrade]
performInsertion stuGradeList  pAddon = do
    let listLength = length initializeStuGrade
    pListIndex <- getInsertPosition
    if validateInsertPosition listLength pListIndex
        then return (addStuGrade stuGradeList pListIndex pAddon)
        else do
            putStrLn "插入位置无效"
            return stuGradeList

-- 主函数：整合逻辑
main :: IO ()
main = do
    -- 获取用户输入
    pAddon <- getUserInput

    -- 执行插入操作并获取结果列表
    stuGradeList <- performInsertion initializeStuGrade  pAddon

    -- 打印结果
    print StuGradeInit
    printStuGradeList stuGradeList