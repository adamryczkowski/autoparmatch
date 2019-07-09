#include<string>
#include<iostream>
#include "make_function_call.h"
#define CALLEE
#include"test.h"

int main(int argc, char* argv[])
{
	std::cout<<std::endl<<std::endl;
	std::cout<<"Welcome to the technology demonstrator of named parameters in C++, designed by Adam Ryczkowski"<<std::endl;
	
	
	auto fields = hana::make_map(
		hana::make_pair("arg0_int"_s, int(42) ),
		hana::make_pair("arg1_int"_s, int(43) ),
		hana::make_pair("arg2_int"_s, int(44) ),
		hana::make_pair("arg_double"_s, double(3.14) ),
		hana::make_pair("arg_float"_s, float(3.14) ),
		hana::make_pair("arg_string"_s, std::string("Ala") )
	);
	
	#ifdef POSITIONAL
	std::cout<<"Calling positional function..."<<std::endl;
	auto ans_pos = call_by_position(fields, Functions::my_function{}, 7);
	std::cout<<"...function returned value "<<ans_pos<<std::endl<<std::endl;
	#endif
	
	
	#ifdef NAMED
	std::cout<<"Calling named function..."<<std::endl;
	auto ans_named = call_by_name(fields, Functions::my_function{}, 7);
	std::cout<<"...function returned value "<<ans_named<<std::endl<<std::endl;
	#endif
	return 0;
}

