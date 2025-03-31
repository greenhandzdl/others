-- 文件: ch04/Adler32.hs
-- .|.二进制或操作
-- .&.二进制与操作
-- shiftL 左移操作
-- ord 函数将字符转换为ASCII值



-- 导入必要的模块
import Data.Char (ord)
import Data.Bits (shiftL, (.&.), (.|.))

-- 定义基数，用于Adler-32算法中的计算
base = 65521

-- Adler-32 checksum计算函数
-- 该函数接收一个字节序列（Char的列表），并返回其Adler-32 checksum值
adler32 xs = helper 1 0 xs
    where
        -- 辅助函数，用于递归计算checksum
        -- a 和 b 是两个累积的checksum值
        helper a b (x:xs) = 
            let 
                -- 更新a的值，加上当前字符的ASCII值（限制在0-255范围内），并取模
                a' = (a + (ord x .&. 0xff)) `mod` base
                -- 更新b的值，加上新的a'值，并取模
                b' = (a' + b) `mod` base
            in 
                -- 继续处理列表中的下一个元素
                helper a' b' xs
        -- 当输入列表为空时，计算最终的checksum值
        -- 将b的值左移16位，然后与a的值进行按位或操作，得到最终的32位checksum值
        helper a b []     = (b `shiftL` 16) .|. a