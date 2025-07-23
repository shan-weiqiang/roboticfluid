import sys
import os

# Add the build directory to the Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build'))

try:
    from example import Pet, Owner
    print("✓ Successfully imported Pet and Owner classes")
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
# pet.set_isvaccinated(True)  # If you have isvaccinated, otherwise skip
# pet.set_gender('M')         # If you have gender, otherwise skip
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

print(f"Created pet: {pet.get_s()} (age: {pet.get_i32()}, weight: {pet.get_f()})")
print(f"Pet owner: {pet.get_own().get_name()}")
print(f"Pet tricks: {pet.get_vec_s()}")
print(f"Pet favorite numbers: {pet.get_arr_i32()}")

# Test the bark method
print("\nTesting bark method:")
pet.bark()

# Test serialization
print("\n=== Testing serialization ===")
serialized = pet.serialize()
print(f"Serialized pet: {serialized}")

# Test deserialization
print("\n=== Testing deserialization ===")
new_pet = Pet()
new_pet.deserialize(serialized)
print(f"Deserialized pet name: {new_pet.get_s()}")
print(f"Deserialized pet age: {new_pet.get_i32()}")

print("\n=== Testing round-trip serialization/deserialization ===")
pet.set_s("Fido")
pet.set_i32(42)
pet.set_f(12.5)

serialized = pet.serialize()
print("Serialized:", serialized)

new_pet = Pet()
new_pet.deserialize(serialized)
print("Deserialized name:", new_pet.get_s())
print("Deserialized age:", new_pet.get_i32())
print("Deserialized weight:", new_pet.get_f())

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
serialized = pet.serialize()
new_pet = Pet()
new_pet.deserialize(serialized)
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

print("\n✓ All basic tests passed!") 