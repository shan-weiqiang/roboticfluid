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
owner.name = "John Doe"
owner.age = 20
print(f"Created owner: {owner.name} (age: {owner.age})")

# Create a pet
pet = Pet()
pet.name = "Buddy"
pet.age = 5
pet.weight = 25.5
pet.height = 45.2
pet.isVaccinated = True
pet.gender = 'M'
pet.owner = owner

# Set some arrays and vectors
pet.favoriteNumbers = [1, 2, 3]
pet.coordinates = [10.5, 20.3]
pet.tricks = ["sit", "stay", "roll"]
pet.scores = [85, 92, 78]

print(f"Created pet: {pet.name} (age: {pet.age}, weight: {pet.weight})")
print(f"Pet owner: {pet.owner.name}")
print(f"Pet tricks: {list(pet.tricks)}")
print(f"Pet favorite numbers: {list(pet.favoriteNumbers)}")

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
print(f"Deserialized pet name: {new_pet.name}")
print(f"Deserialized pet age: {new_pet.age}")

print("\n=== Testing round-trip serialization/deserialization ===")
pet.name = "Fido"
pet.age = 42
pet.weight = 12.5

serialized = pet.serialize()
print("Serialized:", serialized)

new_pet = Pet()
new_pet.deserialize(serialized)
print("Deserialized name:", new_pet.name)
print("Deserialized age:", new_pet.age)
print("Deserialized weight:", new_pet.weight)

assert new_pet.name == pet.name
assert new_pet.age == pet.age
assert abs(new_pet.weight - pet.weight) < 1e-6
print("✓ Round-trip test passed!")

print("\n✓ All basic tests passed!") 