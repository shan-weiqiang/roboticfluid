#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roboticfluid_cpp/rf_owner/nested/owner_v3.hpp"

namespace rf_owner {
namespace nested {

void init_type_owner_v3(pybind11::module_ &m) {
    pybind11::class_<OwnerV3>(m, "OwnerV3")
        .def(pybind11::init<>())
        .def_readwrite("name", &OwnerV3::name)
        .def_readwrite("age", &OwnerV3::age)
        .def("get_name", &OwnerV3::get_name)
        .def("set_name", &OwnerV3::set_name)
        .def("get_age", &OwnerV3::get_age)
        .def("set_age", &OwnerV3::set_age);
}

} // namespace nested
} // namespace rf_owner 