-- 文件名: caesa.hs

import Data.Char
import Data.List

caesaEncrypt :: Int -> String -> String
caesaEncrypt shift msg = map (chr . (+ shift) . ord) msg