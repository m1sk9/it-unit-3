#include <iostream>
#include <string>
using namespace std;

class Person {
  private:
    string name;

  public:
    void setName(string n);
    string getName();
};

void Person::setName(string n) {
    name = n;
}

string Person::getName() {
    return name;
}

class Teacher : public Person {
  private:
    string yakushoku;

  public:
    bool setYakushoku(string y);
    string getYakushoku();
};

bool Teacher::setYakushoku(string y) {
    if (y == "教授" || y == "准教授" || y == "助教") {
        yakushoku = y;
        return true; // 設定成功
    } else {
        yakushoku = ""; // 不正な役職名は空にする
        return false;   // 設定失敗
    }
}

string Teacher::getYakushoku() {
    return yakushoku;
}

int main(void) {
    Teacher nogi;

    nogi.setName("野木");
    if (nogi.setYakushoku("学長")) {
        cout << nogi.getName() << nogi.getYakushoku() << endl;
    } else {
        cout << "error" << endl;
    }

    if (nogi.setYakushoku("教授")) {
        cout << nogi.getName() << nogi.getYakushoku() << endl;
    } else {
        cout << "error" << endl;
    }

    return 0;
}
