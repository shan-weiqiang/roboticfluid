#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "shared_struct.hpp"

namespace py = pybind11;

PYBIND11_MODULE(rf_owner, m) {
    py::class_<rf_owner::Owner>(m, "Owner")
        .def(py::init<>())
        .def_readwrite("name", &rf_owner::Owner::name)
        .def_readwrite("age", &rf_owner::Owner::age)
        .def("get_name", &rf_owner::Owner::get_name)
        .def("set_name", &rf_owner::Owner::set_name)
        .def("get_age", &rf_owner::Owner::get_age)
        .def("set_age", &rf_owner::Owner::set_age);
} 