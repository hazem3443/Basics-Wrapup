#include <iostream>
#include <vector>
#include <ctime>
#include <typeinfo>
using namespace std;

class shape_2D{
    public:
        virtual string myType(){ return "2D-ShapeClass";}
        
        //we moved this function implementation to each class body to achieve open close principal
        //so if we need to create any new shape_2D class we would create it without need of adding any if/else blocks 
        //so we wouldn't need myType function anymore but leave it just for outside usage
        virtual float Area(){ return 0; }; //acts as our interface
        
};

class shape_3D:public shape_2D{
    public:
        virtual string myType(){ return "3D-ShapeClass";}
        
        //we moved this function implementation to each class body to achieve open close principal
        //so if we need to create any new shape_2D class we would create it without need of adding any if/else blocks 
        //so we wouldn't need myType function anymore but leave it just for outside usage
        virtual float Volume(){ return 0; }; //acts as our interface      
};

class Square:public shape_2D{
    protected:
        float length;
        float dimension;
    public:
        Square(float length=0){
            this->length = length;
            this->dimension = length;
            cout<<"Square Constructed "<< this->length <<endl;
        }
        ~Square(){
            cout<<"Square Destroyed "<< this->length <<endl;
        }
        virtual string myType() override {
            return "Square";
        }

        virtual float Area() override {
            return (this)->dimension * (this)->dimension;
        }

        // virtual float Volume() override{
        //     return  ( (this)->dimension * (this)->dimension * (this)->dimension);
        // }
};

class Cuboid: public shape_3D{
    protected:
        float length;
        float dimension;
    public:
        Cuboid(float length=0){
            this->length = length;
            this->dimension = length;
            cout<<"Cuboid Constructed "<< this->length <<endl;
        }
        ~Cuboid(){
            cout<<"Cuboid Destroyed "<< this->length <<endl;
        }
        virtual string myType() override {
            return "Cuboid";
        }

        virtual float Area() override {
            return ((this)->dimension * (this)->dimension *6);
        }

        virtual float Volume() override{
            return  ( (this)->dimension * (this)->dimension * (this)->dimension);
        }
};

class Circle:public shape_2D{
    protected:
        float radius;
        float dimension;
    public:
        Circle(float radius=0){
            this->radius = radius;
            this->dimension = radius;
            cout<<"Circle Constructed "<< this->radius<<endl;
        };
        ~Circle(){
            cout<<"Circle Destroyed "<< this->radius<<endl;
        }
        virtual string myType() override {
            return "Circle";
        }

        virtual float Area() override{
            return  (3.14 * (this)->dimension * (this)->dimension);
        }

        // virtual float Volume() override{
        //     return (0.75 * 3.14 * (this)->dimension * (this)->dimension * (this)->dimension);
        // }
};

class Sphere:public shape_3D{
    protected:
        float radius;
        float dimension;
    public:
        Sphere(float radius=0){
            this->radius = radius;
            this->dimension = radius;
            cout<<"Sphere Constructed "<< this->radius<<endl;
        };
        ~Sphere(){
            cout<<"Sphere Destroyed "<< this->radius<<endl;
        }
        virtual string myType() override {
            return "Sphere";
        }

        virtual float Area() override{
            return  (4*3.14 * (this)->dimension * (this)->dimension);
        }

        virtual float Volume() override{
            return (0.75 * 3.14 * (this)->dimension * (this)->dimension * (this)->dimension);
        }
};

class SumCalculatorOutputter{    
    protected:
        virtual float sum(){return 0;}

    public:

        void Json(){
            cout <<"Json Sum = "<<(this)->sum()<<endl;
        }
        void Html(){
            cout <<"HTML Sum = "<<(this)->sum()<<endl;
        }
};

//here we can make use of a template in order to define any type whether it is a nested type of 2D-3D shape or only 3D one to avoid type collision or casting issues
template <class T>
class AreaCalculator:public SumCalculatorOutputter{
    protected:
        vector<T*> shapes;
    public:
        AreaCalculator(vector<T*> shs){
            cout<<"AreaCalculator Constructed"<<endl;
            for(int i=0;i<shs.size();i++){
                this->shapes.push_back(shs[i]);
            }
        }

        virtual float sum() override{
            float areaSum=0;
            for(int i=0;i<10 && shapes[i]!=NULL ;i++){
                areaSum += shapes[i]->Area() ;
            }
            return areaSum;
        }
};

//here we can make use of a template in order to define any type whether it is a nested type of 2D-3D shape or only 3D one to avoid type collision
template <class T>
class VolumeCalculator:public SumCalculatorOutputter{
    //Liskov rule we need to name the logic function with the same name but with different logic
    //in order to be substitutable for the outputter class or any other one

    protected:
        //in order to achieve interface segregation we need to create other type for each feature
        vector<T*> shapes;
    public:
        VolumeCalculator(vector<T*> shs){
            cout<<"VolumeCalculator Constructed"<<endl;
            for(int i=0;i<shs.size();i++){
                this->shapes.push_back(shs[i]);
            }
        }

        virtual float sum() override{
            float volSum=0;
            for(int i=0;i<10 && this->shapes[i]!=NULL ;i++){
                volSum += this->shapes[i]->Volume() ;
            }
            return volSum;
        }
};

// template<typename Base, typename T>
// inline bool instanceof(const T*) {
//    return is_base_of<Base, T>::value;
// }

int main(){

    vector<shape_2D*> shapes2D = {
        new Square(2),
        new Circle(2)
    };
    
    AreaCalculator<shape_2D>* areaInst = new AreaCalculator<shape_2D>(shapes2D);
    cout<<shapes2D[0]->myType()<<" Area = "<<shapes2D[0]->Area()<<endl;
    cout<<shapes2D[1]->myType()<<" Area = "<<shapes2D[1]->Area()<<endl;
    areaInst->Json();
    areaInst->Html();

    cout << "---------------" <<"Point"<<"---------------" <<endl;
    /*  must create new shapes that will implement shape_3D interface and remove
        shape_3D from square and circle classes in order to achieve interface segregation
        and the new sphere and cuboid will contain an area too but in different way o they 
        should implement area shape_2D and volumen shape_3D 
        and we can conclude that to all features related to 2d and 3d shapes
    */
    vector<shape_3D*> shapes3D = {
        new Cuboid(3),
        new Sphere(3)
    };

    VolumeCalculator<shape_3D>* volInst = new VolumeCalculator<shape_3D>(shapes3D);

    cout<<shapes3D[0]->myType()<<" Surface Area = "<<(shapes3D[0])->Area()<<endl;
    cout<<shapes3D[1]->myType()<<" Surface Area = "<<(shapes3D[1])->Area()<<endl;

    cout<<shapes3D[0]->myType()<<" Volume = "<<shapes3D[0]->Volume()<<endl;
    cout<<shapes3D[1]->myType()<<" Volume = "<<shapes3D[1]->Volume()<<endl;
    volInst->Json();
    volInst->Html();
    
    delete (Square*)shapes2D[0];
    delete (Circle*)shapes2D[1];

    delete (Cuboid*)shapes3D[0];
    delete (Sphere*)shapes3D[1];

    return 0;
}
