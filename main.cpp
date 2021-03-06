/*
Project 4 - Part 6 / 9
Video: Chapter 5 Part 3
 
Create a branch named Part6
 
 Lambdas
 
    Do not delete your previous main. you will be adding to it.

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add two member functions named "apply()" to each of your Heap-Allocated Numeric Type wrappers.
         both apply() functions should work with chaining
 
 2) One of the apply() functions should takes a std::function<> object as the function argument.
    the std::function<> object should return *this;
 
 3) the other apply() function should take a function pointer. 
    the function pointer should return void.
 
 4) Make both of the member functions's Callable Function Parameter use your owned object as it's single parameter.
         e.g. if you manage your owned object via std::unique_ptr<T>, you'd use this for your std::function argument:
             std::function< OwnedT&(std::unique_ptr<T>&)>
             
         if you managed your owned object via a raw pointer, you'd use this for your std::function argument:
             std::function<OwnedT&(T&)>    
 
 5) call that Callable Function Parameter in the apply() member function.
         be sure to practice safe std::function usage (make sure it's not a nullptr function being called)
 
 6) Using one instance of each of your Heap-Allocated Numeric Type wrappers: Call your apply() member function twice in main()
         a) once with a lambda as the argument
         b) once with a free function as the argument.
         c) there will be a total of 6 calls to apply() in main(), 2x per HeapType, IntType, DoubleType instance.
         If this confuses you, rewatch the video where I pass a free function in to a function that wants a function pointer
 
 8) Make your lambda & free function update the value of your held object
 
 9) use std::cout statements to print out the results of calling apply()
 
build/run to make sure you don't have any errors

Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 
 If you need to see an example, look at https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part6Example.cpp
 */






#include <stdexcept>
#include <iostream>
#include <cmath>

struct IntType;
struct DoubleType;
struct FloatType;

struct Point
{
    Point(IntType& _x, IntType& _y);
    Point(FloatType& _x, FloatType& _y);
    Point(DoubleType& _x, DoubleType& _y);

    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
    Point& multiply(const IntType& m);
    Point& multiply(const FloatType& m);
    Point& multiply(const DoubleType& m);

    void toString();
private:
    float x{0}, y{0};
};
 
struct FloatType
{
    FloatType(float);
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }
    
    FloatType& operator+=(float RHS);
    FloatType& operator-=(float RHS);
    FloatType& operator*=(float RHS);
    FloatType& operator/=(float RHS);
    
    FloatType& pow(const FloatType& arg);
    FloatType& pow(const IntType& arg);
    FloatType& pow(const DoubleType& arg);
    FloatType& pow(float arg);

    operator float() const {return *value;}

private:
    float* value;
    FloatType& powInternal(float arg);
};

FloatType::FloatType(float newFloat)
{
    value = new float(newFloat);
}

FloatType& FloatType::operator+=(float RHS)
{
    *value += RHS;
    return *this;
}

FloatType& FloatType::operator-=(float RHS)
{
    *value -= RHS;
    return *this;
}

FloatType& FloatType::operator*=(float RHS)
{
    *value *= RHS;
    return *this;
}

FloatType& FloatType::operator/=(float RHS)
{
    if (RHS == 0.0f)
    {
        std::cout << ("Attempted to divide by Zero\n") << std::endl; 
    }
    *value /= RHS;
    return *this;
}

struct DoubleType
{
    DoubleType(double); 
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& operator+=(double RHS);
    DoubleType& operator-=(double RHS);
    DoubleType& operator*=(double RHS);
    DoubleType& operator/=(double RHS);

    DoubleType& pow(const DoubleType& arg);
    DoubleType& pow(const FloatType& arg);
    DoubleType& pow(const IntType& arg);
    DoubleType& pow(double arg);

    operator double() const { return *value; }

private:
    double* value = nullptr;
    DoubleType& powInternal(double arg);
};

DoubleType::DoubleType(double newDouble)
{
    value = new double(newDouble);    
}

DoubleType& DoubleType::operator+=(double RHS)
{
    *value += RHS;
    return *this;
}

DoubleType& DoubleType::operator-=(double RHS)
{
    *value -= RHS;
    return *this;
}

DoubleType& DoubleType::operator*=(double RHS)
{
    *value *= RHS;
    return *this;
}

DoubleType& DoubleType::operator/=(double RHS)
{
    if (RHS == 0.0)
    {
        std::cout << "Trying to divide by 0" << std::endl; 
    }
    *value /= RHS;
    return *this;
}

struct IntType
{
    IntType(int);
    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& operator+=(int RHS);
    IntType& operator-=(int RHS);
    IntType& operator*=(int RHS);
    IntType& operator/=(int RHS);

