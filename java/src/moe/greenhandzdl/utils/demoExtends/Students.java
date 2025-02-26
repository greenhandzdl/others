package moe.greenhandzdl.utils.demoExtends;

public class Students extends Person{
    public static enum TStudents {
        刚出生,
        小学生,
        中学生,
        大学生,
    }
    private TStudents tStudents;

    public static void main(String[] args){
        Students test = new Students("Greenhandzdl",18, TStudents.大学生);
        test.show();
    }

    public Students(String _Name, double _Age, TStudents _tStudents){
        super(_Name, _Age);
        this.tStudents = _tStudents;
        System.out.println("Students was created!");
    }
    public void show() {
        super.show();
        System.out.println("Students's tStudents is " + this.tStudents);
    }
}
