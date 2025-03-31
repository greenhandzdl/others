-- 显示 lambda 表达式的计算结果
plus num1 num2 = print ((\num1 num2 -> num1 + num2) num1 num2)