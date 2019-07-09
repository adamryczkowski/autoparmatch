#pragma once
//This header is intended to be included in the translation unit that defines (not calls) the function with named parameters,
//before the declaration of the struct


//things needed for the data struct that defines parameters
#include <boost/hana/tuple.hpp>
#include <boost/hana/string.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/size.hpp>
namespace hana = boost::hana;
using namespace hana::literals;

//additional things needed to make the following function work.
//WARNING: Skipping any of those #include from here will generate compilation errors about «'something' before deduction of 'auto'»,
//         pointing to the correct and irrelevant piece of code. Needless to say, it took me 4 hours to troubleshoot it.
#include <boost/hana/concat.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/at_key.hpp>

//Makes correct argument tuple of the given parameter_tuple, filled with default-constructed value. 
//Value must be discarded; only the type of the object is important.
template<typename Pars>
auto make_blank_argument_tuple(Pars) {
	auto provide_template_arg = [&] (auto tuple, auto arg_pair) {
		using argType = typename decltype(+hana::first(arg_pair))::type;
		return hana::concat(
			tuple, 
			hana::make_tuple(
				hana::make_pair(
					hana::second(arg_pair), 
					argType {}
		)	)	);
	};
	auto const pars = Pars::parameters; //this instantiation strips constexpr attribute; needed to do that explictely to avoid linking problems.
	//Compiler would strip the constexpr anyway in the next expression, but without this declaration it would not know how to link it (compiler bug?)
	return hana::fold_left(pars, hana::make_tuple(), provide_template_arg);
}

//Extracts argument tuple from function that can be inserted as a formal argument to our implementation to the named arguments
template<typename ArgTuple>
auto arg_tuple_2_map(ArgTuple arg_tuple) {
	return hana::unpack(arg_tuple, [](auto const&... pair) {
		return hana::make_map(pair...);
	});
}

