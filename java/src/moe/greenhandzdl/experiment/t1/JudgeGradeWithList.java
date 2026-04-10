package moe.greenhandzdl.experiment.t1;

import java.util.Scanner;

public class JudgeGradeWithList {

    private class Students{
        String name = new String();
        int score = 0;
        Students(){}
        Students(String name,int score){
            this.name = name;
            this.score = score;
        }
    }

    private static final java.util.List<Students> studentsList = new java.util.ArrayList<Students>();

    // 静态代码块：在类加载时执行
    static {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.out.println("\n监测到Kill Sign，输出结果：");
            for(var students: studentsList){
                System.out.println("学生姓名：" + students.name + "，成绩：" + students.score + "，评语：" + convertGrade(students.score));
            }
        }));
    }

    private static String convertGrade(int score) {
        return score >= 60 ? "及格" : "不及格";
    }

    // 封装读取姓名的逻辑
    private static String readName(Scanner scanner) {
        String name;
        do {
            System.out.print("请输入学生姓名：");
            name = scanner.nextLine();
            if (name.isEmpty()) {
                System.out.println("姓名不能为空，请重新输入！");
            }
        } while (name.isEmpty());
        return name;
    }

    // 封装读取成绩的逻辑
    private static int readScore(Scanner scanner) {
        int score;
        while (true) {
            System.out.print("请输入学生成绩：");
            if (scanner.hasNextInt()) {
                score = scanner.nextInt();
                scanner.nextLine(); // Consume the newline character
                if (score >= 0 && score <= 100) {
                    break;
                } else {
                    System.out.println("成绩必须在0到100之间，请重新输入！");
                }
            } else {
                System.out.println("输入无效，请输入一个整数！");
                scanner.nextLine(); // 清除错误输入
            }
        }
        return score;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        while (true) {
            String name = readName(scanner);
            int score = readScore(scanner);

            studentsList.add(new JudgeGradeWithList().new Students(name, score));

        }
    }
}
