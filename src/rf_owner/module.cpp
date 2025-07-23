#include <pybind11/pybind11.h>

void init_owner(pybind11::module_ &m);
void init_owner_v2(pybind11::module_ &m);
void init_nested(pybind11::module_ &m);

PYBIND11_MODULE(rf_owner, m) {
    init_owner(m);
    init_owner_v2(m);
    init_nested(m);
} 