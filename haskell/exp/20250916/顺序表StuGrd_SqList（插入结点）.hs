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

main :: IO ()
main = do
    addon <- getLine
    -- 修改点1: 变量名改为listIndexStr，更清晰地表示这是字符串输入
    listIndexStr <- getLine  -- 原代码: listIndex <- getLine
    let pAddon = read addon :: StuGrade
        -- 修改点2: 从listIndexStr读取而不是listIndex
        pListIndex = read listIndexStr :: Int  -- 原代码: pListIndex = read listIndex :: Int
        -- 修改点3: 计算列表长度并存储
        listLength = length initializeStuGrade  -- 新增代码
    -- 修改点4: 扩展条件判断，允许插入位置为1到length+1（包括末尾插入）
    if pListIndex < 1 || pListIndex > listLength + 1  -- 原代码: if ( pListIndex > length initializeStuGrade ) || ( pListIndex < 1 )
        -- 修改点5: 简化错误处理，直接使用putStrLn
        then putStrLn "插入位置无效"  -- 原代码: putStr "插入位置无效" 和 return ()
        else do
            let stuGradeList = addStuGrade initializeStuGrade pListIndex pAddon
            print StuGradeInit
            printStuGradeList stuGradeList