#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roboticfluid_cpp/owner_v4.hpp"

PYBIND11_MODULE(owner_v4, m) {
    pybind11::class_<OwnerV4>(m, "OwnerV4")
        .def(pybind11::init<>())
        .def_readwrite("name", &OwnerV4::name)
        .def_readwrite("age", &OwnerV4::age)
        .def("get_name", &OwnerV4::get_name)
        .def("set_name", &OwnerV4::set_name)
        .def("get_age", &OwnerV4::get_age)
        .def("set_age", &OwnerV4::set_age)
        .def("freeze", [](const OwnerV4& self) { return pybind11::bytes(self.freeze()); })
        .def("melt", [](OwnerV4& self, const pybind11::bytes& src) {
            return self.melt(std::string(src));
        });
} 
