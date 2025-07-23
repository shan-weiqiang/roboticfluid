#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "shared_struct.hpp"

void init_owner_v3(pybind11::module_ &m) {
    pybind11::class_<rf_owner::nested::OwnerV3>(m, "OwnerV3")
        .def(pybind11::init<>())
        .def_readwrite("name", &rf_owner::nested::OwnerV3::name)
        .def_readwrite("age", &rf_owner::nested::OwnerV3::age)
        .def("get_name", &rf_owner::nested::OwnerV3::get_name)
        .def("set_name", &rf_owner::nested::OwnerV3::set_name)
        .def("get_age", &rf_owner::nested::OwnerV3::get_age)
        .def("set_age", &rf_owner::nested::OwnerV3::set_age);
} 