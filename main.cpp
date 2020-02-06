/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 ******* Create a branch named Part2 ********

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

struct A {};

struct HeapA{
    
    HeapA(A* newA) : a (newA){}
    ~HeapA() 
    {
        delete a;
        a = nullptr;
    }

    A* a = nullptr;
};

 /*
 1) Edit your 3 structs so that they own a heap-allocated primitive type without using smart pointers  
         IntType should own a heap-allocated int, for example.
 
 2) give it a constructor that takes the appropriate primitive
    this argument will initialize the owned primitive's value.
         i.e. if you're owning an int on the heap, your ctor argument will initialize that heap-allocated int's value.
 
 3) modify those add/subtract/divide/multiply member functions from chapter 2 on it
         a) make them modify the owned numeric type
         b) set them up so they can be chained together.
             i.e.
             DoubleType dt(3.5);
             dt.add(3.0).multiply(-2.5).divide(7.2); //an example of chaining
 
 4) write some add/subtract/divide/multiply member functions for each type that take your 3 UDTs
         for example, IntType::divide(const DoubleType& dt);
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */


#include <stdexcept>
#include <iostream>

struct IntType;
struct DoubleType;
 
struct FloatType
{
    FloatType(float newFloat) : value (new float(newFloat)) {}
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& multiply(const IntType& it);
    FloatType& multiply(const DoubleType& dt);
    FloatType& divide(float rhs);

    float* value = nullptr;
};

FloatType& FloatType::add(float rhs)
{
    *value += rhs;
    return *this;
}

FloatType& FloatType::subtract(float rhs)
{
    *value -= rhs;
    return *this;
}

FloatType& FloatType::multiply(float rhs)
{
    *value *= rhs;
    return *this;
}

FloatType& FloatType::divide(float rhs)
{
    if (rhs == 0.0f)
    {
        std::cout << ("Attempted to divide by Zero\n") << std::endl; 
    }
    *value /= rhs;
    return *this;
}

struct DoubleType
{
    DoubleType(double newDouble) : value (new double(newDouble)){}
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    double* value = nullptr;

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs); 
    DoubleType& divide(const FloatType& ft);
    DoubleType& divide(const IntType& it); 
};

DoubleType& DoubleType::add(double rhs)
{
    *value += rhs;
    return *this;
}

DoubleType& DoubleType::subtract(double rhs)
{
    *value -= rhs;
    return *this;
}

DoubleType& DoubleType::multiply(double rhs)
{
    *value *= rhs;
    return *this;
}

DoubleType& DoubleType::divide(double rhs)
{
    if (rhs == 0.0)
    {
        std::cout << "Trying to divide by 0" << std::endl; 
    }
    
    *value /= rhs;
    return *this;
}

struct IntType
{
    IntType(int newInt) : value (new int(newInt)) {}
    ~IntType()
    {
        delete value;   
    }
  
    int* value = nullptr; 
    
    IntType& add(int rhs);
    IntType& add(const DoubleType& dt);
    IntType& add(const FloatType& ft);
    IntType& subtract(int rhs);
    IntType& multiply(int rhs);
    IntType& divide(int rhs);
};

IntType& IntType::add(int rhs)
{
    *value += rhs;
    return *this;
}

IntType& IntType::subtract(int rhs)
{
    *value -= rhs;
    return *this;
}

IntType& IntType::multiply(int rhs)
{
    *value *= rhs;
    return *this;
}

IntType& IntType::divide(int rhs)
{
    if (rhs != 0)
    {
        *value /= rhs;
    }
    else 
    {
        std::cout << "Math Error: Tried to Divide by zero!" << std::endl; 
    }
    
    return *this;
}

IntType& IntType::add(const DoubleType& dt)
{
    *value += *dt.value;
    return *this;
}
IntType& IntType::add(const FloatType& ft)
{
    *value += *ft.value;
    return *this;
}

FloatType& FloatType::multiply(const IntType& it)
{
    *value *= *it.value;
    return *this;
}
FloatType& FloatType::multiply(const DoubleType& dt)
{
    *value *= *dt.value;
    return *this;
}

DoubleType& DoubleType::divide(const FloatType& ft) 
{
    if (*ft.value == 0.f)
    {
        std::cout << ("Math error: Attempted to divide by Zero\n") << std::endl;
    }
    
    *value /= *ft.value;
    return *this;
}
DoubleType& DoubleType::divide(const IntType& it) 
{
    if (*it.value == 0)
    {
        std::cout << ("Math error: Attempted to divide by Zero\n") << std::endl;
    }
    
    *value /= *it.value;
    return *this;
}


#include <iostream>
int main()
{
    DoubleType dt(3.5);
    dt.add(3.0).multiply(-2.5).divide(7.2);
    std::cout << *dt.value << std::endl;
    
    FloatType ft(1.7f);
    std::cout << *ft.value << "f + 3.0 = ";
    ft.add(3.0);
    std::cout << *ft.value << " + 2 = ";
    ft.add(2);
    std::cout << *ft.value << std::endl;
    
    DoubleType dt1(18.6), dt2(18.6);
    IntType it1(6);
    FloatType ft2(6.f);
    std::cout << "Fun with multiple primitive types! A double of 18.6 can be divided by int or floats!\n";
    std::cout << "By int (6): " << *dt1.divide(it1).value << ".\nBy float (6.f): " << *dt2.divide(ft2).value << std::endl;
}
