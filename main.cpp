
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
#if false
namespace Example
{
    int main()
    {
        FloatType floatNum(4.3f);
        IntType intNum(2);
        IntType intNum2(6);

        /* 
        if you previously had a line like this demonstrating chaining:
            
            intNum.add(3).add(4.5f).divide(floatNum); 

        it should become:
        */
        intNum += 3;
        intNum += 4.5f;
        intNum /= floatNum;
        std::cout << "intNum: " << intNum << std::endl;
        
        return 0;
    }
}
#endif
 /*
 6) compile/link/run to make sure you don't have any errors
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */




#include <iostream>
#include <cmath>

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
//                  FloatType object definition
// =============================================================
struct FloatType
{
private:
    float* value;
public:    
    FloatType(float value_) : value( new float(value_) ) {}
    ~FloatType()
    { 
        delete value; 
        value = nullptr;
    }
    // Operator overloading
    FloatType& operator+=(float rhs);
    FloatType& operator-=(float rhs);
    FloatType& operator*=(float rhs);
    FloatType& operator/=(float rhs);
    // 4 power functions with different exponent type
    FloatType& powInternal(const float exp);
    FloatType& pow(const float exp); 
    FloatType& pow(const IntType& itExp);
    FloatType& pow(const FloatType& ftExp);
    FloatType& pow(const DoubleType& dtExp);    
    // convert UDT to primitive type
    operator float() const
    {
        return *value;
    }
}; 
// Operator overloading
FloatType& FloatType::operator+=(float rhs) 
{
    *value += rhs;
    return *this;
}
FloatType& FloatType::operator-=(float rhs)
{
    *value -= rhs;
    return *this;
}
FloatType& FloatType::operator*=(float rhs)
{
    *value *= rhs;
    return *this;
}
FloatType& FloatType::operator/=(float rhs)
{
    *value /= rhs;
    return *this;
}
// =============================================================
//                  DoubleType object definition
// =============================================================
struct DoubleType
{
private:
    double* value;
public:   
    DoubleType(double value_) : value( new double(value_) ) {}
    ~DoubleType()
    { 
        delete value; 
        value = nullptr;
    }
    // Operator overloading
    DoubleType& operator+=(double rhs);
    DoubleType& operator-=(double rhs);
    DoubleType& operator*=(double rhs);
    DoubleType& operator/=(double rhs);
    // 4 power functions with different exponent type
    DoubleType& powInternal(const double exp);
    DoubleType& pow(const double exp); 
    DoubleType& pow(const IntType& itExp);
    DoubleType& pow(const FloatType& ftExp);
    DoubleType& pow(const DoubleType& dtExp);
    // convert UDT to primitive type
    operator double() const
    {
        return *value;
    }
}; 
// Operator overloading
DoubleType& DoubleType::operator+=(double rhs) 
{
    *value += rhs;
    return *this;
}
DoubleType& DoubleType::operator-=(double rhs)
{
    *value -= rhs;
    return *this;
}
DoubleType& DoubleType::operator*=(double rhs)
{
    *value *= rhs;
    return *this;
}
DoubleType& DoubleType::operator/=(double rhs)
{
    *value /= rhs;
    return *this;
}
// =============================================================
//                  IntType object definition
// =============================================================
struct IntType
{
private:
    int* value;
public:       
    IntType(int value_) : value( new int(value_) ) {}
    ~IntType()
    { 
        delete value; 
        value = nullptr;
    }
    // Operator overloading
    IntType& operator+=(int rhs);
    IntType& operator-=(int rhs);
    IntType& operator*=(int rhs);
    IntType& operator/=(int rhs);
    // 4 power functions with different exponent type
    IntType& powInternal(const int exp);
    IntType& pow(const int exp); 
    IntType& pow(const IntType& itExp);
    IntType& pow(const FloatType& ftExp);
    IntType& pow(const DoubleType& dtExp);
    // convert UDT to primitive type
    operator int() const
    {
        return *value;
    }
}; 
// Operator overloading
IntType& IntType::operator+=(int rhs) 
{
    *value += rhs;
    return *this;
}
IntType& IntType::operator-=(int rhs)
{
    *value -= rhs;
    return *this;
}
IntType& IntType::operator*=(int rhs)
{
    *value *= rhs;
    return *this;
}
IntType& IntType::operator/=(int rhs)
{
    if( rhs != 0 )
        *value /= rhs;
    else    
        std::cout << "division by zero not allowed with integers" << std::endl;
    return *this;        
}
// =============================================================
//                  Power methods implementations
// =============================================================
// Power methods for FloatType
FloatType& FloatType::powInternal(const float exp) 
{
    *value = std::pow(*value, exp);
    return *this;
}
FloatType& FloatType::pow(const float exp) 
{
    return powInternal(exp);
}
FloatType& FloatType::pow(const IntType& itExp) 
{ 
    return powInternal(itExp); 
}
FloatType& FloatType::pow(const FloatType& ftExp) 
{
    return powInternal(ftExp);    
}
FloatType& FloatType::pow(const DoubleType& dtExp) 
{
    return powInternal(static_cast<float>(dtExp));
}
// ------------------------------------------------------------
// Power methods for DoubleType
DoubleType& DoubleType::powInternal(const double exp) 
{
    *value = std::pow(*value, exp);
    return *this;
}
DoubleType& DoubleType::pow(const double exp) 
{
    return powInternal(exp);
}
DoubleType& DoubleType::pow(const IntType& itExp) 
{ 
    return powInternal(itExp); 
}
DoubleType& DoubleType::pow(const FloatType& ftExp) 
{
    return powInternal(static_cast<double>(ftExp));    
}
DoubleType& DoubleType::pow(const DoubleType& dtExp) 
{
    return powInternal(dtExp);
}
// ------------------------------------------------------------
// Power methods for IntType
IntType& IntType::powInternal(const int exp) 
{
    *value = static_cast<int>(std::pow(*value, exp));
    return *this;
}
IntType& IntType::pow(const int exp) 
{
    return powInternal(exp);
}
IntType& IntType::pow(const IntType& itExp) 
{ 
    return powInternal(itExp); 
}
IntType& IntType::pow(const FloatType& ftExp) 
{
    return powInternal(static_cast<int>(ftExp));    
}
IntType& IntType::pow(const DoubleType& dtExp) 
{
    return powInternal(static_cast<int>(dtExp));
}

