#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class ScoreBoard {
  private:
    int b; // ボールを数える
    int s; // ストライクを数える
    int o; // アウトを数える
  public:
    ScoreBoard() {
        b = 0;
        s = 0;
        o = 0;
    }
    void ball();
    void print();
    int strike();
    int out();
};

void ScoreBoard::ball() {
    b++;
    if (b == 4) { // フォアボール
        b = 0;
        s = 0;
    }
}

int ScoreBoard::strike() {
    s++;
    if (s == 3) { // ストライクアウト
        b = 0;
        s = 0;
        return out(); // アウトを1個増やす（チェンジ時は1が返る）
    }
    return 0;
}

int ScoreBoard::out() {
    o++;
    if (o == 3) { // チェンジ
        return 1; // チェンジの時は１を返す
    } else {      // アウトカウントが増えたとき
        b = 0;
        s = 0;
        return 0; // アウトカウントが増えたときは０を返す
    }
}

void ScoreBoard::print() {
    cout << "B: ";
    for (int i = 0; i < b; i++) {
        cout << "o";
    }
    cout << endl;

    cout << "S: ";
    for (int i = 0; i < s; i++) {
        cout << "o";
    }
    cout << endl;

    cout << "O: ";
    for (int i = 0; i < o; i++) {
        cout << "o";
    }
    cout << endl;
}

int main(void) {
    string s;
    ScoreBoard sb;

    while (cin >> s) {
        if (s == "b") {
            sb.ball();
            sb.print();
        } else if (s == "s") {
            if (sb.strike() == 1) {
                break;
            }
            sb.print();
        } else if (s == "o") {
            if (sb.out() == 1) {
                break;
            }
            sb.print();
        }
    }
    return 0;
}
