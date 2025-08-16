#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "roboticfluid_cpp/rf_owner/owner_v2.hpp"

namespace rf_owner {

void init_type_owner_v2(pybind11::module_ &m) {
    pybind11::class_<OwnerV2>(m, "OwnerV2")
        .def(pybind11::init<>())
        .def_readwrite("name", &OwnerV2::name)
        .def_readwrite("age", &OwnerV2::age)
        .def("get_name", [](const OwnerV2& self) { return pybind11::bytes(self.get_name()); })
        .def("set_name", &OwnerV2::set_name)
        .def("get_age", &OwnerV2::get_age)
        .def("set_age", &OwnerV2::set_age)
        .def("dump", [](const OwnerV2& self) {
            std::vector<uint8_t> out;
            self.dump(out);
            return pybind11::bytes(reinterpret_cast<const char*>(out.data()), out.size());
        })
        .def("load", [](OwnerV2& self, const pybind11::bytes& src) {
            std::string s = static_cast<std::string>(src);
            std::vector<uint8_t> buf(s.begin(), s.end());
            self.load(buf);
        })
        .def("dump_compressed", [](const OwnerV2& self) {
            std::vector<uint8_t> out;
            self.dump_compressed(out);
            return pybind11::bytes(reinterpret_cast<const char*>(out.data()), out.size());
        })
        .def("load_compressed", [](OwnerV2& self, const pybind11::bytes& src) {
            std::string s = static_cast<std::string>(src);
            std::vector<uint8_t> buf(s.begin(), s.end());
            return self.load_compressed(buf);
        });
}

} // namespace rf_owner 