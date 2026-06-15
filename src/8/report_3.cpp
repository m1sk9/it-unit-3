#include <iostream>
#include <string>
using namespace std;

class Person {
  private:
    string name;

  public:
    void setName(const string &n);
    string getName();
};

void Person::setName(const string &n) {
    name = n;
}

string Person::getName() {
    return name;
}

class Student : public Person {
  private:
    int gakuseki;

  public:
    virtual void setGakuseki(int n);
    int getGakuseki() const;
};

void Student::setGakuseki(int n) {
    gakuseki = n;
}

int Student::getGakuseki() const {
    return gakuseki;
}

class Student2 : public Student {
  public:
    void setGakuseki(int n);
};

void Student2::setGakuseki(int n) {
    if (n >= 100 && n <= 199) {
        Student::setGakuseki(n); // 正しい学籍番号
    } else {
        Student::setGakuseki(0); // 不正なときは0を設定
    }
}

int main(void) {
    Student2 iwasaki;

    iwasaki.setName("iwasaki");
    iwasaki.setGakuseki(100);
    if (iwasaki.getGakuseki() == 0) {
        cout << "error" << '\n';
    } else {
        cout << iwasaki.getName() << ":" << iwasaki.getGakuseki() << '\n';
    }

    iwasaki.setName("iwasaki");
    iwasaki.setGakuseki(300);
    if (iwasaki.getGakuseki() == 0) {
        cout << "error" << '\n';
    } else {
        cout << iwasaki.getName() << ":" << iwasaki.getGakuseki() << '\n';
    }

    return 0;
}
