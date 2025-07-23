#include <pybind11/pybind11.h>
#include "shared_struct.hpp"

void init_owner_v2(pybind11::module_ &m) {
    pybind11::class_<rf_owner::OwnerV2>(m, "OwnerV2")
        .def(pybind11::init<>())
        .def_readwrite("name", &rf_owner::OwnerV2::name)
        .def_readwrite("age", &rf_owner::OwnerV2::age)
        .def("get_name", &rf_owner::OwnerV2::get_name)
        .def("set_name", &rf_owner::OwnerV2::set_name)
        .def("get_age", &rf_owner::OwnerV2::get_age)
        .def("set_age", &rf_owner::OwnerV2::set_age);
} 