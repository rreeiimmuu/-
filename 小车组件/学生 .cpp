#include <iostream>
#include <string>

// 学生类
class Student {
public:
    Student(const std::string& name, int age, const std::string& degree)
        : name(name), age(age), degree(degree) {}

    virtual void printInfo() const {
        std::cout << "姓名：" << name << std::endl;
        std::cout << "\\t年龄：" << age << std::endl;
        std::cout << "\\t学位：" << degree << std::endl;
    }

protected:
    std::string name;
    int age;
    std::string degree;
};

// 本科生类
class Undergraduate : public Student {
public:
    Undergraduate(const std::string& name, int age, const std::string& specialty)
        : Student(name, age, "本科"), specialty(specialty) {}

    void printInfo() const override {
        Student::printInfo();
        std::cout << "\\t专业：" << specialty << std::endl;
    }

private:
    std::string specialty;
};

// 研究生类
class Graduate : public Student {
public:
    Graduate(const std::string& name, int age, const std::string& studyDirection)
        : Student(name, age, "硕士"), studyDirection(studyDirection) {}

    void printInfo() const override {
        Student::printInfo();
        std::cout << "\\t研究方向：" << studyDirection << std::endl;
    }

private:
    std::string studyDirection;
};

// 测试类
class Test {
public:
    static void run() {
        Student* students[2];

        students[0] = new Undergraduate("王军", 23, "工业自动化");
        students[1] = new Graduate("刘君", 27, "网络技术");

        for (int i = 0; i < 2; ++i) {
            students[i]->printInfo();
            std::cout << "------------------" << std::endl;
        }

        // 释放动态分配的内存
        for (int i = 0; i < 2; ++i) {
            delete students[i];
        }
    }
};

int main() {
    Test::run();
    return 0;
}