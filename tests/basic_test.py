import sys
import os

# Add the build directory to the Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build', 'roboticfluid', 'lib'))
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build', 'roboticfluid'))

try:
    from roboticfluid_py.rf_owner import Owner, OwnerV2
    from roboticfluid_py.rf_pet import Pet, PetType
    from roboticfluid_py.rf_owner.nested import OwnerV3
    from roboticfluid_py import OwnerV4
    print("✓ Successfully imported Pet, Owner, OwnerV2, OwnerV3, OwnerV4 classes and PetType enum")
except ImportError as e:
    print(f"✗ Failed to import: {e}")
    sys.exit(1)

# Test basic functionality
print("\n=== Testing basic Pet and Owner functionality ===")

# Create an owner
owner = Owner()
owner.set_name("John Doe")
owner.set_age(20)
print(f"Created owner: {owner.get_name()} (age: {owner.get_age()})")

# Create a pet
pet = Pet()
pet.set_s("Buddy")
pet.set_i32(5)
pet.set_f(25.5)
pet.set_d(45.2)
pet.set_own(owner)

# Set some arrays and vectors
pet.set_arr_d([1.1, 2.2])
pet.set_arr_f([3.3, 4.4])
pet.set_arr_i32([10, 20])
pet.set_arr_i64([100, 200])
pet.set_arr_u32([1000, 2000])
pet.set_arr_u64([10000, 20000])
pet.set_arr_bval([True, False])
pet.set_arr_s(["a", "b"])
pet.set_vec_d([5.5, 6.6, 7.7])
pet.set_vec_f([8.8, 9.9])
pet.set_vec_i32([30, 40, 50])
pet.set_vec_i64([300, 400])
pet.set_vec_u32([3000, 4000])
pet.set_vec_u64([30000, 40000])
pet.set_vec_bval([False, True, True])
pet.set_vec_s(["x", "y", "z"])

# Set arr_u8
pet.set_arr_u8([i for i in range(100)])
print(f"Pet arr_u8: {pet.get_arr_u8()[:10]} ... (len={len(pet.get_arr_u8())})")

print(f"Created pet: {pet.get_s()} (age: {pet.get_i32()}, weight: {pet.get_f()})")
print(f"Pet owner: {pet.get_own().get_name()}")
print(f"Pet tricks: {pet.get_vec_s()}")
print(f"Pet favorite numbers: {pet.get_arr_i32()}")

# Test enum functionality
pet.set_pet_type(PetType.DOG)
pet.set_arr_pet_type([PetType.CAT, PetType.BIRD])
pet.set_vec_pet_type([PetType.FISH, PetType.HAMSTER, PetType.RABBIT])
print(f"Pet type: {pet.get_pet_type()}")
print(f"Pet type array: {pet.get_arr_pet_type()}")
print(f"Pet type vector: {pet.get_vec_pet_type()}")

# Test the bark method
print("\nTesting bark method:")
pet.bark()

# Test freezing
print("\n=== Testing freezing ===")
freezed = pet.freeze()
print(f"Freezed pet: {freezed}")

# Test melting
print("\n=== Testing melting ===")
new_pet = Pet()
new_pet.melt(freezed)
print(f"Melted s: {new_pet.get_s()}")
print(f"Melted i32: {new_pet.get_i32()}")
print(f"Melted arr_u8[:10]: {new_pet.get_arr_u8()[:10]}")
assert new_pet.get_arr_u8() == [i for i in range(100)]

print("\n=== Testing round-trip freezing/melting ===")
pet.set_s("Fido")
pet.set_i32(42)
pet.set_f(12.5)

freezed = pet.freeze()
print("Freezed:", freezed)

new_pet = Pet()
new_pet.melt(freezed)
print("Melted s:", new_pet.get_s())
print("Melted i32:", new_pet.get_i32())
print("Melted f:", new_pet.get_f())

assert new_pet.get_s() == pet.get_s()
assert new_pet.get_i32() == pet.get_i32()
assert abs(new_pet.get_f() - pet.get_f()) < 1e-6
print("✓ Round-trip test passed!")

print("\n=== Testing custom Owner members ===")
owner1 = Owner(); owner1.set_name("Alice"); owner1.set_age(30)
owner2 = Owner(); owner2.set_name("Bob"); owner2.set_age(40)
pet = Pet()
pet.set_own(owner1)
arr_owners = [Owner() for _ in range(10)]
for i, o in enumerate(arr_owners):
    o.set_name(f"ArrOwner{i}")
    o.set_age(100 + i)
pet.set_arr_own(arr_owners)
vec_owners = [Owner() for _ in range(3)]
for i, o in enumerate(vec_owners):
    o.set_name(f"VecOwner{i}")
    o.set_age(200 + i)
pet.set_vec_own(vec_owners)
freezed = pet.freeze()
new_pet = Pet()
new_pet.melt(freezed)
assert new_pet.get_own().get_name() == "Alice"
assert new_pet.get_own().get_age() == 30
arr_owners_new = new_pet.get_arr_own()
for i, o in enumerate(arr_owners_new):
    assert o.get_name() == f"ArrOwner{i}"
    assert o.get_age() == 100 + i
vec_owners_new = new_pet.get_vec_own()
for i, o in enumerate(vec_owners_new):
    assert o.get_name() == f"VecOwner{i}"
    assert o.get_age() == 200 + i
print("✓ Custom Owner members round-trip test passed!")

print("\n=== Testing PetType enum round-trip ===")
pet = Pet()
pet.set_pet_type(PetType.SNAKE)
pet.set_arr_pet_type([PetType.LIZARD, PetType.FERRET])
pet.set_vec_pet_type([PetType.GUINEA_PIG, PetType.DOG, PetType.CAT])
freezed = pet.freeze()
new_pet = Pet()
new_pet.melt(freezed)
assert new_pet.get_pet_type() == PetType.SNAKE
assert new_pet.get_arr_pet_type() == [PetType.LIZARD, PetType.FERRET]
assert new_pet.get_vec_pet_type() == [PetType.GUINEA_PIG, PetType.DOG, PetType.CAT]
print("✓ PetType enum round-trip test passed!")

print("\n=== Testing OwnerV2 ===")
ownerv2 = OwnerV2()
ownerv2.set_name("Jane Smith")
ownerv2.set_age(33)
print(f"Created OwnerV2: {ownerv2.get_name()} (age: {ownerv2.get_age()})")
assert ownerv2.get_name() == "Jane Smith"
assert ownerv2.get_age() == 33
print("✓ OwnerV2 test passed!")

print("\n=== Testing OwnerV3 ===")
ownerv3 = OwnerV3()
ownerv3.set_name("Nested User")
ownerv3.set_age(44)
print(f"Created OwnerV3: {ownerv3.get_name()} (age: {ownerv3.get_age()})")
assert ownerv3.get_name() == "Nested User"
assert ownerv3.get_age() == 44
print("✓ OwnerV3 test passed!")

print("\n=== Testing OwnerV4 ===")
ownerv4 = OwnerV4()
ownerv4.set_name("Top User")
ownerv4.set_age(55)
print(f"Created OwnerV4: {ownerv4.get_name()} (age: {ownerv4.get_age()})")
assert ownerv4.get_name() == "Top User"
assert ownerv4.get_age() == 55
print("✓ OwnerV4 test passed!")

print("\n✓ All basic tests passed!") 