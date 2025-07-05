#include <iostream>
#include <string>

// 基类
class Person {
public:
    Person(const std::string& name, const std::string& birthDate, const std::string& gender, const std::string& college)
        : name(name), birthDate(birthDate), gender(gender), college(college) {}

    virtual void printInfo() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Birth Date: " << birthDate << std::endl;
        std::cout << "Gender: " << gender << std::endl;
        std::cout << "College: " << college << std::endl;
    }

protected:
    std::string name;
    std::string birthDate;
    std::string gender;
    std::string college;
};

// 教员类
class Teacher : public Person {
public:
    Teacher(const std::string& name, const std::string& birthDate, const std::string& gender, const std::string& college, const std::string& majorCode)
        : Person(name, birthDate, gender, college), majorCode(majorCode) {}

    void printInfo() const override {
        Person::printInfo();
        std::cout << "Major Code: " << majorCode << std::endl;
    }

private:
    std::string majorCode;
};

// 非教员类
class NonTeacher : public Person {
public:
    NonTeacher(const std::string& name, const std::string& birthDate, const std::string& gender, const std::string& college, const std::string& achievement)
        : Person(name, birthDate, gender, college), achievement(achievement) {}

    void printInfo() const override {
        Person::printInfo();
        std::cout << "Achievement: " << achievement << std::endl;
    }

private:
    std::string achievement;
};