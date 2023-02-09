#include <iostream>
#include <string>
#include <vector>
#include "efficient_swap.h"

using namespace std;

class Impl
{
public:
    vector<int> arr;

    explicit Impl(const vector<int> _arr): arr(_arr) {}
};

class Base
{
private:
    const Impl* pimpl;

public:
    explicit Base(const Impl& impl): pimpl(&impl) {}

    void print()
    {
        cout << endl << "[";
        for (vector<int>::const_iterator it = pimpl->arr.begin(); it != pimpl->arr.end(); ++it)
        {
            cout << *it << ", ";
        }
        cout << "]" << endl;
    }

    void swap(Base& other)
    {
        std::swap(other.pimpl, pimpl);
    }
};

namespace wh 
{
    void swap(Base& obj1, Base& obj2)
    {
        obj1.swap(obj2);
    }
}

using namespace wh;

namespace efficient_swap
{
    void run()
    {
        vector<int> arr1 = {1, 2, 3};
        Impl impl1 = Impl(arr1);
        vector<int> arr2 = {4, 5, 6};
        Impl impl2 = Impl(arr2);

        Base b1 = Base(impl1);
        Base b2 = Base(impl2);

        b1.print();
        b2.print();

        swap(b1, b2);

        cout << string(79, '*') << endl;
        b1.print();
        b2.print();
    }
}
