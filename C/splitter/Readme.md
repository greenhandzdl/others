## 关于splitter模块

> 灵感来源:

```haskell
import Data.List.Split (splitOn)

createSplitter :: String -> IO [String]
createSplitter delimiter = fmap (splitOn delimiter) getLine

-- 许愿（上面的版本可能会产生指向空字符串的指针，所以需要过滤掉空字符串）:
getSplitWordsLn = (filter (not . null) . splitOn " ") <$> getLine
```

该模块已经自文档化，在头文件已经驱动函数有较为详细解释。