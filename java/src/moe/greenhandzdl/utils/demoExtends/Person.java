package moe.greenhandzdl.utils.demoExtends;

// import java.util.Objects;
// Objects.requireNonNullElse(_Name,"Man");
import java.util.Optional;


public class Person {
    private final String Name;
    private double Age = 0d;

    public static void main(String[] args){
        Person test = new Person("Greenhandzdl", 18);
        test.show();
    }

    public Person(String _Name, double _Age) {
        this.Name = Optional.ofNullable(_Name).orElse("Man");
        this.Age = (_Age != 0 ) ? _Age : 18 ;
        System.out.println("Person was Created!");
    }
    public Person(String _Name){
        this(_Name,0);
    }
    public Person(double _Age){
        this(null,_Age);
    }
    public Person(){
        this(null,0);
    }

    public String getName() {
        return Name;
    }
    public double getAge(){
        return Age;
    }
    public void setAge(double _Age){
        this.Age = _Age;
    }

    public void show(){
        System.out.println("Name:"+this.Name+",Age:"+this.Age);
    }
}
