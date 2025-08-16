#include <pybind11/pybind11.h>

namespace rf_pet {
void init_type_pet(pybind11::module_ &m);
void init_type_pet_type(pybind11::module_ &m);
}

PYBIND11_MODULE(rf_pet, m) {
    rf_pet::init_type_pet_type(m);
    rf_pet::init_type_pet(m);
} 