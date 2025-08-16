#include <pybind11/pybind11.h>

namespace rf_owner {
namespace nested {
void init_type_owner_v3(pybind11::module_ &m);
}

void init_submodule_nested(pybind11::module_ &m) {
    auto m_nested = m.def_submodule("nested", "Bindings for rf_owner::nested namespace");
    rf_owner::nested::init_type_owner_v3(m_nested);
}

} // namespace rf_owner 