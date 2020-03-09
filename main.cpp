/*
 Project 4 - Part 3 / 9
 Video: Chapter 4 Part 3 
 Casting

 Create a branch named Part3
 
 do not edit main().  you'll be making your old main work with these new code changes.
 
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
 
 8) use your knowledge of casting to remove any conversion warnings. 
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
Make a pull request after you make your first commit and pin the pull request link to our DM thread.

send me a DM to check your pull request

 Wait for my code review.
 */




#include <iostream>
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
    // 4 functions taking a float as input
    FloatType& add(float rhs );
    FloatType& subtract(float rhs );
    FloatType& multiply(float rhs );
    FloatType& divide(float rhs );
    // convert UDT to primitive type
    operator float();
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
// convert UDT to primitive type
FloatType::operator float()
{
    return float(*this->value); 
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
    // 4 functions taking a double as input
    DoubleType& add(double rhs );
    DoubleType& subtract(double rhs );
    DoubleType& multiply(double rhs );
    DoubleType& divide(double rhs );
    // convert UDT to primitive type
    operator double();
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
// convert UDT to primitive type
DoubleType::operator double()
{
    return double(*this->value);
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
    // 4 functions taking an int as input
    IntType& add( int rhs );
    IntType& subtract( int rhs );
    IntType& multiply( int rhs );
    IntType& divide( int rhs );
    // convert UDT to primitive type
    operator int();
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
// convert UDT to primitive type
IntType::operator int()
{
    return int(*this->value);
}
// =============================================================
//                              MAIN
// =============================================================

int main()
{
    // FloatType object instanciation and method tests
    FloatType ft (3.0f);
    // --------
    std::cout << "Initial value of ft: " << float(ft) << std::endl;
    // --------
    std::cout << "Use of function concatenation (only float arguments) " << std::endl;
    std::cout << "New value of ft = (ft + 3.0f) * 1.5f / 5.0f = " << float( (ft.add( 3.0f ).multiply(1.5f).divide(5.0f)) ) << std::endl;
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType/IntType object instanciation and method tests
    DoubleType dt (5.0);
    IntType it(10);
    // --------
    std::cout << "Initial value of dt: " << double(dt) << std::endl;
    std::cout << "Initial value of it: " << int(it) << std::endl;
    // --------
    std::cout << "Use of function concatenation (mixed type arguments) " << std::endl;
    std::cout << "New value of dt = (dt * it) / 5.0f + ft = " << double( dt.multiply(it).divide(double(5.0f)).add(double(ft)) ) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
    
    // Intercept division by 0
    // --------
    std::cout << "Intercept division by 0 " << std::endl;
    std::cout << "New value of it = dt / 0 = " << int((it.divide(0)) ) << std::endl;

    std::cout << "---------------------\n" << std::endl; 
}
