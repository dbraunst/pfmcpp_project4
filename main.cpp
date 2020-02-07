/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.

 1) remove your functions that accepted a User-Defined Type
 
 2) remove any getValue() functions if you added them
 
 3) move all of your add/subtract/multiply/divide implementations out of the class.
  
 4) add user-defined conversion functions that convert to the numeric type your object holds.
        i.e. if your type holds an int, you'll need an operator int() function.
 
 5) make your member variable private.
         this conversion function should be the ONLY WAY to access the held value.
 
 6) clean up any forward declaration that you might have.
 
 7) make sure it compiles & runs without errors.
 
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
    FloatType(float); 
    //FIXME THIS LEAKS!!!! Where is your destructor!??!!
    ~FloatType(){
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
    ~DoubleType(){
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
    ~IntType(){
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
