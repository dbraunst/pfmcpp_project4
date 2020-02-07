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

struct Point
{
    Point& multiply(float m)
    {
        x *= m;
        y *= m;
        return *this;
    }
private:
    float x{0}, y{0};
};

#include <stdexcept>
#include <iostream>

struct IntType;
struct DoubleType;
 
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

    operator float(){return *value;}

private:
    float* value;
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
    //FIXME THIS LEAKS!!!! Where is your destructor!??!!
    ~DoubleType()
    {
        delete value;
        value = nullptr;
    }

    DoubleType& add(double rhs);
    DoubleType& subtract(double rhs);
    DoubleType& multiply(double rhs);
    DoubleType& divide(double rhs); 

    operator double() { return *value; }

private:
    double* value = nullptr;
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

    operator int(){return *value;}

private:
    int* value = nullptr;
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

#include <iostream>
int main()
{
    DoubleType dt1(3.5);
    DoubleType dt2(3.0);
    DoubleType dt3(-2.5);
    DoubleType dt4(7.2);
    std::cout << "(((3.5 + 3.0) * -2.5) / 7.2) = " << dt1.add(dt2).multiply(dt3).divide(dt4)<< std::endl;
    
    FloatType ft1(1.7f);
    FloatType ft2(3.0f);
    FloatType ft3(2.0f);
    std::cout << ft1 << "f + 3.0f = " << ft1.add(ft2) << "f * 2.0f = ";
    std::cout << ft1.multiply(ft3) << "f.\n";

    IntType it1(6);
    IntType it2(6);
    IntType it3(47);
    std::cout << "(" << it3 << " / 6) * 6 = " << it3.divide(it2).multiply(it1) << std::endl;
}
