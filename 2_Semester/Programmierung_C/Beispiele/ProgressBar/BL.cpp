#include <iostream>
using namespace std;

class A
{
public:
    virtual void f()  { cout << "A::f\n"; }
};
class B : public A
{
public:
    virtual void f()  { cout << "B::f\n"; }
};
class C : public B
{
public:
    virtual void f()  { cout << "C::f\n"; }
};
int main()
{
    C c;
    A& ra = c;
    B& rb = c;
    C& rc = c;
    ra.f(); // => A::f
    rb.f(); // => B::f
    rc.f(); // => C::f
}