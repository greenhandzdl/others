#include <iostream>
#include <string>

// 基类 Employee
class Employee {
protected:
    int id;
    std::string name;
    double baseSalary;

public:
    Employee(int _id, const std::string& _name, double _baseSalary)
        : id(_id), name(_name), baseSalary(_baseSalary) {}

    virtual double getSalary() const {
        return baseSalary;
    }

    virtual void displayInfo() const {
        std::cout << "员工ID: " << id << std::endl;
        std::cout << "姓名: " << name << std::endl;
        std::cout << "基本工资: " << baseSalary << std::endl;
    }

    virtual ~Employee() {}
};

// 派生类 Manager
class Manager : public Employee {
protected:
    double bonus;

public:
    Manager(int _id, const std::string& _name, double _baseSalary, double _bonus)
        : Employee(_id, _name, _baseSalary), bonus(_bonus) {}

    double getSalary() const override {
        return baseSalary + bonus;
    }

    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << "奖金: " << bonus << std::endl;
        std::cout << "总薪资: " << getSalary() << std::endl;
    }
};

// 派生类 Developer
class Developer : public Employee {
private:
    double hourlyWage;
    double hoursWorked;

public:
    Developer(int _id, const std::string& _name, double _baseSalary, 
              double _hourlyWage, double _hoursWorked)
        : Employee(_id, _name, _baseSalary), 
          hourlyWage(_hourlyWage), hoursWorked(_hoursWorked) {}

    double getSalary() const override {
        return baseSalary + (hourlyWage * hoursWorked);
    }

    void displayInfo() const override {
        Employee::displayInfo();
        std::cout << "时薪: " << hourlyWage << std::endl;
        std::cout << "工作小时数: " << hoursWorked << std::endl;
        std::cout << "总薪资: " << getSalary() << std::endl;
    }
};

// 从 Manager 派生的 SeniorManager 类
class SeniorManager : public Manager {
private:
    double stockOptions;

public:
    SeniorManager(int _id, const std::string& _name, double _baseSalary, 
                  double _bonus, double _stockOptions)
        : Manager(_id, _name, _baseSalary, _bonus), stockOptions(_stockOptions) {}

    double getSalary() const override {
        return baseSalary + bonus + stockOptions;
    }

    void displayInfo() const override {
        Manager::displayInfo();
        std::cout << "股票期权价值: " << stockOptions << std::endl;
        std::cout << "总薪资(含股票): " << getSalary() << std::endl;
    }
};

int main() {
    // 创建 Manager 实例
    Manager manager(1001, "张经理", 10000, 5000);
    std::cout << "======== 经理信息 ========" << std::endl;
    manager.displayInfo();
    std::cout << std::endl;

    // 创建 Developer 实例
    Developer developer(2001, "李开发", 8000, 200, 160);
    std::cout << "======== 开发人员信息 ========" << std::endl;
    developer.displayInfo();
    std::cout << std::endl;

    // 创建 SeniorManager 实例
    SeniorManager seniorManager(3001, "王高管", 15000, 8000, 20000);
    std::cout << "======== 高级经理信息 ========" << std::endl;
    seniorManager.displayInfo();
    std::cout << std::endl;

    return 0;
}