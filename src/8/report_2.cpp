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

class Student : public Person {
  private:
    int gakuseki;

  public:
    void setGakuseki(int n);
    int getGakuseki();
};

void Student::setGakuseki(int n) {
    gakuseki = n;
}

int Student::getGakuseki() {
    return gakuseki;
}

int main(void) {
    Student sasaki;
    sasaki.setName("ささき");
    sasaki.setGakuseki(100);
    cout << sasaki.getName() << endl;
    cout << sasaki.getGakuseki() << endl;
    return 0;
}
