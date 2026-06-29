#include "db/db.cpp"

int main() {
    Zaiko z;
    z.load();
    z.view();
    z.save();

    return 0;
}
