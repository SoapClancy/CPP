#include "big3.h"
#include <string>
#include <iostream>

using namespace std;

class Impl
{
public:
    string val;

    Impl(string val): val(val) {}
};

class Base
{
public:
    Impl *pimpl;

    Base(Impl* pimpl): pimpl(pimpl) {}

    void print()
    {
        cout << pimpl->val << endl;
    } 
};

void big3::run()
{
    Impl impl1("1");
    Impl impl2("2");

    Base b1(&impl1);
    b1.print();

    Base b2(b1);
    b2.print();

    cout << b1.pimpl << endl;
    cout << b2.pimpl << endl;

    cout << &b1.pimpl << endl;
    cout << &b2.pimpl << endl;

    b2.pimpl->val = "2";
    b1.print();
    b2.print();
}