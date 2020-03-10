
#include <iostream>
/*
Project 4: Part 5 / 9
 video: Chapter 5 Part 2
 Operator Overloading.

Do not delete your previous main. 

 Create a branch named Part5

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) replace the add/subtract/multiply/etc functions with overloaded math operators 
        e.g. add() would become operator+=() because it modifies the internal heap-allocated object.
 
 2) Your overloaded operators should only take primitives, passed by value.
 
 3) don't delete your conversion functions.
         if you removed them in Chapter 4 Part 7, put them back in.
         uncomment them if you commented them in Chapter 4 Part 7
 
 4) your main() function should be the same as Chapter 4 Part 7.  
     
 5) if your Chapter4 Part7 task didn't use any [+ - * or /], 
         add some in and fix the build errors that might result via the techniques you have learned in the previous weeks (hint: casting)
         i.e.
 */
/*#if false
namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

         
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 

        it should become:
        
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif*/
 /*
 6) compile/link/run to make sure you don't have any errors
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
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
