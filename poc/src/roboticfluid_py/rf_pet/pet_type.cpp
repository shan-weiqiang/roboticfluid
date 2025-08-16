#include <pybind11/pybind11.h>
#include "roboticfluid_cpp/rf_pet/pet_type.hpp"

namespace rf_pet {

void init_type_pet_type(pybind11::module_ &m) {
    // Bind the PetType enum
    pybind11::enum_<PetType>(m, "PetType")
        .value("DOG", PetType::DOG)
        .value("CAT", PetType::CAT)
        .value("BIRD", PetType::BIRD)
        .value("FISH", PetType::FISH)
        .value("HAMSTER", PetType::HAMSTER)
        .value("RABBIT", PetType::RABBIT)
        .value("SNAKE", PetType::SNAKE)
        .value("LIZARD", PetType::LIZARD)
        .value("FERRET", PetType::FERRET)
        .value("GUINEA_PIG", PetType::GUINEA_PIG);
}

} // namespace rf_pet 