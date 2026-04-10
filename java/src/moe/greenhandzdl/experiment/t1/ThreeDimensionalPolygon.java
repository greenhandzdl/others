package moe.greenhandzdl.experiment.t1;

import java.util.Scanner;

public interface ThreeDimensionalPolygon {
    abstract double getVolumes();
    abstract double getAreas();
}

interface Cube extends ThreeDimensionalPolygon {

    public abstract double getLength();

    public abstract double getWidth();

    public abstract double getHeight();

    public abstract void setLength(double length);

    public abstract void setWidth(double width);

    public abstract void setHeight(double height);

}

class main {
    private static final StringBuilder output = new StringBuilder();

    // 静态代码块：在类加载时执行
    static {
        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            System.out.println("\n监测到Kill Sign，输出结果：");
            System.out.println(output);
        }));
    }

    private static double readPositiveDouble(Scanner sc, String prompt) {
        double value;
        while (true) {
            System.out.print(prompt);
            if (sc.hasNextDouble()) {
                value = sc.nextDouble();
                if (value > 0) {
                    sc.nextLine(); // Consume the newline character
                    return value;
                } else {
                    System.out.println("输入的值必须大于0，请重新输入！");
                }
            } else {
                System.out.println("输入无效，请输入一个正数！");
                sc.nextLine(); // 清除错误输入
            }
        }
    }

    public static void main(String[] args) {
        var Cube = new Cube() {
            private double length = 0;
            private double width = 0;
            private double height = 0;

            public double getLength() {
                return length;
            }
            public double getWidth() {
                return width;
            }
            public double getHeight() {
                return height;
            }

            public void setLength(double length) {
                this.length = length;
            }
            public void setWidth(double width) {
                this.width = width;
            }
            public void setHeight(double height) {
                this.height = height;
            }


            @Override
            public double getVolumes() {
                return length * width * height;
            }

            @Override
            public double getAreas() {
                return  2*(length*width + width*height +height*length);
            }
        };
        var sc = new Scanner(System.in);

        System.out.println("请输入长宽高：");
        try {
            for(int id = 1; ;++id) {
                Cube.setLength(readPositiveDouble(sc, "请输入第" + id + "个立方体的长度："));
                Cube.setWidth(readPositiveDouble(sc, "请输入第" + id + "个立方体的宽度："));
                Cube.setHeight(readPositiveDouble(sc, "请输入第" + id + "个立方体的高度："));
                output.append(String.format("第%d个立方体，", id))
                        .append(String.format("长：%.2f，宽：%.2f，高：%.2f\n", Cube.getLength(), Cube.getWidth(), Cube.getHeight()))
                        .append(String.format("体积：%.2f，表面积：%.2f\n", Cube.getVolumes(), Cube.getAreas()));
            }
        } catch (Exception e) {
            System.out.println("检测到异常数据，输入结束，输出异常数据之前结果：");
        } finally {
            sc.close();
            System.out.println(output);
        }
    }
}

