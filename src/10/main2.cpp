#include "db/db.cpp"

int main() {
    ChuumonKanri ch;
    ch.load();
    ch.view();
    ch.save();

    return 0;
}
