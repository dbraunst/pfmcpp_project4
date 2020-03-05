
/*
Project 4: Part 4 / 9
 Chapter 4 Part 7
 Function/Constructor Overloading

 Create a branch named Part4

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 1) add pow() functions, and a powInternal() function to each of your UDTs
     a) your pow() functions should call powInternal()
     b) add a pow() whose argument type is the primitive your UDT owns.  the argument should be passed by copy.
     c) for each UDT in the file, your class should have pow() overloads that take that UDT as the function argument.
         the argument should be passed as const ref
         i.e. if you had UDTs named IntType, FloatType, DoubleType
             in your IntType class, you'd have:
                 pow(const IntType&),
                 pow(const FloatType&),
                 pow(const DoubleType&),
                 and pow(int)
     d) be sure to remember the rules about what member functions can be called on const objects.
             (const objects can only call their const member functions)
 
 2) your powInternal() function should do something like this in its body:    *val = std::pow( *val, arg );
         where 'arg' is the passed-in type, converted to whatever type your object is holding.
             if your UDT owns an int, then arg would be an int.
             if your UDT owns a float, then arg would be a float.
         std::pow's documentation is found here: https://en.cppreference.com/w/cpp/numeric/math/pow so be sure to include
             the proper header file listed there.
 
 3) modify the Point class below to have Constructors that accept your UDTs.
     a) make the Constructor's UDT arguments initialize the Point class's two member variables.
     b) overload the multiply() function so it can accept each of your UDTs.  I've added an implementation you can mimick for this function.
     c) add a toString() function to the Point class that prints out the x and y members via std::cout.
 
 4) clear out your old main()
     a) use your new pow() function in main for all of your types and print out the results.
     b) use the Point class in main and multiply some Point instances with your UDTs
     c) use the Point::toString() function to print out the results.
 
 
 5) make sure it compiles without errors.
 
 You will need to use Forward Declaration and out-of-class definitions to complete this.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

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
    //FIXME THIS LEAKS!!!! Where is your destructor!??!!
    ~FloatType()
    {
        delete value;
        value = nullptr;
    }

    FloatType& add(float rhs);
    FloatType& subtract(float rhs);
    FloatType& multiply(float rhs);
    FloatType& divide(float rhs);
    
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
    DoubleType(double); 
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs); 

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
    IntType(int); 
    //FIXME THIS LEAKS!!!! Where is your destructor!??!!
    ~IntType()
    {
        delete value;
        value = nullptr;
    }

    IntType& add(int rhs);
    IntType& subtract(int rhs);
    IntType& multiply(int rhs);
    IntType& divide(int rhs);

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

//POW Function Implementations

FloatType& FloatType::powInternal(float arg)
{
    *value = std::pow(*value, arg);
    return *this;
}

FloatType& FloatType::pow(float arg)
{
    powInternal(arg);
    return *this;
}

FloatType& FloatType::pow(const IntType& arg)
{
    powInternal(static_cast<float>(arg));
    return *this;
}

FloatType& FloatType::pow(const DoubleType& arg)
{
    powInternal(static_cast<float>(arg));
    return *this;
}

FloatType& FloatType::pow(const FloatType& arg)
{
    powInternal(arg);
    return *this;
}

DoubleType& DoubleType::powInternal(double arg)
{
    *value = std::pow(*value, arg);
    return *this;
}

DoubleType& DoubleType::pow(const DoubleType& arg)
{
    powInternal(arg);
    return *this;
}

DoubleType& DoubleType::pow(const FloatType& arg)
{
    powInternal(static_cast<double>(arg));
    return *this;
}

DoubleType& DoubleType::pow(const IntType& arg)
{
    powInternal(static_cast<double>(arg));
    return *this;
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
    powInternal(static_cast<int>(arg));
    return *this;
}

IntType& IntType::pow(const FloatType& arg)
{
    powInternal(static_cast<int>(arg));
    return *this;
}

IntType& IntType::pow(int arg)
{
    powInternal(arg);
    return *this;
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

//multiply
Point& Point::multiply(const IntType& m)
{
    x *= m;
    y *= m;
    return *this;
}
Point& Point::multiply(const FloatType& m)
{
    x *= m;
    y *= m;
    return *this;
}
Point& Point::multiply(const DoubleType& m)
{
    x *= static_cast<float>(m);
    y *= static_cast<float>(m);
    return *this;
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
    
    FloatType ft1(1.7f);
    FloatType ft2(3.2f);

    IntType it1(6);
    IntType it2(4);

    std::cout << "6 ^ 3.0: " << it1.pow(dt2) << std::endl;
    std::cout << "1.7f ^ 3.5: " << ft1.pow(dt1) << std::endl;
    std::cout << "4 ^ 3.2f: " << it2.pow(ft2) << std::endl;
}
