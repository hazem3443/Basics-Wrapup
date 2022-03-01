

#include <iostream>
#include <string>
#include <vector>

template<typename A>
A add(A x,A y){
	return x+y;
}

class parentclass {
	public:
	 virtual int draw(){
		std::cout <<"parent class draw"<<std::endl;
		return 0;
	}
	 int drawstatic(){
		std::cout <<"parent class"<<std::endl;
		return 0;
	}
};

class childclass:public parentclass{
	public:
	int draw() override {
		std::cout <<"child class"<<std::endl;
		return 0;
	}

	static int drawstatic(){
		std::cout <<"child class"<<std::endl;
		return 0;
	}
};

void func(parentclass &inst);



int main()
{
	parentclass A;
	childclass B;

	func(A);
	func(B);

	std::cout<<add(2,3)<<std::endl;

	std::cout<<add(7.0,3.0)<<std::endl;
	std::cout<<add(7.0f,3.0f)<<std::endl;

	std::cout << "Hello world - C++ !" << std::endl;
	return 0;
}





void func(parentclass &inst){

	inst.draw();
	inst.drawstatic();

}

// blicking lib

//static int redled;

