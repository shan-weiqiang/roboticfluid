#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "shared_struct.hpp"

namespace py = pybind11;

PYBIND11_MODULE(example, m) {
    py::class_<Owner>(m, "Owner")
        .def(py::init<>())
        .def_readwrite("name", &Owner::name_)
        .def_readwrite("age", &Owner::age_)
        .def("getName", &Owner::getName)
        .def("setName", &Owner::setName)
        .def("getAge", &Owner::getAge)
        .def("setAge", &Owner::setAge);

    py::class_<Pet>(m, "Pet")
        .def(py::init<>())
        .def(py::init([](void* ptr) {
            return reinterpret_cast<Pet*>(ptr);
        }), py::arg("ptr"))
        .def_static("from_address", [](uintptr_t addr) {
            return reinterpret_cast<Pet*>(addr);
        }, py::arg("addr"))
        .def_readwrite("name", &Pet::name)
        .def_readwrite("age", &Pet::age)
        .def_readwrite("weight", &Pet::weight)
        .def_readwrite("height", &Pet::height)
        .def_readwrite("isVaccinated", &Pet::isVaccinated)
        .def_readwrite("gender", &Pet::gender)
        .def_readwrite("favoriteNumbers", &Pet::favoriteNumbers)
        .def_readwrite("coordinates", &Pet::coordinates)
        .def_readwrite("tricks", &Pet::tricks)
        .def_readwrite("scores", &Pet::scores)
        .def_readwrite("owner", &Pet::owner)
        .def_readwrite("multipleOwners", &Pet::multipleOwners)
        .def_readwrite("ownerList", &Pet::ownerList)
        .def("bark", &Pet::bark)
        .def("getName", &Pet::getName)
        .def("setName", &Pet::setName)
        .def("getAge", &Pet::getAge)
        .def("setAge", &Pet::setAge)
        .def("getWeight", &Pet::getWeight)
        .def("setWeight", &Pet::setWeight)
        .def("getHeight", &Pet::getHeight)
        .def("setHeight", &Pet::setHeight)
        .def("getIsVaccinated", &Pet::getIsVaccinated)
        .def("setIsVaccinated", &Pet::setIsVaccinated)
        .def("getGender", &Pet::getGender)
        .def("setGender", &Pet::setGender)
        .def("getFavoriteNumbers", &Pet::getFavoriteNumbers, py::return_value_policy::reference_internal)
        .def("setFavoriteNumbers", &Pet::setFavoriteNumbers)
        .def("getCoordinates", &Pet::getCoordinates, py::return_value_policy::reference_internal)
        .def("setCoordinates", &Pet::setCoordinates)
        .def("getTricks", &Pet::getTricks, py::return_value_policy::reference_internal)
        .def("setTricks", &Pet::setTricks)
        .def("getScores", &Pet::getScores, py::return_value_policy::reference_internal)
        .def("setScores", &Pet::setScores)
        .def("getOwner", &Pet::getOwner, py::return_value_policy::reference_internal)
        .def("setOwner", &Pet::setOwner)
        .def("getMultipleOwners", &Pet::getMultipleOwners, py::return_value_policy::reference_internal)
        .def("setMultipleOwners", &Pet::setMultipleOwners)
        .def("getOwnerList", &Pet::getOwnerList, py::return_value_policy::reference_internal)
        .def("setOwnerList", &Pet::setOwnerList)
        .def("serialize", [](const Pet& pet) { return py::bytes(pet.serialize()); })
        .def("deserialize", [](Pet& pet, const py::bytes& src) {
            pet.deserialize(std::string(src));
        });
}