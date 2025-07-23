#include <pybind11/pybind11.h>

void init_owner_v3(pybind11::module_ &m);

void init_nested(pybind11::module_ &m) {
    auto m_nested = m.def_submodule("nested", "Bindings for rf_owner::nested namespace");
    init_owner_v3(m_nested);
} 