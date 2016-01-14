#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include "PrisonersDilemma.h"



BOOST_PYTHON_MODULE(evolution)
{
	using namespace boost::python;

	class_<PrisonersDilemma>("PrisonersDilemma", init<std::string, int>(args("hist", "iterationNumber"), "__init__ docstring"))
		.def("solve", &PrisonersDilemma::solve)
		.def("getFitnesses", &PrisonersDilemma::getFitnesses)
		.def("getCoeff", &PrisonersDilemma::getCoeffs)
		;

	class_< std::vector<double> >("Fitnesses")
		.def(vector_indexing_suite< std::vector<double> >())
		;
}