#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roboticfluid_cpp/rf_owner/owner_v2.hpp"

namespace rf_owner {

void init_type_owner_v2(pybind11::module_ &m) {
    pybind11::class_<OwnerV2>(m, "OwnerV2")
        .def(pybind11::init<>())
        .def_readwrite("name", &OwnerV2::name)
        .def_readwrite("age", &OwnerV2::age)
        .def("get_name", &OwnerV2::get_name)
        .def("set_name", &OwnerV2::set_name)
        .def("get_age", &OwnerV2::get_age)
        .def("set_age", &OwnerV2::set_age)
        .def("freeze", [](const OwnerV2& self) { return pybind11::bytes(self.freeze()); })
        .def("melt", [](OwnerV2& self, const pybind11::bytes& src) {
            return self.melt(std::string(src));
        });
}

} // namespace rf_owner 