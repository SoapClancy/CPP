#include <iostream>
#include "utils.h"
#include <string>
#include <exception>
#include <vector>
#include "rvo.h"

using namespace std;

// https://stackoverflow.com/questions/10476665/avoiding-copy-of-objects-with-the-return-statement
namespace RVO
{
    class Base
    {
    public:
        string name;

        Base(string _name) : name(_name)
        {
            cout << "ctr called for " << name << endl;
        }

        Base(const Base &other) : name(other.name)
        {
            cout << "Copy ctr called for " << name << endl;
        }

        Base &operator=(const Base &other)
        {
            cout << "Assign " << other.name << " to " << name << endl;
            name = other.name;

            return *this;
        }

        ~Base()
        {
            cout << "destr called for " << name << endl;
        }
    };

    void func1(string name)
    {
        Base b = Base(name);
    }

    void func2(string name)
    {
        Base *b = new Base(name);
    }

    Base func3(string name)
    {
        Base b = Base(name);
        cout << "To return from func3..." << endl;
        return b;
    }

    /* Compile warning.
    Runtime error can happen - segmentation fault
    Base& func4(string name)
    {
        Base b = Base(name);
        cout << "To return from func4..." << endl;
        return b;
    }
    */

    Base func5(string name)
    {
        cout << "To return from func5..." << endl;
        return Base(name);
    }

    /* Compile error: 'return': cannot convert from 'Base' to 'Base &'
    Base& func6(string name)
    {
        cout << "To return from func6..." << endl;
        return Base(name);
    }
    */

    Base *func7(string name)
    {
        Base *b = new Base(name);
        cout << "To return from func7..." << endl;
        return b;
    }

    Base *func8(string name)
    {
        cout << "To return from func8..." << endl;
        return new Base(name);
    }

    void test()
    {
        cout << endl
             << std::string(30, '*') << "func1" << std::string(30, '*') << endl;
        func1("obj1");
        cout << endl
             << std::string(30, '*') << "func2" << std::string(30, '*') << endl;
        func2("obj2");

        cout << endl
             << std::string(30, '*') << "func3 - assign" << std::string(30, '*') << endl;
        Base tmp = Base("tmp");
        tmp = func3("obj3");

        cout << endl
             << std::string(30, '*') << "func3 - constructor" << std::string(30, '*') << endl;
        Base obj3 = func3("obj3");

        cout << endl
             << std::string(30, '*') << "func5 - assign" << std::string(30, '*') << endl;
        tmp = Base("tmp2");
        tmp = func5("obj5");

        cout << endl
             << std::string(30, '*') << "func5 - constructor" << std::string(30, '*') << endl;
        Base obj5 = func5("obj5");

        cout << endl
             << std::string(30, '*') << "func7 - assign" << std::string(30, '*') << endl;
        Base *ptmp = nullptr; // If here write new Base("ptmp"), not sure whether memo leak will occur
        ptmp = func7("obj7");
        cout << "call delete" << endl;
        delete ptmp;

        cout << endl
             << std::string(30, '*') << "func7 - constructor" << std::string(30, '*') << endl;
        Base *obj7 = func7("obj7");
        cout << "call delete" << endl;
        delete obj7;

        cout << endl
             << std::string(30, '*') << "func8 - assign" << std::string(30, '*') << endl;
        ptmp = nullptr; // If here write new Base("ptmp"), not sure whether memo leak will occur
        ptmp = func8("obj8");
        cout << "call delete" << endl;
        delete ptmp;

        cout << endl
             << std::string(30, '*') << "func8 - constructor" << std::string(30, '*') << endl;
        Base *obj8 = func8("obj8");
        cout << "call delete" << endl;
        delete obj8;
    }
}