// =============================================================
//             Point class methods implementations
// =============================================================

Point::Point(float cx, float cy) : x(cx), y(cy) {}
Point& Point::multiply(const FloatType& ftm)
{
    return multiply(static_cast<float>(ftm));
}
Point& Point::multiply(const DoubleType& dtm)
{
    return multiply(static_cast<float>(dtm));
}
Point& Point::multiply(const IntType& itm)
{
    return multiply(static_cast<float>(itm));
}
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
    FloatType ft0 (3.0f);
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
    DoubleType dt0 (5.0);
    IntType it0 (10);

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
    std::cout << "New value of it0 = it0 / 0 = " << it0  << std::endl;

    std::cout << "===============================\n" << std::endl; 

    // ------------------------------------------------------------
    //                          Power tests
    // ------------------------------------------------------------
    FloatType ft1(2);
    DoubleType dt1(2);
    IntType it1(2);    
    int floatExp = 2.0f;
    int doubleExp = 2.0;
    int intExp = 2;
    IntType itExp(2);
    FloatType ftExp(2.0f);
    DoubleType dtExp(2.0);
    
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
    FloatType ft2(3.0f);
    DoubleType dt2(4.0);
    IntType it2(5);
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
    p2.multiply(dt2); 
    p2.toString();   
    std::cout << "---------------------\n" << std::endl;

    // Point tests with IntType
    std::cout << "Point tests with IntType argument:" << std::endl;
    Point p3(ft2, static_cast<float>(dt2));
    p3.toString();   
    std::cout << "Multiplication factor: " << it2 << std::endl;
    p3.multiply(it2); 
    p3.toString();   
    std::cout << "---------------------\n" << std::endl;

}
