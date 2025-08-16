import unittest
import sys
import os

# Add build directory to sys.path for import
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build', 'roboticfluid', 'lib'))

from roboticfluid_py.rf_owner import Owner

class TestOwner(unittest.TestCase):
    def setUp(self):
        self.owner = Owner()

    def test_set_and_get_name(self):
        self.owner.set_name("John Doe")
        self.assertEqual(self.owner.get_name().decode('utf-8'), "John Doe")
        self.owner.set_name("")
        self.assertEqual(self.owner.get_name().decode('utf-8'), "")

    def test_set_and_get_age(self):
        self.owner.set_age(25)
        self.assertEqual(self.owner.get_age(), 25)
        self.owner.set_age(0)
        self.assertEqual(self.owner.get_age(), 0)

    def test_type_errors(self):
        with self.assertRaises(TypeError):
            self.owner.set_name(123)
        with self.assertRaises(TypeError):
            self.owner.set_age("not an int")

    def test_freeze_and_melt(self):
        self.owner.set_name("Alice")
        self.owner.set_age(42)
        freezed = self.owner.dump()
        new_owner = Owner()
        new_owner.load(freezed)
        self.assertEqual(new_owner.get_name().decode('utf-8'), "Alice")
        self.assertEqual(new_owner.get_age(), 42)

        # Edge case: empty name, zero age
        self.owner.set_name("")
        self.owner.set_age(0)
        freezed = self.owner.dump()
        new_owner = Owner()
        new_owner.load(freezed)
        self.assertEqual(new_owner.get_name().decode('utf-8'), "")
        self.assertEqual(new_owner.get_age(), 0)


if __name__ == "__main__":
    unittest.main() 