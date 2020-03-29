/*
Prject 4: Part 8 / 9
 video: Chapter 5 Part 6 Task 

Create a branch named Part8

 R-Values L-Values Move Semantics.

 This Task is going to demonstrate R-Values and writing Generic Code

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 
 
 Edit your Chapter 5 Part 4 Task and replace its instructions with these instructions
 
 Your job is to replace the owned type (the primitive specified by your template argument) from the 
     Templated Class you created in Ch5 p04 with a struct named Temporary that can behave ENTIRELY as a temporary object.
 
 That means you must use conversion functions to interact with what it owns.
 
 You need to figure out how to use conversion functions to be able to GET and SET the 'value' member variable.
    hint: conversion functions can return by value and also by ___...
  
 1) Here is a starting point for how to implement your Temporary struct.
 */

#include <typeinfo>
template<typename NumericType>
struct Temporary
{
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }
    /*
     revise these conversion functions to read/write to 'v' here
     hint: what qualifier do read-only functions usually have?
     */
    operator ___() { /* read-only function */ }
    operator ___() { /* read/write function */ }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
namespace example
{
template<typename NumericType>
struct Numeric
{
    //snip
    template<typename OtherType>
    Numeric& operator-=(const OtherType& o) 
    { 
        *value -= static_cast<NumericType>(o); 
        return *this; 
    }
    //snip
};
}

/*
 4) remove your specialized <double> template of your Numeric<T> class from the previous task (ch5 p04)
    replace the 2 apply() functions in your Numeric<T> with the single templated apply() function from the specialized <double> template.
 */

/*
 5) Template your pow() function the same way you templated the overloaded math operators
    Remove the call to powInternal() and just call std::pow() directly.
    you'll need to static_cast<> the pow() argument the same way you did in the overloaded math operators, when you pass it to std::pow()
 */
/*
 
 6) Finally, your conversion function in your templated class is going to be returning this Temporary, 
        so you should probably NOT return by copy if you want your templated class's owned object to be modified by any math operation.
    See the previous hint for implementing the conversion functions for the Temporary if you want to get the held value
*/


/*
 7)   replace main() with the main below

 If you did everything correctly, this is the output you should get:
 
I'm a Temporary<f> object, #0
I'm a Temporary<i> object, #0
I'm a Temporary<d> object, #0
f: -1.89
d: -3.024
i: -9
Point { x: -1.89, y: -9 }
d: 3.024
I'm a Temporary<d> object, #1
I'm a Temporary<d> object, #2
d: 1.49519e+08
Point { x: -2.82591e+08, y: -1.34567e+09 }
I'm a Temporary<f> object, #1
I'm a Temporary<i> object, #1
I'm a Temporary<i> object, #2
I'm a Temporary<i> object, #3
intNum: 5
I'm a Temporary<f> object, #2
f squared: 3.5721
I'm a Temporary<f> object, #3
f cubed: 45.5796
I'm a Temporary<d> object, #3
d squared: 2.2356e+16
I'm a Temporary<d> object, #4
d cubed: 1.11733e+49
I'm a Temporary<i> object, #4
i squared: 81
I'm a Temporary<i> object, #5
i cubed: 531441

Use a service like https://www.diffchecker.com/diff to compare your output. 

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
*/

#include <iostream>
int main()
{
    Numeric<float> f(0.1f);
    Numeric<int> i(3);
    Numeric<double> d(4.2);
    
    f += 2.f;
    f -= i;
    f *= d;
    f /= 2.f;
    std::cout << "f: " << f << std::endl;
    
    d += 2.f;
    d -= i;
    d *= f;
    d /= 2.f;
    std::cout << "d: " << d << std::endl;
    
    i += 2.f; i -= f; i *= d; i /= 2.f;
    std::cout << "i: "<< i << std::endl;
    
    Point p(f, i);
    p.toString();
    
    d *= -1;
    std::cout << "d: " << d << std::endl;
    
    p.multiply(d.pow(f).pow(i));
    std::cout << "d: " << d << std::endl;
    
    p.toString();
    
    Numeric<float> floatNum(4.3f);
    Numeric<int> intNum(2);
    Numeric<int> intNum2(6);
    intNum = 2 + (intNum2 - 4) + floatNum / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f)::Type;
        f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d)::Type;
        d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i)::Type;
        i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type> );
        std::cout << "i cubed: " << i << std::endl;
    }
}






