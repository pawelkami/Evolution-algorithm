#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "PrisonersDilemma.h"

BOOST_PYTHON_MODULE(evolution)
{
	using namespace boost::python;

	class_<PrisonersDilemma>("PrisonersDilemma", init<std::string>(args("hist"), "__init__ docstring"))
		.def("solve", &PrisonersDilemma::solve)
		.def("getFitnesses", &PrisonersDilemma::getFitnesses)
		;

	class_< std::vector<int> >("Fitnesses")
		.def(vector_indexing_suite< std::vector<int> >())
		;
}