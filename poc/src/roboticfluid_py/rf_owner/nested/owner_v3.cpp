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
        .def("get_name", [](const OwnerV3& self) { return pybind11::bytes(self.get_name()); })
        .def("set_name", &OwnerV3::set_name)
        .def("get_age", &OwnerV3::get_age)
        .def("set_age", &OwnerV3::set_age)
        .def("dump", [](const OwnerV3& self) {
            std::vector<uint8_t> out;
            self.dump(out);
            return pybind11::bytes(reinterpret_cast<const char*>(out.data()), out.size());
        })
        .def("load", [](OwnerV3& self, const pybind11::bytes& src) {
            std::string s = static_cast<std::string>(src);
            std::vector<uint8_t> buf(s.begin(), s.end());
            self.load(buf);
        })
        .def("dump_compressed", [](const OwnerV3& self) {
            std::vector<uint8_t> out;
            self.dump_compressed(out);
            return pybind11::bytes(reinterpret_cast<const char*>(out.data()), out.size());
        })
        .def("load_compressed", [](OwnerV3& self, const pybind11::bytes& src) {
            std::string s = static_cast<std::string>(src);
            std::vector<uint8_t> buf(s.begin(), s.end());
            return self.load_compressed(buf);
        });
}

} // namespace nested
} // namespace rf_owner 