#include <iostream>
#include <cmath>
#include <functional>

// Forward declare the 3 UDT
struct FloatType;
struct DoubleType;
struct IntType;

struct Point
{
    Point(float, float);
    Point& multiply(const FloatType& ftm);
    Point& multiply(const DoubleType& dtm);
    Point& multiply(const IntType& itm);
    Point& multiply(float m);
    void toString();
private:
    float x{0}, y{0};
};

// =============================================================
//                  Numeric object definition
// =============================================================
template <typename TemplatedType> 
struct Numeric
{
public:    

    using CurrentType = TemplatedType;
    
    Numeric(CurrentType value_) : value( new CurrentType(value_) ) {}
    // Operator overloading
    Numeric& operator+=(CurrentType rhs)
    {
        *value += rhs;
        return *this;
    }
    Numeric& operator-=(CurrentType rhs)
    {
        *value -= rhs;
        return *this;
    }
    Numeric& operator*=(CurrentType rhs)
    {
        *value *= rhs;
        return *this;
    }
       
    Numeric& operator /= (const CurrentType& rhs)
    {
        if constexpr ( std::is_same<int, CurrentType>::value ) 
        {
            if( rhs == 0 )
            {
                std::cout << "Division by zero not allowed with integers!!" << std::endl;
                return *this;
            }
        }
        else if( std::abs(rhs) <= std::numeric_limits<CurrentType>::epsilon() )
        {
            std::cout << "Warning: Floating point division by zero!" << std::endl;
        }

        *value /= rhs;
        return *this;
    }
    // 4 power functions with different exponent type
    Numeric& powInternal(const CurrentType exp)
    {
        *value = static_cast<CurrentType>(std::pow(*value, exp));
        return *this;
    }
    Numeric& pow(const CurrentType exp)
    {
        return powInternal(exp);
    }
    // This is necessary for when I call pow from an object of a given Numeric type with an argument of a different Numeric type; otherwise it would give me some conversion warnings
    template<typename DifferentTemplatedType> 
    Numeric& pow(const DifferentTemplatedType& nExp)
    {
        return powInternal(static_cast<CurrentType>(nExp));
    }
    // convert UDT to primitive type
    operator CurrentType() const { return *value; }
    // 
    Numeric& apply(std::function<Numeric&(std::unique_ptr<CurrentType>&)> myFunc)
    {
        std::cout << "--->Numeric as a return type" << std::endl;
        if( myFunc )    
            return myFunc(value);
        return *this;
    }    
    Numeric& apply(void(*myFunc)(std::unique_ptr<CurrentType>&))
    {
        std::cout << "--->Void as a return type" << std::endl;
        if( myFunc )
            myFunc(value);
        return *this;
    }
private:
    std::unique_ptr<CurrentType> value; // #1)    
}; 
// Definition of the (void) templated free functions
template<typename CurrentType>
void myNumericFreeFunct(std::unique_ptr<CurrentType>& value)
{
    *value += static_cast<CurrentType>(7.0); // Now value is a (reference to a) unique pointer  => must be dereferenced
}

// =============================================================
//        Template specialization of Numeric for double
// =============================================================
template <> 
struct Numeric<double>
{
public:    

    using CurrentType = double;
    
