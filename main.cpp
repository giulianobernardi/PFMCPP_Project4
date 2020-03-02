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
// Forward declarations to be able to use DoubleType and IntType
struct DoubleType;
struct IntType;

// =============================================================
//                  FloatType object definition
// =============================================================
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
    // 4 functions taking a FloatType as input
    FloatType& add(const FloatType& rhsFt );
    FloatType& subtract(const FloatType& rhsFt );
    FloatType& multiply(const FloatType& rhsFt );
    FloatType& divide(const FloatType& rhsFt );
    // 4 functions taking a DoubleType as input
    FloatType& add(const DoubleType& rhsDt );
    FloatType& subtract(const DoubleType& rhsDt );
    FloatType& multiply(const DoubleType& rhsDt );
    FloatType& divide(const DoubleType& rhsDt );
    // 4 functions taking an int as input
    FloatType& add(const IntType& rhsIt );
    FloatType& subtract(const IntType& rhsIt );
    FloatType& multiply(const IntType& rhsIt );
    FloatType& divide(const IntType& rhsIt );
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
//                  DoubleType object definition
// =============================================================
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
    // 4 functions taking a FloatType as input
    DoubleType& add(const FloatType& rhsFt );
    DoubleType& subtract(const FloatType& rhsFt );
    DoubleType& multiply(const FloatType& rhsFt );
    DoubleType& divide(const FloatType& rhsFt );
    // 4 functions taking a DoubleType as input
    DoubleType& add(const DoubleType& rhsDt );
    DoubleType& subtract(const DoubleType& rhsDt );
    DoubleType& multiply(const DoubleType& rhsDt );
    DoubleType& divide(const DoubleType& rhsDt );
    // 4 functions taking an int as input
    DoubleType& add(const IntType& rhsIt );
    DoubleType& subtract(const IntType& rhsIt );
    DoubleType& multiply(const IntType& rhsIt );
    DoubleType& divide(const IntType& rhsIt );
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
//                  IntType object definition
// =============================================================
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
    // 4 functions taking a FloatType as input
    IntType& add(const FloatType& rhsFt );
    IntType& subtract(const FloatType& rhsFt );
    IntType& multiply(const FloatType& rhsFt );
    IntType& divide(const FloatType& rhsFt );
    // 4 functions taking a DoubleType as input
    IntType& add(const DoubleType& rhsDt );
    IntType& subtract(const DoubleType& rhsDt );
    IntType& multiply(const DoubleType& rhsDt );
    IntType& divide(const DoubleType& rhsDt );
    // 4 functions taking an int as input
    IntType& add(const IntType& rhsIt );
    IntType& subtract(const IntType& rhsIt );
    IntType& multiply(const IntType& rhsIt );
    IntType& divide(const IntType& rhsIt );    
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

// =============================================================
//         Functions accepting other UDTs as input types
// =============================================================

// -----------------------FloatType----------------------
// FloatType accepting FloatType
FloatType& FloatType::add(const FloatType& rhsFt)
{
    return add(*rhsFt.value);
}
FloatType& FloatType::subtract(const FloatType& rhsFt)
{
    return subtract(*rhsFt.value);
}
FloatType& FloatType::multiply(const FloatType& rhsFt)
{
    return multiply(*rhsFt.value);
}
FloatType& FloatType::divide(const FloatType& rhsFt)
{
    return divide(*rhsFt.value);
}

// FloatType accepting DoubleType
FloatType& FloatType::add(const DoubleType& rhsDt)
{
    return add(*rhsDt.value);
}
FloatType& FloatType::subtract(const DoubleType& rhsDt)
{
    return subtract(*rhsDt.value);
}
FloatType& FloatType::multiply(const DoubleType& rhsDt)
{
    return multiply(*rhsDt.value);
}
FloatType& FloatType::divide(const DoubleType& rhsDt)
{
    return divide(*rhsDt.value);
}

