#include "include/parser.h"

#include <iostream>

using namespace std;

int main()
{
    list<Border> lst = parseFile("../test.txt");

    for (Border b: lst) {
        cout << b << endl;
    }

    return 0;
}