    Numeric(CurrentType value_) : value( new CurrentType(value_) ) {}
    // Operator overloading
    Numeric& operator+=(CurrentType rhs)
    {
        *value += rhs;
        return *this;
    }
    Numeric& operator-=(CurrentType rhs)
    {
        *value -= rhs;
        return *this;
    }
    Numeric& operator*=(CurrentType rhs)
    {
        *value *= rhs;
        return *this;
    }
    Numeric& operator/=(CurrentType rhs)
    {
        if( std::abs(rhs) <= std::numeric_limits<CurrentType>::epsilon() )
        {
            std::cout << "Warning: Floating point division by zero!" << std::endl;
        }
        *value /= rhs;
        return *this; 
    }    
    // 4 power functions with different exponent type
    Numeric& powInternal(const CurrentType exp)
    {
        *value = static_cast<CurrentType>(std::pow(*value, exp));
        return *this;
    }
    Numeric& pow(const CurrentType exp)
    {
        return powInternal(exp);
    }
    // This is necessary for when I call pow from an object of a given Numeric type with an argument of a different Numeric type; otherwise it would give me some conversion warnings
    template<typename DifferentTemplatedType> 
    Numeric& pow(const DifferentTemplatedType& nExp)
    {
        return powInternal(static_cast<CurrentType>(nExp));
    }
    // convert UDT to primitive type
    operator CurrentType() const { return *value; }
    // 
    template<typename CallableFcn>
    Numeric& apply(CallableFcn myFunc)
    {
        std::cout << "--->Templated return type" << std::endl;
        myFunc(value);
        return *this;
    }    
 
private:
    std::unique_ptr<CurrentType> value; // #1)    
}; 

// =============================================================
//             Point class methods implementations
// =============================================================
Point::Point(float cx, float cy) : x(cx), y(cy) {}
Point& Point::multiply(float m)
{
    x *= m;
    y *= m;
    return *this;
}
void Point::toString()
{
    std::cout << "x: " << x << ", " << "y: " << y << std::endl;
}

// =============================================================
//                              MAIN
// =============================================================