// FloatType accepting IntType
FloatType& FloatType::add(const IntType& rhsIt)
{
    return add(*rhsIt.value);
}
FloatType& FloatType::subtract(const IntType& rhsIt)
{
    return subtract(*rhsIt.value);
}
FloatType& FloatType::multiply(const IntType& rhsIt)
{
    return multiply(*rhsIt.value);
}
FloatType& FloatType::divide(const IntType& rhsIt)
{
    return divide(*rhsIt.value);
}

// -----------------------DoubleType----------------------
// DoubleType accepting FloatType
DoubleType& DoubleType::add(const FloatType& rhsFt)
{
    return add(*rhsFt.value);
}
DoubleType& DoubleType::subtract(const FloatType& rhsFt)
{
    return subtract(*rhsFt.value);
}
DoubleType& DoubleType::multiply(const FloatType& rhsFt)
{
    return multiply(*rhsFt.value);
}
DoubleType& DoubleType::divide(const FloatType& rhsFt)
{
    return divide(*rhsFt.value);
}

// DoubleType accepting DoubleType
DoubleType& DoubleType::add(const DoubleType& rhsDt)
{
    return add(*rhsDt.value);
}
DoubleType& DoubleType::subtract(const DoubleType& rhsDt)
{
    return subtract(*rhsDt.value);
}
DoubleType& DoubleType::multiply(const DoubleType& rhsDt)
{
    return multiply(*rhsDt.value);
}
DoubleType& DoubleType::divide(const DoubleType& rhsDt)
{
    return divide(*rhsDt.value);
}

// DoubleType accepting IntType
DoubleType& DoubleType::add(const IntType& rhsIt)
{
    return add(*rhsIt.value);
}
DoubleType& DoubleType::subtract(const IntType& rhsIt)
{
    return subtract(*rhsIt.value);
}
DoubleType& DoubleType::multiply(const IntType& rhsIt)
{
    return multiply(*rhsIt.value);
}
DoubleType& DoubleType::divide(const IntType& rhsIt)
{
    return divide(*rhsIt.value);
}


// -----------------------IntType----------------------
// IntType accepting FloatType
IntType& IntType::add(const FloatType& rhsFt)
{
    return add(*rhsFt.value);
}
IntType& IntType::subtract(const FloatType& rhsFt)
{
    return subtract(*rhsFt.value);
}
IntType& IntType::multiply(const FloatType& rhsFt)
{
    return multiply(*rhsFt.value);
}
IntType& IntType::divide(const FloatType& rhsFt)
{
    return divide(*rhsFt.value);
}

// IntType accepting DoubleType
IntType& IntType::add(const DoubleType& rhsDt)
{
    return add(*rhsDt.value);
}
IntType& IntType::subtract(const DoubleType& rhsDt)
{
    return subtract(*rhsDt.value);
}
IntType& IntType::multiply(const DoubleType& rhsDt)
{
    return multiply(*rhsDt.value);
}
IntType& IntType::divide(const DoubleType& rhsDt)
{
    return divide(*rhsDt.value);
}

// IntType accepting IntType
IntType& IntType::add(const IntType& rhsIt)
{
    return add(*rhsIt.value);
}
IntType& IntType::subtract(const IntType& rhsIt)
{
    return subtract(*rhsIt.value);
}
IntType& IntType::multiply(const IntType& rhsIt)
{
    return multiply(*rhsIt.value);
}
IntType& IntType::divide(const IntType& rhsIt)
{
    return divide(*rhsIt.value);
}


// =============================================================
//                              MAIN
// =============================================================

int main()
{
    // FloatType object instanciation and method tests
    FloatType ft (3.0f);
    // --------
    std::cout << "Initial value of ft: " << *(ft.value) << std::endl;
    // --------
    std::cout << "Use of function concatenation (only float arguments) " << std::endl;
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << *(ft.add( 3.0f ).multiply(1.5f).divide(5.0f).value) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    DoubleType dt (5.0);
    IntType it(10);
    // --------
    std::cout << "Initial value of dt: " << *(dt.value) << std::endl;
    std::cout << "Initial value of it: " << *(it.value) << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << *(dt.multiply(it).divide(5.0f).add(ft).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = dt / 0 = " << *(it.divide(0).value) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
}
