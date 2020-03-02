/*
 Project 4 - Part 2 / 9
 Video: Chapter 3 Part 6

 Create a branch named Part2

New/This/Pointers/References conclusion

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
 
 0) in the blank space below, declare/define an empty struct named 'A' on a single Line. 
     on the lines below it, write a struct named 'HeapA' that correctly shows how to own an instance of 'A' 
         on the heap without leaking, without using smart pointers. 
 */

struct A {};

struct HeapA
{
    A* varA;
    HeapA() : varA( new A() ) {}
    ~HeapA()
    { 
        delete varA; 
        varA = nullptr;
    }
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
 
 4) write add/subtract/divide/multiply member functions for each type that take your 3 UDTs
        These are in addition to your member functions that take primitives
        for example, IntType::divide(const DoubleType& dt);
 
 5) print out the results with some creative couts 
    i.e.
         FloatType ft(0.1f);
         IntType it(3);
         std::cout << "adding 3 and subtracting 'it' from 'ft' results in the following value: " << *ft.add(2.f).subtract( it ).value << std::endl;  //note the dereference of the `value` member of `ft`
 
 6) Don't let your heap-allocated owned type leak!
 
 7) click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */



#include <iostream>
// FloatType object definition
struct FloatType
{
    float* value;
    FloatType(float value_) : value( new float(value_) ) {}
    ~FloatType()
    { 
        delete value; 
        value = nullptr;
    }
    // 4 functions taking a float as input
    FloatType& add(float rhs );
    FloatType& subtract(float rhs );
    FloatType& multiply(float rhs );
    FloatType& divide(float rhs );
    // // 4 functions taking a FloatType as input
    // FloatType& add(const FloatType& rhs );
    // FloatType& subtract(const FloatType& rhs );
    // FloatType& multiply(const FloatType& rhs );
    // FloatType& divide(const FloatType& rhs );
    // // 4 functions taking a DoubleType as input
    // FloatType& add(const DoubleType& rhs );
    // FloatType& subtract(const DoubleType& rhs );
    // FloatType& multiply(const DoubleType& rhs );
    // FloatType& divide(const DoubleType& rhs );
    // // 4 functions taking an int as input
}; 

// 4 functions taking a float as input
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
    *value /= rhs;
    return *this;
}

// =============================================================
// DoubleType object definition
struct DoubleType
{
    double* value;
    DoubleType(double value_) : value( new double(value_) ) {}
    ~DoubleType()
    { 
        delete value; 
        value = nullptr;
    }
    // 4 functions taking a double as input
    DoubleType& add(double rhs );
    DoubleType& subtract(double rhs );
    DoubleType& multiply(double rhs );
    DoubleType& divide(double rhs );
}; 

// 4 functions taking a double as input
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
    *value /= rhs;
    return *this;
}
// =============================================================
// IntType object definition
struct IntType
{
    int* value;
    IntType(int value_) : value( new int(value_) ) {}
    ~IntType()
    { 
        delete value; 
        value = nullptr;
    }
    // 4 functions taking an int as input
    IntType& add( int rhs );
    IntType& subtract( int rhs );
    IntType& multiply( int rhs );
    IntType& divide( int rhs );
}; 
// 4 functions taking an int as input
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
    if( rhs != 0 )
        *value /= rhs;
    else    
        std::cout << "division by zero not allowed with integers" << std::endl;
    return *this;
}

// // Functions taking other UDTs as inpu   t
// FloatType& FloatType::add(const DoubleType& rhs)
// {
//     *value += rhs;
//     return *this;
// }
// FloatType& FloatType::subtract(const DoubleType& rhs)
// {
//     *value -= rhs;
//     return *this;
// }
// FloatType& FloatType::multiply(const DoubleType& rhs)
// {
//     *value *= rhs;
//     return *this;
// }
// FloatType& FloatType::divide(const DoubleType& rhs)
// {
//     *value /= rhs;
//     return *this;
// }

// =============================================================
//                              MAIN
// =============================================================

int main()
{
    // FloatType object instanciation and method tests
    FloatType ft (3.2f);
    float secondFloatArg = 23.f;
    // --------
    std::cout << "First float argument: " << *(ft.value) << std::endl;
    std::cout << "Second float argument: " << secondFloatArg << std::endl;
    // --------
    std::cout << "result of ft.add(): " << *(ft.add( secondFloatArg ).value) << std::endl;
    std::cout << "result of ft.subtract(): " << *(ft.subtract( secondFloatArg ).value) << std::endl;
    std::cout << "result of ft.multiply(): " << *(ft.multiply( secondFloatArg ).value) << std::endl;
    std::cout << "result of ft.divide(): " << *(ft.divide( secondFloatArg ).value) << std::endl; 
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType object instanciation and method tests
    DoubleType dt (3.2);
    double secondDoubleArg = 23.;
    // --------
    std::cout << "First double argument: " << *(dt.value) << std::endl;
    std::cout << "Second double argument: " << secondDoubleArg << std::endl;   
    // -------- 
    std::cout << "result of dt.add(): " << *(dt.add( secondDoubleArg ).value) << std::endl;
    std::cout << "result of dt.subtract(): " << *(dt.subtract( secondDoubleArg ).value) << std::endl;
    std::cout << "result of dt.multiply(): " << *(dt.multiply( secondDoubleArg ).value) << std::endl;
    std::cout << "result of dt.divide(): " << *(dt.divide( secondDoubleArg ).value) << std::endl; 

    std::cout << "---------------------\n" << std::endl; 

    // IntType object instanciation and method tests
    IntType it(3);
    int secondIntArg = 0;
    // --------
    std::cout << "First int argument: " << *(it.value) << std::endl;
    std::cout << "Second int argument: " << secondIntArg << std::endl;   
    // --------     
    std::cout << "result of it.add(): " << *(it.add( secondIntArg ).value) << std::endl;
    std::cout << "result of it.subtract(): " << *(it.subtract( secondIntArg ).value) << std::endl;
    std::cout << "result of it.multiply(): " << *(it.multiply( secondIntArg ).value) << std::endl;
    std::cout << "result of it.divide(): " << *(it.divide( secondIntArg ).value) << std::endl;           
}
