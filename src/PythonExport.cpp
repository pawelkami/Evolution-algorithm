#include <boost/python.hpp>

std::string getName()
{
	return "test";
}

BOOST_PYTHON_MODULE(evolution)
{
	boost::python::def("getName", getName);
}