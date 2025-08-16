#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roboticfluid_cpp/rf_owner/owner.hpp"

namespace rf_owner {

void init_type_owner(pybind11::module_ &m) {
    pybind11::class_<Owner>(m, "Owner")
        .def(pybind11::init<>())
        .def_readwrite("name", &Owner::name)
        .def_readwrite("age", &Owner::age)
        .def("get_name", [](const Owner& self) { return pybind11::bytes(self.get_name()); })
        .def("set_name", &Owner::set_name)
        .def("get_age", &Owner::get_age)
        .def("set_age", &Owner::set_age)
        .def("dump", [](const Owner& self) {
            std::vector<uint8_t> out;
            self.dump(out);
            return pybind11::bytes(reinterpret_cast<const char*>(out.data()), out.size());
        })
        .def("load", [](Owner& self, const pybind11::bytes& src) {
            std::string s = static_cast<std::string>(src);
            std::vector<uint8_t> buf(s.begin(), s.end());
            self.load(buf);
        })
        .def("dump_compressed", [](const Owner& self) {
            std::vector<uint8_t> out;
            self.dump_compressed(out);
            return pybind11::bytes(reinterpret_cast<const char*>(out.data()), out.size());
        })
        .def("load_compressed", [](Owner& self, const pybind11::bytes& src) {
            std::string s = static_cast<std::string>(src);
            std::vector<uint8_t> buf(s.begin(), s.end());
            return self.load_compressed(buf);
        });
}

} // namespace rf_owner 