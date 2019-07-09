#include <string>

#ifdef NAMED
#include "be_called_by_name.h"
#endif

namespace Functions{

struct my_function {
#if defined NAMED || defined CALLEE
	struct Parameters {
		constexpr auto static parameters = hana::make_tuple(
			hana::make_pair(hana::type_c<int>, "arg0_int"_s ),
			hana::make_pair(hana::type_c<std::string>, "arg_string"_s ), 
			hana::make_pair(hana::type_c<double>, "arg_double"_s ) );
		constexpr auto static arg_offset = hana::size_c<1>; //What is the index of the first named argument?
	};
#endif
#ifdef NAMED
	using Arg_tuple = decltype(make_blank_argument_tuple(Parameters{}));
	static int fun_named(int, Arg_tuple);
#endif
#ifdef POSITIONAL
	static int fun_positional(int, 
		int, 
		std::string, double);
#endif
};

};


