// NOTE: Requires pybind11 headers to be available in the include path for successful compilation.
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include "../include/shared_struct.hpp"

namespace py = pybind11;

// Helper: Expose std::array as numpy array (zero-copy), except for bool
// General case
template <typename T, size_t N>
py::array_t<T> array_to_numpy(std::array<T, N>& arr) {
    return py::array_t<T>(N, arr.data(), py::cast(&arr));
}
// Specialization for bool: return as list
inline py::list array_to_numpy(std::array<bool, 4>& arr) {
    py::list l;
    for (bool v : arr) l.append(v);
    return l;
}

// Helper: Expose std::vector as numpy array (zero-copy), except for bool
// General case
template <typename T>
py::array_t<T> vector_to_numpy(std::vector<T>& vec) {
    return py::array_t<T>(vec.size(), vec.data(), py::cast(&vec));
}
// Specialization for bool: return as list
inline py::list vector_to_numpy(std::vector<bool>& vec) {
    py::list l;
    for (bool v : vec) l.append(v);
    return l;
}

PYBIND11_MODULE(roboticfluid, m) {
    py::class_<CustomType>(m, "CustomType")
        .def(py::init<>())
        .def_property("a", &CustomType::get_a, &CustomType::set_a)
        .def_property("b", &CustomType::get_b, &CustomType::set_b);

    py::class_<SharedStruct>(m, "SharedStruct", py::buffer_protocol())
        .def(py::init<>())
        // Basic types
        .def_property("d", &SharedStruct::get_d, &SharedStruct::set_d)
        .def_property("f", &SharedStruct::get_f, &SharedStruct::set_f)
        .def_property("i32", &SharedStruct::get_i32, &SharedStruct::set_i32)
        .def_property("i64", &SharedStruct::get_i64, &SharedStruct::set_i64)
        .def_property("u32", &SharedStruct::get_u32, &SharedStruct::set_u32)
        .def_property("u64", &SharedStruct::get_u64, &SharedStruct::set_u64)
        .def_property("bval", &SharedStruct::get_bval, &SharedStruct::set_bval)
        .def_property("s", &SharedStruct::get_s, &SharedStruct::set_s)
        // Arrays as numpy arrays (zero-copy) or list for bool
        .def_property("arr_d", [](SharedStruct& self) { return array_to_numpy(self.arr_d); }, nullptr)
        .def_property("arr_f", [](SharedStruct& self) { return array_to_numpy(self.arr_f); }, nullptr)
        .def_property("arr_i32", [](SharedStruct& self) { return array_to_numpy(self.arr_i32); }, nullptr)
        .def_property("arr_i64", [](SharedStruct& self) { return array_to_numpy(self.arr_i64); }, nullptr)
        .def_property("arr_u32", [](SharedStruct& self) { return array_to_numpy(self.arr_u32); }, nullptr)
        .def_property("arr_u64", [](SharedStruct& self) { return array_to_numpy(self.arr_u64); }, nullptr)
        .def_property("arr_bval", [](SharedStruct& self) { return array_to_numpy(self.arr_bval); }, nullptr)
        // String arrays as list (no zero-copy)
        .def_property("arr_s", [](SharedStruct& self) { return py::cast(self.arr_s); }, nullptr)
        // Vectors as numpy arrays (zero-copy) or list for bool
        .def_property("vec_d", [](SharedStruct& self) { return vector_to_numpy(self.vec_d); }, nullptr)
        .def_property("vec_f", [](SharedStruct& self) { return vector_to_numpy(self.vec_f); }, nullptr)
        .def_property("vec_i32", [](SharedStruct& self) { return vector_to_numpy(self.vec_i32); }, nullptr)
        .def_property("vec_i64", [](SharedStruct& self) { return vector_to_numpy(self.vec_i64); }, nullptr)
        .def_property("vec_u32", [](SharedStruct& self) { return vector_to_numpy(self.vec_u32); }, nullptr)
        .def_property("vec_u64", [](SharedStruct& self) { return vector_to_numpy(self.vec_u64); }, nullptr)
        .def_property("vec_bval", [](SharedStruct& self) { return vector_to_numpy(self.vec_bval); }, nullptr)
        // String vectors as list (no zero-copy)
        .def_property("vec_s", [](SharedStruct& self) { return py::cast(self.vec_s); }, nullptr)
        // CustomType arrays and vectors as list (no zero-copy)
        .def_property("arr_custom", [](SharedStruct& self) { return py::cast(self.arr_custom); }, nullptr)
        .def_property("vec_custom", [](SharedStruct& self) { return py::cast(self.vec_custom); }, nullptr)
        // Expose full getter/setter coverage for all fields
        .def("get_arr_d", &SharedStruct::get_arr_d)
        .def("set_arr_d", &SharedStruct::set_arr_d)
        .def("get_arr_f", &SharedStruct::get_arr_f)
        .def("set_arr_f", &SharedStruct::set_arr_f)
        .def("get_arr_i32", &SharedStruct::get_arr_i32)
        .def("set_arr_i32", &SharedStruct::set_arr_i32)
        .def("get_arr_i64", &SharedStruct::get_arr_i64)
        .def("set_arr_i64", &SharedStruct::set_arr_i64)
        .def("get_arr_u32", &SharedStruct::get_arr_u32)
        .def("set_arr_u32", &SharedStruct::set_arr_u32)
        .def("get_arr_u64", &SharedStruct::get_arr_u64)
        .def("set_arr_u64", &SharedStruct::set_arr_u64)
        .def("get_arr_bval", &SharedStruct::get_arr_bval)
        .def("set_arr_bval", &SharedStruct::set_arr_bval)
        .def("get_arr_s", &SharedStruct::get_arr_s)
        .def("set_arr_s", &SharedStruct::set_arr_s)
        .def("get_vec_d", &SharedStruct::get_vec_d)
        .def("set_vec_d", &SharedStruct::set_vec_d)
        .def("get_vec_f", &SharedStruct::get_vec_f)
        .def("set_vec_f", &SharedStruct::set_vec_f)
        .def("get_vec_i32", &SharedStruct::get_vec_i32)
        .def("set_vec_i32", &SharedStruct::set_vec_i32)
        .def("get_vec_i64", &SharedStruct::get_vec_i64)
        .def("set_vec_i64", &SharedStruct::set_vec_i64)
        .def("get_vec_u32", &SharedStruct::get_vec_u32)
        .def("set_vec_u32", &SharedStruct::set_vec_u32)
        .def("get_vec_u64", &SharedStruct::get_vec_u64)
        .def("set_vec_u64", &SharedStruct::set_vec_u64)
        .def("get_vec_bval", &SharedStruct::get_vec_bval)
        .def("set_vec_bval", &SharedStruct::set_vec_bval)
        .def("get_vec_s", &SharedStruct::get_vec_s)
        .def("set_vec_s", &SharedStruct::set_vec_s)
        .def("get_arr_custom", &SharedStruct::get_arr_custom)
        .def("set_arr_custom", &SharedStruct::set_arr_custom)
        .def("get_vec_custom", &SharedStruct::get_vec_custom)
        .def("set_vec_custom", &SharedStruct::set_vec_custom)
        // Static method to create from pointer (for shared memory)
        .def_static("from_address", [](uintptr_t addr) {
            return reinterpret_cast<SharedStruct*>(addr);
        }, py::return_value_policy::reference);
} 