int main()
{
    // ------------------------------------------------------------
    //                      Arithmetic tests
    // ------------------------------------------------------------
    // FloatType object instanciation and method tests
    Numeric<float> ft0 (3.0f);
    // --------
    std::cout << "Initial value of ft0: " << ft0 << std::endl;
    // --------
    std::cout << "Use of function concatenation (only float arguments) " << std::endl;
    ft0 += 3.0f;
    ft0 *= 1.5f;
    ft0 /= 5.0f;
    std::cout << "New value of ft0 = (ft0 + 3.0f) * 1.5f / 5.0f = " <<  ft0  << std::endl;


    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    Numeric<double> dt0 (5.0);
    Numeric<int> it0 (10);

    // --------
    std::cout << "Initial value of dt0: " << dt0 << std::endl;
    std::cout << "Initial value of it0: " << it0 << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    dt0 *= it0;
    dt0 /= static_cast<double>(5.0f);
    dt0 += static_cast<double>(ft0);
    std::cout << "New value of dt0 = (dt0 * it0) / 5.0f + ft0 = " <<  dt0 << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    it0 /= 0;
    std::cout << "New value of it0 = it0 / 0 = " << it0  << std::endl;

    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    Numeric<float> ft1(2);
    Numeric<double> dt1(2);
    Numeric<int> it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    Numeric<int> itExp(2);
    Numeric<float> ftExp(2.0f);
    Numeric<double> dtExp(2.0);
    
    // Power tests with FloatType
    std::cout << "Power tests with FloatType " << std::endl;
    std::cout << "pow(ft1, floatExp) = " << ft1 << "^" << floatExp << " = " << ft1.pow(floatExp)  << std::endl;
    std::cout << "pow(ft1, itExp) = " << ft1 << "^" << itExp << " = " << ft1.pow(itExp)  << std::endl;
    std::cout << "pow(ft1, ftExp) = " << ft1 << "^" << ftExp << " = " << ft1.pow(ftExp)  << std::endl;    
    std::cout << "pow(ft1, dtExp) = " << ft1 << "^" << dtExp << " = " << ft1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;  

    // Power tests with DoubleType
    std::cout << "Power tests with DoubleType " << std::endl;
    std::cout << "pow(dt1, doubleExp) = " << dt1 << "^" << doubleExp << " = " << dt1.pow(intExp)  << std::endl;
    std::cout << "pow(dt1, itExp) = " << dt1 << "^" << itExp << " = " << dt1.pow(itExp)  << std::endl;
    std::cout << "pow(dt1, ftExp) = " << dt1 << "^" << ftExp << " = " << dt1.pow(ftExp)  << std::endl;    
    std::cout << "pow(dt1, dtExp) = " << dt1 << "^" << dtExp << " = " << dt1.pow(dtExp)  << std::endl;    
    std::cout << "---------------------\n" << std::endl;    

    // Power tests with IntType
    std::cout << "Power tests with IntType " << std::endl;
    std::cout << "pow(it1, intExp) = " << it1 << "^" << intExp << " = " << it1.pow(intExp)  << std::endl;
    std::cout << "pow(it1, itExp) = " << it1 << "^" << itExp << " = " << it1.pow(itExp)  << std::endl;
    std::cout << "pow(it1, ftExp) = " << it1 << "^" << ftExp << " = " << it1.pow(ftExp)  << std::endl;    
    std::cout << "pow(it1, dtExp) = " << it1 << "^" << dtExp << " = " << it1.pow(dtExp)  << std::endl;    
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Point tests
    // ------------------------------------------------------------
    Numeric<float> ft2(3.0f);
    Numeric<double> dt2(4.0);
    Numeric<int> it2(5);   
    float floatMul = 6.0f;

    // Point tests with float
    std::cout << "Point tests with float argument:" << std::endl;
    Point p0(ft2, floatMul);
    p0.toString();   
    std::cout << "Multiplication factor: " << floatMul << std::endl;
    p0.multiply(floatMul); 
    p0.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with FloatType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p1(ft2, ft2);
    p1.toString();   
    std::cout << "Multiplication factor: " << ft2 << std::endl;
    p1.multiply(ft2); 
    p1.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with DoubleType
    std::cout << "Point tests with FloatType argument:" << std::endl;
    Point p2(ft2, static_cast<float>(dt2));
    p2.toString();   
    std::cout << "Multiplication factor: " << dt2 << std::endl;
    p2.multiply(static_cast<float>(dt2)); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2); 
    p3.toString();
    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                  Lambda tests with fcn apply()
    // ------------------------------------------------------------
    Numeric<float> ft3(3.0f);
    Numeric<double> dt3(4.0);
    Numeric<int> it3(5);
    using FtNumeric = decltype(ft3);
    using DtNumeric = decltype(dt3);
    using ItNumeric = decltype(it3);
    
    std::cout << "Calling FloatType::apply() using a lambda (adds 7.0f) and FloatType as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply( [&ft3](std::unique_ptr<FtNumeric::CurrentType> &value) -> FtNumeric&
    {
      *value += 7.0f;
      return ft3;
    } );
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "Calling FloatType::apply() twice using a free function (adds 7.0f) and void as return type:" << std::endl;
    std::cout << "ft3 before: " << ft3 << std::endl;
    ft3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "ft3 after: " << ft3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling DoubleType::apply() using a lambda (adds 6.0) and DoubleType as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply( [&dt3](std::unique_ptr<DtNumeric::CurrentType> &value) -> DtNumeric&
    {
      *value += 6.0;
      return dt3;
    } ); // This calls the templated apply fcn
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "Calling DoubleType::apply() twice using a free function (adds 7.0) and void as return type:" << std::endl;
    std::cout << "dt3 before: " << dt3 << std::endl;
    dt3.apply(myNumericFreeFunct<double>).apply(myNumericFreeFunct<double>); // This calls the templated apply fcn
    std::cout << "dt3 after: " << dt3 << std::endl;
    std::cout << "---------------------\n" << std::endl;

    std::cout << "Calling IntType::apply() using a lambda (adds 5) and IntType as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply( [&it3](std::unique_ptr<ItNumeric::CurrentType> &value) -> ItNumeric&
    {
      *value += 5;
      return it3;
    } );
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "Calling IntType::apply() twice using a free function (adds 7) and void as return type:" << std::endl;
    std::cout << "it3 before: " << it3 << std::endl;
    it3.apply(myNumericFreeFunct).apply(myNumericFreeFunct);
    std::cout << "it3 after: " << it3 << std::endl;
    std::cout << "---------------------\n" << std::endl;    
}
