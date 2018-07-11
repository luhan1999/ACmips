#ifndef exception_hpp
#define exception_hpp
/*
   function:ÓÃÓÚÅ×³ö´íÎó
*/
#include <cstddef>
#include <cstring>
#include <string>
class exception
{
protected:
	const std::string variant = "";
	std::string detail = "";
public:
	exception() {}
	exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
	virtual std::string what() { return variant + " " + detail; }
};
class index_out_of_bound : public exception {};
class runtime_error : public exception {};
class invalid_program : public exception {};
class error : public exception {};
#endif
