#include <boost/python.hpp>
#include "PrisonersDilemma.h"

std::string getName()
{
	return "test";
}

BOOST_PYTHON_MODULE(evolution)
{
	using namespace boost::python;
	def("getName", getName);

	class_<PrisonersDilemma>("PrisonersDilemma", init<std::string>(args("hist"), "__init__ docstring"))
		.def("solve", &PrisonersDilemma::solve)
		;
}