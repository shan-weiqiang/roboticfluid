#include <pybind11/pybind11.h>
#include "shared_struct.hpp"

void init_owner(pybind11::module_ &m) {
    pybind11::class_<rf_owner::Owner>(m, "Owner")
        .def(pybind11::init<>())
        .def_readwrite("name", &rf_owner::Owner::name)
        .def_readwrite("age", &rf_owner::Owner::age)
        .def("get_name", &rf_owner::Owner::get_name)
        .def("set_name", &rf_owner::Owner::set_name)
        .def("get_age", &rf_owner::Owner::get_age)
        .def("set_age", &rf_owner::Owner::set_age);
} 