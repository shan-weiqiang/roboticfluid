#include <pybind11/pybind11.h>

void init_pet(pybind11::module_ &m);

PYBIND11_MODULE(rf_pet, m) {
    init_pet(m);
} 