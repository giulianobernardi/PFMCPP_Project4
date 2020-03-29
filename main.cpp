
#include <iostream>
#include <memory>
/*
Project 4: Part 7 / 9
Video: Chapter 5 Part 4

Create a branch named Part7

Do not delete your previous main. you will be adding to it.

Templates and Containers

    Build/Run often with this task to make sure you're not breaking the code with each step.
    I recommend committing after you get each step working so you can revert to a working version easily if needed.
    it's very easy to mess this task up. 

#1) if you're not using std::unique_ptr to own your heap-allocated type as a member variable, 
    replace your manual memory management techniques with a private std::unique_ptr member variable.

#2) replace your Heap-Allocated Numeric Type-owning class with a templated class called Numeric.
        replace all of your previous instances of your separate classes with this templated class.

#3) add a 'using <some name> = <your class template parameter>;' 
        treat this type declaration via 'using' as a static member variable
        use this Type alias as the argument everywhere you previously used the template argument.
        this will make it very easy to change the type if needed.
            i.e. if you have 'std::unique_ptr<NumericType> value;' before you'd replace NumericType in that variable declaration with '<some name>'
        
#4) you'll need to pair it with decltype() to help the compiler figure out the type of the object your class owns when you make your lambda and free function that takes your unique_ptr.  
    i.e. like this for determining the template parameter of the unique_ptr function argument to your class's apply() function
        std::unique_ptr< decltype( <instance of class> )::<some name> >
    
#5) template your free function for the apply() that takes a function pointer so it can be used with your Wrapper class's apply() function

#6) add an explicit template specialization for 'double' of your wrapper class
        this template specialization will have one apply() function instead of 2. 

#7) this apply() function will be templated, and expect a Callable object, not std::function<>.   //need to see if I can do this.
        the function should allow for chaining.  
        the callable object should return void, like the function pointer-based apply() function in the primary class template

#8) instantiate your explicit template specialization

#9) call the apply function twice, once with a lambda and once with the free function
        the free function is templated, so you might need to call it including the template arguments.
        
#10) in addition to using the lambda argument to modify the owned object:  (your previous task's lambdas did this same thing) 
        make the lambda use your explicit template instance (maybe via a std::cout), 



compile/link/run to make sure you don't have any errors

Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.

If you need to view an example, see: https://bitbucket.org/MatkatMusic/pfmcpptasks/src/master/Projects/Project4/Part7Example.cpp
*/






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
    Numeric& operator/=(CurrentType rhs)
    {
        if (std::is_same<CurrentType, int>::value) 
        {
            // We enter this if with an int rhs. If it's larger or equal than one, we divide, otherwise it's 0 and we return the cout. If I used '!= 0', I'd get the error (-Wfloat-equal)
            if( std::abs(rhs) >= 1)
                {
                    *value /= rhs;
                }
            else    
                std::cout << "Division by zero not allowed with integers!!" << std::endl;
            return *this;       
        }
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
