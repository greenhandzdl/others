-- 创建数据库
CREATE DATABASE IF NOT EXISTS university_management;
USE university_management;

-- 1. 创建院系表
CREATE TABLE DEPARTMENTS (
    dept_id INT AUTO_INCREMENT PRIMARY KEY,
    dept_name VARCHAR(50) NOT NULL UNIQUE,
    office_loc VARCHAR(100) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 2. 创建课程表
CREATE TABLE COURSES (
    c_id INT AUTO_INCREMENT PRIMARY KEY,
    c_name VARCHAR(100) NOT NULL,
    credit TINYINT NOT NULL CHECK (credit BETWEEN 1 AND 10),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- 3. 创建学生表
CREATE TABLE STUDENTS (
    stu_id INT AUTO_INCREMENT PRIMARY KEY,
    stu_name VARCHAR(50) NOT NULL,
    gender ENUM('M', 'F') NOT NULL,
    birthday DATE NOT NULL,
    addr VARCHAR(200),
    dept_id INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (dept_id) REFERENCES DEPARTMENTS(dept_id) ON DELETE RESTRICT,
    INDEX idx_dept_id (dept_id),
    INDEX idx_birthday (birthday)
);

-- 4. 创建成绩表
CREATE TABLE SCORES (
    grade DECIMAL(5,2) CHECK (grade >= 0 AND grade <= 100),
    term VARCHAR(20) NOT NULL,
    exam_date DATE NOT NULL,
    stu_id INT NOT NULL,
    c_id INT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    PRIMARY KEY (stu_id, c_id),
    FOREIGN KEY (stu_id) REFERENCES STUDENTS(stu_id) ON DELETE CASCADE,
    FOREIGN KEY (c_id) REFERENCES COURSES(c_id) ON DELETE CASCADE,
    INDEX idx_stu_id (stu_id),
    INDEX idx_c_id (c_id),
    INDEX idx_term (term)
);

-- 插入模拟数据

-- 插入院系数据
INSERT INTO DEPARTMENTS (dept_name, office_loc) VALUES
('计算机科学与技术学院', '科技楼A座301'),
('电子信息工程学院', '科技楼B座205'),
('机械工程学院', '工程楼101'),
('经济管理学院', '经管楼308'),
('外国语学院', '文科楼102');

-- 插入课程数据
INSERT INTO COURSES (c_name, credit) VALUES
('高等数学', 4),
('大学英语', 3),
('程序设计基础', 3),
('数据结构', 4),
('电路原理', 3),
('机械设计', 3),
('微观经济学', 2),
('数据库系统', 3),
('操作系统', 4),
('计算机网络', 3);

-- 插入学生数据
INSERT INTO STUDENTS (stu_name, gender, birthday, addr, dept_id) VALUES
('张三', 'M', '2002-05-15', '北京市海淀区', 1),
('李四', 'M', '2003-02-20', '上海市浦东新区', 1),
('王五', 'F', '2002-11-08', '广州市天河区', 2),
('赵六', 'F', '2003-07-12', '深圳市南山区', 2),
('钱七', 'M', '2002-09-25', '杭州市西湖区', 3),
('孙八', 'F', '2003-04-18', '南京市鼓楼区', 3),
('周九', 'M', '2002-12-30', '成都市武侯区', 4),
('吴十', 'F', '2003-01-14', '武汉市洪山区', 4),
('郑十一', 'M', '2002-08-22', '西安市雁塔区', 1),
('王十二', 'F', '2003-03-07', '长沙市岳麓区', 2);

-- 插入成绩数据
INSERT INTO SCORES (grade, term, exam_date, stu_id, c_id) VALUES
(85.50, '2023-2024-1', '2024-01-15', 1, 1),
(92.00, '2023-2024-1', '2024-01-16', 1, 2),
(78.50, '2023-2024-1', '2024-01-17', 1, 3),
(88.00, '2023-2024-1', '2024-01-15', 2, 1),
(76.50, '2023-2024-1', '2024-01-16', 2, 2),
(91.00, '2023-2024-1', '2024-01-17', 2, 3),
(82.50, '2023-2024-1', '2024-01-15', 3, 4),
(79.00, '2023-2024-1', '2024-01-16', 3, 5),
(87.50, '2023-2024-1', '2024-01-17', 4, 4),
(94.00, '2023-2024-1', '2024-01-15', 4, 5),
(81.50, '2023-2024-1', '2024-01-16', 5, 6),
(89.00, '2023-2024-1', '2024-01-17', 5, 1),
(77.50, '2023-2024-1', '2024-01-15', 6, 6),
(83.00, '2023-2024-1', '2024-01-16', 6, 2),
(90.50, '2023-2024-1', '2024-01-17', 7, 7),
(85.00, '2023-2024-1', '2024-01-15', 7, 1),
(79.50, '2023-2024-1', '2024-01-16', 8, 7),
(86.00, '2023-2024-1', '2024-01-17', 8, 2),
(92.50, '2023-2024-1', '2024-01-15', 9, 8),
(88.00, '2023-2024-1', '2024-01-16', 9, 9),
(84.50, '2023-2024-1', '2024-01-17', 10, 10),
(91.00, '2023-2024-1', '2024-01-15', 10, 4);

-- 创建一个视图：方便查询学生、院系、课程及成绩信息
CREATE OR REPLACE VIEW vw_student_scores AS
SELECT
    rank() OVER (PARTITION BY c.c_id ORDER BY sc.grade DESC) AS '排名',
    c.c_name AS '课程名称',
    s.stu_name AS '学生姓名',
    case s.gender WHEN 'M' THEN '男' WHEN 'F' THEN '女' END AS '性别',
    s.stu_id AS '学号',
    d.dept_name AS '院系',
    sc.grade AS '成绩',
    sc.term AS '学期',
    sc.exam_date AS '考试日期',
    sc.created_at AS '成绩录入时间'
FROM SCORES sc
JOIN STUDENTS s ON sc.stu_id = s.stu_id
JOIN COURSES c ON sc.c_id = c.c_id
LEFT JOIN DEPARTMENTS d ON s.dept_id = d.dept_id
ORDER BY '课程名称','排名' DESC;

SELECT
    *
FROM vw_student_scores;

-- 使用 SELECT 语句查看 student 表中的数据信息
SELECT * FROM STUDENTS;

-- 使用 SELECT 语句查看 score 表中的数据信息
SELECT * FROM SCORES;

-- 从 student 表中查询计算机科学与技术学院和外国语学院的信息
SELECT * FROM STUDENTS
WHERE dept_id IN (
    SELECT dept_id FROM DEPARTMENTS
    WHERE dept_name IN ('计算机科学与技术学院', '外国语学院')
);

-- 从 student 表中查询年龄 5~30 岁的学生信息。
SELECT * FROM STUDENTS
WHERE birthday BETWEEN DATE_SUB(CURDATE(), INTERVAL 30 YEAR) AND DATE_SUB(CURDATE(), INTERVAL 5 YEAR);

-- 在 student 表中统计每个院系各有几个学生。
SELECT d.dept_name AS '院系名称', COUNT(s.stu_id) AS '学生人数'
FROM STUDENTS s
JOIN DEPARTMENTS d ON s.dept_id = d.dept_id
GROUP BY s.dept_id, d.dept_name;

drop schema university_management;