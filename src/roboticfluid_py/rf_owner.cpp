#include <pybind11/pybind11.h>

namespace rf_owner {
void init_type_owner(pybind11::module_ &m);
void init_type_owner_v2(pybind11::module_ &m);
void init_submodule_nested(pybind11::module_ &m);
}

PYBIND11_MODULE(rf_owner, m) {
    rf_owner::init_type_owner(m);
    rf_owner::init_type_owner_v2(m);
    rf_owner::init_submodule_nested(m);
} 