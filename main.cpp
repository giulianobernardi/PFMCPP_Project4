/*
 Project 4 - Part 1 / 9
 video: Chapter 2 Part 7
 Returning Values tasks 

 Create a branch named Part1
 
 1) write 3 UDTs named FloatType, DoubleType, IntType.
 
 2) give each UDT the following member functions:
        add( lhs, rhs );
        subtract( lhs, rhs );
        multiply( lhs, rhs );
        divide( lhs, rhs );
 
 3) make them return the correct primitive type. e.g. if you're implementing the FloatType::add function, your implementation would start like this:
        float FloatType::add( float lhs, float rhs )
 
 4) declare a few instances of each class in main() and call the member functions with the appropriate arguments.
        FloatType ft;
        auto result = ft.add(3.2f, 23.f );
 
 5) print out those results using std::cout:
        std::cout "result of ft.add(): " << result << std::endl;
 
 6) After you finish defining each type/function, click the [run] button.  Clear up any errors or warnings as best you can.
 
 Commit your changes by clicking on the Source Control panel on the left, entering a message, and click [Commit and push].
 
 Send me the the link to your repl.it in a DM on Slack

 Wait for my code review.
 */

// FloatType object definition
struct FloatType
{
    float add(float lhs, float rhs ){ return lhs + rhs;}
    float subtract(float lhs,float rhs ){ return lhs - rhs;}
    float multiply(float lhs, float rhs ){ return lhs * rhs;}
    float divide(float lhs, float rhs ){ return lhs / rhs;}
}; 

// DoubleType object definition
struct DoubleType
{
    double add(double lhs, double rhs ){ return lhs + rhs;}
    double subtract(double lhs,double rhs ){ return lhs - rhs;}
    double multiply(double lhs, double rhs ){ return lhs * rhs;}
    double divide(double lhs, double rhs ){ return lhs / rhs;}
}; 

// IntType object definition
struct IntType
{
    int add(int lhs, int rhs ){ return lhs + rhs;}
    int subtract(int lhs,int rhs ){ return lhs - rhs;}
    int multiply(int lhs, int rhs ){ return lhs * rhs;}
    int divide(int lhs, int rhs ){ return lhs / rhs;}
}; 

// Example of external definition using the scoping operator
// float FloatType::add( float lhs, float rhs )
// {
//     return lhs + rhs;
// }

#include <iostream>
int main()
{
    // FloatType object instanciation and method tests
    FloatType ft;
    float firstFloatArg = 3.2f;
    float secondFloatArg = 23.f;
    // --------
    std::cout << "First float argument: " << firstFloatArg << std::endl;
    std::cout << "Second float argument: " << secondFloatArg << std::endl;
    // --------
    std::cout << "result of ft.add(): " << ft.add(firstFloatArg, secondFloatArg ) << std::endl;
    std::cout << "result of ft.subtract(): " << ft.subtract(firstFloatArg, secondFloatArg ) << std::endl;
    std::cout << "result of ft.multiply(): " << ft.multiply(firstFloatArg, secondFloatArg ) << std::endl;
    std::cout << "result of ft.divide(): " << ft.divide(firstFloatArg, secondFloatArg ) << std::endl; 
       
    std::cout << "---------------------\n" << std::endl; 
    
    // DoubleType object instanciation and method tests
    DoubleType dt;
    double firstDoubleArg = 3.2;
    double secondDoubleArg = 23.;
    // --------
    std::cout << "First double argument: " << firstDoubleArg << std::endl;
    std::cout << "Second double argument: " << secondDoubleArg << std::endl;   
    // -------- 
    std::cout << "result of dt.add(): " << dt.add(firstDoubleArg, secondDoubleArg ) << std::endl;
    std::cout << "result of dt.subtract(): " << dt.subtract(firstDoubleArg, secondDoubleArg ) << std::endl;
    std::cout << "result of dt.multiply(): " << dt.multiply(firstDoubleArg, secondDoubleArg ) << std::endl;
    std::cout << "result of dt.divide(): " << dt.divide(firstDoubleArg, secondDoubleArg ) << std::endl; 

    std::cout << "---------------------\n" << std::endl; 

    // IntType object instanciation and method tests
    IntType it;
    int firstIntArg = 3;
    int secondIntArg = 23;
    // --------
    std::cout << "First int argument: " << firstIntArg << std::endl;
    std::cout << "Second int argument: " << secondIntArg << std::endl;   
    // --------     
    std::cout << "result of it.add(): " << it.add(firstIntArg, secondIntArg ) << std::endl;
    std::cout << "result of it.subtract(): " << it.subtract(firstIntArg, secondIntArg ) << std::endl;
    std::cout << "result of it.multiply(): " << it.multiply(firstIntArg, secondIntArg ) << std::endl;
    std::cout << "result of it.divide(): " << it.divide(firstIntArg, secondIntArg ) << std::endl;           
}
