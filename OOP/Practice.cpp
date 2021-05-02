#include <iostream>

using namespace std;

class MyClass {        // The class
  public:              // Access specifier
    void myMethodInsideClass(int x) {  // Method/function defined inside the class
      cout << "Hello World from Inside!\n" <<x<<endl;
    }
    // void myMethodOutsideClass(); //Method/function declaration (interface)
};

class MyClass2: public MyClass {        // The class
  public:              // Access specifier
    void myMethodInsideClass(int x, int y) {  // Method/function defined inside the class
      cout << "Hello World from Inside x, y!\n"<<x<<endl<<y<<endl;
    }
    // void myMethodOutsideClass(); //Method/function declaration (interface)
};

//scope resolution ::
// void MyClass::myMethodOutsideClass(int x) {
//   cout << "Hello World from Outside!\n";
// }

int main() {
  MyClass myObj;     // Create an object of MyClass
  myObj.myMethodInsideClass(1);  // Call the method
  MyClass2 myObj2;     // Create an object of MyClass
  myObj2.myMethodInsideClass(1,2); 
  return 0;
}