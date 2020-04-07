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

#include <iostream>
#include <cmath>
#include <memory>
#include <functional>
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
    operator NumericType() const
    { 
        /* read-only function */
        return v; 
    }
    operator NumericType&() 
    { 
        /* read/write function */
        return v; 
    }
private:
    static int counter;
    NumericType v;
};

/*
 2) add the definition of Temporary::counter here, which is a static variable and must be defined outside of the class.
    Remember the rules about how to define a Template member variable/function outside of the class.
*/
template<typename NumericType>
int Temporary<NumericType>::counter = 0;

/*
 3) You'll need to template your overloaded math operator functions in your Templated Class from Ch5 p04
    use static_cast to convert whatever type is passed in to your template's NumericType before performing the +=, -=, etc.  here's an example implementation:
 */
// namespace example
// {
// template<typename NumericType>
// struct Numeric
// {
//     //snip
//     template<typename OtherType>
//     Numeric& operator-=(const OtherType& o) 
//     { 
//         *value -= static_cast<NumericType>(o); 
//         return *this; 
//     }
//     //snip
// };
// }

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


// =============================================================
//                  Numeric object definition
// =============================================================
template <typename TemplatedType> 
struct Numeric
{
public:    
    using CurrentType = Temporary<TemplatedType>;
    
    // Constructor when no argument is passed
    Numeric() 
    : value( std::make_unique<CurrentType>(0) ) {}

    // Constructor when passing an object
    Numeric(CurrentType value_) 
    : value( std::make_unique<CurrentType>(value_) ) {}
    
    // -------------------------------
    // Operators overloading
    // -------------------------------
    // Assign operator
    template <typename OtherTemplatedType>
    Numeric& operator=(const OtherTemplatedType& ott)
    {
        *value = static_cast<TemplatedType>(ott);
        return *this;
    }    
    // Add-equal operator
    template <typename OtherTemplatedType>
    Numeric& operator+=(const OtherTemplatedType& ott)
    {
        *value += static_cast<TemplatedType>(ott);
        return *this;
    }
    // Subtract-equal operator
    template <typename OtherTemplatedType>
    Numeric& operator-=(const OtherTemplatedType& ott)
    {
        *value -= static_cast<TemplatedType>(ott);
        return *this;
    }
    // Multiply-equal operator
    template <typename OtherTemplatedType>
    Numeric& operator*=(const OtherTemplatedType& ott)
    {
        *value *= static_cast<TemplatedType>(ott);
        return *this;
    }
    // Divide-equal operator
    template <typename OtherTemplatedType>   
    Numeric& operator /= (const OtherTemplatedType& ott)
    {
        if constexpr ( std::is_same<int, OtherTemplatedType>::value ) 
        {
            if( ott == 0 )
            {
                std::cout << "Division by zero not allowed with integers!!" << std::endl;
                return *this;
            }
        }
        else if( std::abs(ott) <= std::numeric_limits<OtherTemplatedType>::epsilon() )
        {
            std::cout << "Warning: Floating point division by zero!" << std::endl;
        }

        *value /= static_cast<TemplatedType>(ott);
        return *this;
    }

    // Conversion functions to read/write to 'value'
    operator TemplatedType() const 
    {
        /* read-only function */
        return *value; 
    }
    operator TemplatedType&()
    {
        /* read/write function */
        return *value; 
    }


    // Power function
    template <typename OtherTemplatedType>   
    Numeric& pow(const OtherTemplatedType& exp)
    {
        *value = std::pow(*value, static_cast<TemplatedType>(exp));
        return *this;
    }

    // // Apply function
    // Numeric& apply(std::function<Numeric&(std::unique_ptr<CurrentType>&)> myFunc)
    // {
    //     std::cout << "--->Numeric as a return type" << std::endl;
    //     if( myFunc )    
    //         return myFunc(value);
    //     return *this;
    // }  

private:
    std::unique_ptr<CurrentType> value;
}; 

// =============================================================
//                          Point class
// =============================================================

struct Point
{
    Point(float, float);

    template <typename OtherTemplatedType>  
    Point& multiply(const OtherTemplatedType& ott)
    {
        x *= static_cast<float>(ott);
        y *= static_cast<float>(ott);
        return *this;
    }

    void toString();
private:
    float x{0}, y{0};
};

Point::Point(float cx, float cy) : x(cx), y(cy) {}

void Point::toString()
{
    std::cout << "Point { x: " << x << ", " << "y: " << y << " }"<< std::endl;
}


// =============================================================
//                              MAIN
// =============================================================

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
    
    // {
    //     using Type = decltype(f)::Type;
    //     f.apply([&f](std::unique_ptr<Type>&value) -> decltype(f)&
    //             {
    //                 auto& v = *value;
    //                 v = v * v;
    //                 return f;
    //             });
    //     std::cout << "f squared: " << f << std::endl;
        
    //     f.apply( cube<Type> );
    //     std::cout << "f cubed: " << f << std::endl;
    // }
    
    // {
    //     using Type = decltype(d)::Type;
    //     d.apply([&d](std::unique_ptr<Type>&value) -> decltype(d)&
    //             {
    //                 auto& v = *value;
    //                 v = v * v;
    //                 return d;
    //             });
    //     std::cout << "d squared: " << d << std::endl;
        
    //     d.apply( cube<Type> );
    //     std::cout << "d cubed: " << d << std::endl;
    // }
    
    // {
    //     using Type = decltype(i)::Type;
    //     i.apply([&i](std::unique_ptr<Type>&value) -> decltype(i)&
    //             {
    //                 auto& v = *value;
    //                 v = v * v;
    //                 return i;
    //             });
    //     std::cout << "i squared: " << i << std::endl;
        
    //     i.apply( cube<Type> );
    //     std::cout << "i cubed: " << i << std::endl;
    // }
}
