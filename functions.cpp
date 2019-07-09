#include"test.h"

#include <typeinfo>



namespace Functions {

#ifdef POSITIONAL
int my_function::fun_positional(int extra, 
		int arg_int, 
	std::string s, double d){
	//Getting the field size
	return 42+arg_int+extra;
}
#endif

#ifdef NAMED
int my_function::fun_named(int extra, my_function::Arg_tuple arg_tuple )
{
	auto arg_map = arg_tuple_2_map(arg_tuple);
	int arg_int = arg_map["arg0_int"_s];//  # Does not compile
	
	return 42+arg_int+extra;
}
#endif
};
