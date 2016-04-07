#include "include/parser.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    list<Border> lst = parseFile("../test.txt");

    for (Border b: lst) {
        cout << '(' << b.first.x << ", " << b.first.y << ") " <<
                '(' << b.first.x << ", " << b.first.y << ") " <<
                b.u << endl;
    }

    return 0;
}

