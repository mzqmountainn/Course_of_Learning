//
// Created by 18455 on 2026/4/13.
//

#include <iostream>

using namespace std;

class Move {
private:
    double x;
    double y;
public:
    Move(double a = 0, double b = 0);
    void showmove() const;
    Move add(const Move &m) const;
    void reset(double a = 0, double b = 0);
};

Move::Move(double a, double b) {
    x = a;
    y = b;

}

void Move::showmove() const {
    cout << x << "   " << y << endl;
}
Move Move::add(const Move &m) const {
    Move temp;
    temp.x = x + m.x;
    temp.y = y + m.y;
    return temp;
}
void Move::reset(double a, double b) {
    x = a;
    y = b;
}

int main() {
    Move a{3, 5};
    Move b;
    Move c{1, 1};
    a.showmove();
    b =a.add(c);
    b.showmove();
    return 0;
}
