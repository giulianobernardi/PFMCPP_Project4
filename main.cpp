/*
Project 4: Part 9 / 9
 video: Chapter 5 Part 8

Create a branch named Part9

 Rule of 3-5-0 and S.R.P.
 
 DO NOT EDIT YOUR PREVIOUS main(). 
 
 1) add the Leak Detector files from Project5
 
 2) add these macros after the JUCE_LEAK_DETECTOR macro :
 */

// #define JUCE_DECLARE_NON_COPYABLE(className) \
//             className (const className&) = delete;\
//             className& operator= (const className&) = delete;

// #define JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(className) \
//             JUCE_DECLARE_NON_COPYABLE(className) \
//             JUCE_LEAK_DETECTOR(className)

/*
 3) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Temporary) to the end of the  Temporary<> struct
 
 4) add JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Numeric) to the end of the Numeric<> struct
 
 if you compile it, you'll see lots of errors about deleted functions.
 
 5) Implement the Rule of 5 on Numeric<> and Temporary<> to fix this.
 
 You should end up with the same program output as Part 8's task if you did it right.
 */

/*
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
#include <math.h>
#include <functional>
#include <memory>
#include <typeinfo>
#include "LeakedObjectDetector.h"


template<typename NumericType>
struct Temporary
{
    // Constructor when passing a NumericType object
    Temporary(NumericType t) : v(t)
    {
        std::cout << "I'm a Temporary<" << typeid(v).name() << "> object, #"
                  << counter++ << std::endl;
    }

    // ----- The magnificient 3 (+2 implicit) --------
    // Destructor
    ~Temporary() = default;
    // Move constructor
    Temporary(Temporary&& other) : v( std::move(other.v) ) { }
    // Move assignment operator
    Temporary& operator=(Temporary&& other)
    {
        this->v =  std::move(other.v);
        return *this;
    }    
    // -------------------------------------------------

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

    // Leak detector for Temporary
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Temporary)
};


template<typename NumericType>
int Temporary<NumericType>::counter = 0;

// =============================================================
//                  Numeric object definition
// =============================================================
template <typename TemplatedType> 
struct Numeric
{
public:    
    using CurrentType = Temporary<TemplatedType>;
    
    // Constructor when passing a TemplatedType object
    Numeric(TemplatedType value_) 
    : value( std::make_unique<CurrentType>(value_) ) {}

    // ----- The magnificient 3 (+2 implicit) --------
    // Destructor
    ~Numeric() = default;
    // Move constructor
    Numeric(Numeric&& other_) : value( std::move(other_.value) ) { }
    // Move assignment operator
    Numeric& operator=(Numeric&& other_)
    {
        this->value =  std::move(other_.value);
        return *this;
    }    
    // -------------------------------------------------
    
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
        if constexpr ( std::is_same<int, TemplatedType>::value ) 
        { // If template type is an int
            if constexpr ( std::is_same<int, OtherTemplatedType>::value ) 
            { // If param type is an int
                if( ott == 0 )
                { // If param is 0
                    std::cout << "Division by zero not allowed with integers!!" << std::endl;
                    return *this;
                }
            }
            else if( std::abs(ott) <= std::numeric_limits<OtherTemplatedType>::epsilon() )
            {  // If param type is not an int, but param is <= than eps
                std::cout << "Division by (non-integer almost) zero not allowed when the first operand is integer!!!" << std::endl;
            }
        }
        else if( std::abs(ott) <= std::numeric_limits<OtherTemplatedType>::epsilon() )
        {  // If neither template nor param type are int, and param is <= than eps
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

    // Apply function
    template<typename CallableFcn>
    Numeric& apply(CallableFcn myFunc)
    {
        myFunc(value);
        return *this;
    }  

private:
    std::unique_ptr<CurrentType> value;

    // Leak detector for Numeric
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Numeric)
}; 

// Cube function
template <typename TemplatedType>
void cube(std::unique_ptr<TemplatedType>& value)
{
    *value =  (*value) * (*value) * (*value);
}

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
    intNum = 2 + (intNum2 - 4) + static_cast<double>(floatNum) / 2.3;
    std::cout << "intNum: " << intNum << std::endl;
    
    {
        using Type = decltype(f);
        f.apply([&f](std::unique_ptr<Type::CurrentType>&value) -> Type&
                {
                    auto& v = *value;
                    v = v * v;
                    return f;
                });
        std::cout << "f squared: " << f << std::endl;
        
        f.apply( cube<Type::CurrentType> );
        std::cout << "f cubed: " << f << std::endl;
    }
    
    {
        using Type = decltype(d);
        d.apply([&d](std::unique_ptr<Type::CurrentType>&value) -> Type&
                {
                    auto& v = *value;
                    v = v * v;
                    return d;
                });
        std::cout << "d squared: " << d << std::endl;
        
        d.apply( cube<Type::CurrentType> );
        std::cout << "d cubed: " << d << std::endl;
    }
    
    {
        using Type = decltype(i);
        i.apply([&i](std::unique_ptr<Type::CurrentType>&value) -> Type&
                {
                    auto& v = *value;
                    v = v * v;
                    return i;
                });
        std::cout << "i squared: " << i << std::endl;
        
        i.apply( cube<Type::CurrentType> );
        std::cout << "i cubed: " << i << std::endl;
    }
}
