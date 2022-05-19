#include <cstdlib>
#include <iostream>

using namespace std;

int (*func)(int a);

// A class to represent an integer array
template<class ForwardIt>
class Array {
private:
	ForwardIt* ptr;
	int size;

public:
	Array(ForwardIt* p , int s ){
        this->size = s;
        this->ptr = NULL;
        if (s != 0) {
            this->ptr = new int[s];
            for (int i = 0; i < s; i++)
                this->ptr[i] = p[i];
        }
    }

	// Overloading [] operator to access elements in array style
	ForwardIt& operator[](ForwardIt index){
        if (index >= size ||index < 0) {
            cout << "Array index out of bound, exiting"<<endl;
            exit(0);//stop code execution
        }
        return ptr[index];
    }

    //Add an element to the end of the array
    void push_back(ForwardIt el)
    {
        this->size++;
        ForwardIt* new_ptr = new int[this->size];
            for (int i = 0; i < this->size-1; i++)
                new_ptr[i] = this->ptr[i];
        new_ptr[this->size-1] = el;

        free(this->ptr);//to avoid memory leak

        this->ptr = new_ptr;
        
    }
    
    // method to print contents
    void print() const
    {
        if(this->size!=0){
            cout<<"{ ";
            for (int i = 0; i < size; i++)
                cout<<this->ptr[i]<<", ";
            cout<<"\b \b\b \b }"<<endl;
        }
    }
    
    //return the start of the array elements
    ForwardIt* begin(){
        return this->ptr;
    }

    //return the end of the array elements
    ForwardIt* end(){
        return this->ptr + this->size -1;
    }

    //return array of result of lamda condition
    template<class FIt, class Ue>
    Array<int>* remove_if_el(FIt* first, FIt* last, Ue p)
    {
        Array<FIt>* res = new Array<FIt>(0,0);

        if (first != last)
            for(FIt* i = first; i != last+1;i++ )
                if (!p(*i))
                    res->push_back(*i);
        
        free(this->ptr);//to avoid memory leak
        
        this->ptr = res->ptr;
        this->size = res->size;

        return res;
    }

};

int main()
{
    int a[] = { 1, 2, 4, 5 };

    Array<int> arr1(a, 4);
    arr1[3] = 6;
    arr1.push_back(10);
    // arr1[-4] = 6; // array index out of range
    arr1.print();
    cout<<endl;
    auto itemx = arr1[2];
    auto itemy = arr1[3];

    //remember demorgan law for lamda condition
    // (A+B)' = A'. B'
    // (A.B)' = A' + B'
    arr1.remove_if_el(arr1.begin(),
                        arr1.end(),
                        [itemx,itemy](int el){
                            return (el != itemx)&(el != itemy);
                    });
    arr1.print();

    return 0;
}

//TODO:
/*
- we can make array type have a template of an input type of array element

- we can overload = operator to make remove_if method more effective with other types 

- to make the template more dynamic dependent of item type we need to isolate array type from 
item type and make them dependent of each othe in terms of methods so

item_type{
    method operator=();
    method printEl();
}

array_type{
    method operator[]();
    method push_back(item_type);

    method operator==();
    method remove_if(lamdaFnx);
    method printArray();//loops over and executes item.printEl()
}


*/