    IntType& pow(const IntType& arg);
    IntType& pow(const DoubleType& arg);
    IntType& pow(const FloatType& arg);
    IntType& pow(int arg); 

    operator int() const {return *value;}

private:
    int* value = nullptr;
    IntType& powInternal(int arg);
};

IntType::IntType(int newInt)
{
    value = new int(newInt);
}

IntType& IntType::operator+=(int RHS)
{
    *value += RHS;
    return *this;
}

IntType& IntType::operator-=(int RHS)
{
    *value -= RHS;
    return *this;
}

IntType& IntType::operator*=(int RHS)
{
    *value *= RHS;
    return *this;
}

IntType& IntType::operator/=(int RHS)
{
    if (RHS != 0)
    {
        *value /= RHS;
    }
    else 
    {
        std::cout << "Math Error: Tried to Divide by zero!" << std::endl; 
    }

    return *this;
}


//POW Function Implementations
FloatType& FloatType::powInternal(float arg)
{
    *value = std::pow(*value, arg);
    return *this;
}

FloatType& FloatType::pow(float arg)
{
    return powInternal(arg);
}

FloatType& FloatType::pow(const IntType& arg)
{
    return powInternal(static_cast<float>(arg));
}

FloatType& FloatType::pow(const DoubleType& arg)
{
    return powInternal(static_cast<float>(arg));
}

FloatType& FloatType::pow(const FloatType& arg)
{
    return powInternal(arg);
}

DoubleType& DoubleType::powInternal(double arg)
{
    *value = std::pow(*value, arg);
    return *this;
}

DoubleType& DoubleType::pow(const DoubleType& arg)
{
    return powInternal(arg);
}

DoubleType& DoubleType::pow(const FloatType& arg)
{
    return (powInternal(static_cast<double>(arg)));
}

DoubleType& DoubleType::pow(const IntType& arg)
{
    return (powInternal(static_cast<double>(arg)));
}

DoubleType& DoubleType::pow(double arg)
{
    powInternal(arg);
    return *this;
}

IntType& IntType::powInternal(int arg)
{
    *value = static_cast<int>(std::pow(*value, arg));
    return *this;
}

IntType& IntType::pow(const IntType& arg)
{
    powInternal(arg);
    return *this;
}

IntType& IntType::pow(const DoubleType& arg)
{
    return (powInternal(static_cast<int>(arg)));
}

IntType& IntType::pow(const FloatType& arg)
{
    return (powInternal(static_cast<int>(arg)));
}

IntType& IntType::pow(int arg)
{
    return powInternal(arg);
}

//Point Constructors
Point::Point(FloatType& _x, FloatType& _y) : x(_x), y(_y) {}

Point::Point(IntType& _x, IntType& _y)
{
    x = static_cast<float>(_x);
    y = static_cast<float>(_y);
}
Point::Point(DoubleType& _x, DoubleType& _y)
{
    x = static_cast<float>(_x);
    y = static_cast<float>(_y);
}

//Point Implementations
Point& Point::multiply(const IntType& m)
{
    return multiply(static_cast<float>(m));
}
Point& Point::multiply(const FloatType& m)
{
    return multiply(static_cast<float>(m));
}
Point& Point::multiply(const DoubleType& m)
{
    return multiply(static_cast<float>(m));
}

void Point::toString()
{
    std::cout << "X: " << x << ", Y:" << y << std::endl;
}

#include <iostream>
int main()
{   
    DoubleType dt1(3.5);
    DoubleType dt2(3.0);
    DoubleType dt3(-2.5);
    DoubleType dt4(7.2);
    dt1 /= dt2;
    dt3 *= dt4;
    std::cout << "dt1: " << dt1 << " dt2: " << dt2 << std::endl;
    
    FloatType ft1(1.7f);
    FloatType ft2(3.0f);
    FloatType ft3(2.0f);
    ft1 -= 2.0f;
    ft2 /= ft3;
    std::cout << "ft1:  " << ft1 << " ft2: " << ft2 << std::endl;

    IntType it1(6);
    IntType it2(6);
    IntType it3(47);
    it1 *= it2;
    it3 += -25;
    std::cout << "it1: " << it1 << " it3: " << it3 << std::endl;

    dt3 += it1;
    std::cout << "dt3 += it1: " << dt3 << std::endl;
    ft1 /= static_cast<float>(dt2);
    std::cout << "ft1 /= dt2: " << ft1 << std::endl;
    it3 *= static_cast<int>(ft2);
    std::cout << "it3 *= ft2: " << it3 << std::endl;
} 
