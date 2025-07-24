#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roboticfluid_cpp/rf_owner/owner.hpp"

namespace rf_owner {

void init_type_owner(pybind11::module_ &m) {
    pybind11::class_<Owner>(m, "Owner")
        .def(pybind11::init<>())
        .def_readwrite("name", &Owner::name)
        .def_readwrite("age", &Owner::age)
        .def("get_name", &Owner::get_name)
        .def("set_name", &Owner::set_name)
        .def("get_age", &Owner::get_age)
        .def("set_age", &Owner::set_age);
}

} // namespace rf_owner 