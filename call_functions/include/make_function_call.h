#pragma once
//This header is intended to be included in the translation unit that calls (not defines) the function with named parameters.
#include <boost/hana/string.hpp>
#include <boost/hana/map.hpp>
#include <boost/hana/size.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/pair.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/unpack.hpp>
#include <boost/hana/concat.hpp>
#include <boost/hana/at_key.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


//Calls function Fun::fun_positional that is defined using standard positional arguments.
//Arguments passed to the function consist of positional arguments (optional parameter pack args) 
//followed by the values picked up from the argument map (parameter argmap) based on the parameter declaration
//contained in the definition of the Fun structure. 
//
//Function makes sure that the order of the arguments agrees with the Fun's definition
//Function checks types of the passed arguments.
//Function checks number of positional arguments.
//Definition of the Fun::fun_positional need not be in the same translation unit as the caller. 
template<typename ArgMap, typename Fun, typename... PositionalArgs>
auto call_by_position(ArgMap argmap, Fun, PositionalArgs... args) {
	auto get_and_test = [&] (auto tuple, auto arg_pair) {
		using req_type = typename decltype(+hana::first(arg_pair))::type;
		using actual_type = typename std::remove_reference<decltype(argmap[hana::second(arg_pair)])>::type;
		static_assert(std::is_same<req_type,actual_type>::value, "Not-matching arguments");
		return hana::concat(tuple, hana::make_tuple(argmap[hana::second(arg_pair)]));
	};
	constexpr auto pars = Fun::Parameters::parameters;
	auto positional_arguments = hana::make_tuple(args...);
	static_assert(hana::size(positional_arguments)==Fun::Parameters::arg_offset, "Number of positional arguments does not match");
	auto arguments_tuple = hana::concat(positional_arguments, hana::fold_left(pars, hana::make_tuple(), get_and_test));
	return(hana::unpack(arguments_tuple, Fun::fun_positional));
}

//Calls function Fun::fun_named and passes it a tuple of all named arguments. Separate function can be used to convert this tuple
//to the hana::map that is convenient compile-time container for arguments.
//
//Arguments passed to the function consist of positional arguments (optional parameter pack args) 
//followed tuple of arguments as the final argument to the function Fun::fun_named
//
//Why hana::tuple of arguments instead of hana::map? Good question. It is because documentation of Hana::map makes it clear, that 
//the actual layout of the map is implementation-specific and cannot be relied on.
//
//Function checks types of the passed arguments.
//Function checks number of positional arguments.
//Definition of the Fun::fun_named need not be in the same translation unit as the caller. 
template<typename Map, typename Fun, typename... Args>
auto call_by_name(Map map, Fun, Args... args) {
	auto get_and_test = [&] (auto tuple, auto arg_pair) {
		using req_type = typename decltype(+hana::first(arg_pair))::type;
		using actual_type = typename std::remove_reference<decltype(map[hana::second(arg_pair)])>::type;
		static_assert(std::is_same<req_type,actual_type>::value, "Not-matching arguments");
		return hana::concat(tuple, 
			hana::make_tuple(
				hana::make_pair(
					hana::second(arg_pair),
					map[hana::second(arg_pair)]
		)	)	);
	};
	constexpr auto pars = Fun::Parameters::parameters;
	auto positional_arguments = hana::make_tuple(args...);
	static_assert(hana::size(positional_arguments)==Fun::Parameters::arg_offset, "Number of positional arguments does not match");
	auto arguments_tuple = hana::concat(
		positional_arguments, 
		hana::make_tuple(
			hana::fold_left(
				pars, 
				hana::make_tuple(), 
				get_and_test
	)	)	); 
	
	return(hana::unpack(arguments_tuple, Fun::fun_named));
}
