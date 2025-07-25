import unittest
import sys
import os

# Add build directory to sys.path for import
sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..', 'build','roboticfluid',  'lib'))

from roboticfluid_py.rf_pet import Pet
from roboticfluid_py.rf_owner import Owner

class TestPet(unittest.TestCase):
    def setUp(self):
        self.pet = Pet()
        self.owner = Owner()
        self.owner.set_name("Alice")
        self.owner.set_age(30)

    def assertListAlmostEqual(self, list1, list2, places=6):
        self.assertEqual(len(list1), len(list2))
        for a, b in zip(list1, list2):
            self.assertAlmostEqual(a, b, places=places)

    def test_d(self):
        self.pet.set_d(1.23)
        self.assertEqual(self.pet.get_d(), 1.23)

    def test_f(self):
        self.pet.set_f(2.34)
        self.assertAlmostEqual(self.pet.get_f(), 2.34, places=5)

    def test_i32(self):
        self.pet.set_i32(123)
        self.assertEqual(self.pet.get_i32(), 123)

    def test_i64(self):
        self.pet.set_i64(1234567890123)
        self.assertEqual(self.pet.get_i64(), 1234567890123)

    def test_u32(self):
        self.pet.set_u32(123456)
        self.assertEqual(self.pet.get_u32(), 123456)

    def test_u64(self):
        self.pet.set_u64(123456789012345)
        self.assertEqual(self.pet.get_u64(), 123456789012345)

    def test_bval(self):
        self.pet.set_bval(True)
        self.assertTrue(self.pet.get_bval())
        self.pet.set_bval(False)
        self.assertFalse(self.pet.get_bval())

    def test_s(self):
        self.pet.set_s("test string")
        self.assertEqual(self.pet.get_s(), "test string")

    def test_arr_d(self):
        arr = [1.1] * 10000
        arr[0] = 1.1
        arr[1] = 2.2
        self.pet.set_arr_d(arr)
        got = list(self.pet.get_arr_d())
        self.assertEqual(got[:2], [1.1, 2.2])
        self.assertEqual(len(got), 10000)

    def test_arr_f(self):
        arr = [3.3] * 10000
        arr[1] = 4.4
        self.pet.set_arr_f(arr)
        got = list(self.pet.get_arr_f())
        self.assertAlmostEqual(got[0], 3.3, places=6)
        self.assertAlmostEqual(got[1], 4.4, places=6)
        self.assertEqual(len(got), 10000)

    def test_arr_i32(self):
        arr = [10] * 10000
        arr[0] = 10
        arr[1] = 20
        self.pet.set_arr_i32(arr)
        got = list(self.pet.get_arr_i32())
        self.assertEqual(got[:2], [10, 20])
        self.assertEqual(len(got), 10000)

    def test_arr_i64(self):
        arr = [100] * 10000
        arr[0] = 100
        arr[1] = 200
        self.pet.set_arr_i64(arr)
        got = list(self.pet.get_arr_i64())
        self.assertEqual(got[:2], [100, 200])
        self.assertEqual(len(got), 10000)

    def test_arr_u32(self):
        arr = [1000] * 10000
        arr[0] = 1000
        arr[1] = 2000
        self.pet.set_arr_u32(arr)
        got = list(self.pet.get_arr_u32())
        self.assertEqual(got[:2], [1000, 2000])
        self.assertEqual(len(got), 10000)

    def test_arr_u64(self):
        arr = [10000] * 10000
        arr[0] = 10000
        arr[1] = 20000
        self.pet.set_arr_u64(arr)
        got = list(self.pet.get_arr_u64())
        self.assertEqual(got[:2], [10000, 20000])
        self.assertEqual(len(got), 10000)

    def test_arr_bval(self):
        arr = [True] * 10000
        arr[0] = True
        arr[1] = False
        self.pet.set_arr_bval(arr)
        got = list(self.pet.get_arr_bval())
        self.assertEqual(got[:2], [True, False])
        self.assertEqual(len(got), 10000)

    def test_arr_s(self):
        arr = ["a"] * 10000
        arr[0] = "a"
        arr[1] = "b"
        self.pet.set_arr_s(arr)
        got = list(self.pet.get_arr_s())
        self.assertEqual(got[:2], ["a", "b"])
        self.assertEqual(len(got), 10000)

    def test_vec_d(self):
        self.pet.set_vec_d([5.5, 6.6, 7.7])
        self.assertEqual(self.pet.get_vec_d(), [5.5, 6.6, 7.7])

    def test_vec_f(self):
        self.pet.set_vec_f([8.8, 9.9])
        self.assertListAlmostEqual(self.pet.get_vec_f(), [8.8, 9.9])

    def test_vec_i32(self):
        self.pet.set_vec_i32([30, 40, 50])
        self.assertEqual(self.pet.get_vec_i32(), [30, 40, 50])

    def test_vec_i64(self):
        self.pet.set_vec_i64([300, 400])
        self.assertEqual(self.pet.get_vec_i64(), [300, 400])

    def test_vec_u32(self):
        self.pet.set_vec_u32([3000, 4000])
        self.assertEqual(self.pet.get_vec_u32(), [3000, 4000])

    def test_vec_u64(self):
        self.pet.set_vec_u64([30000, 40000])
        self.assertEqual(self.pet.get_vec_u64(), [30000, 40000])

    def test_vec_bval(self):
        self.pet.set_vec_bval([False, True, True])
        self.assertEqual(self.pet.get_vec_bval(), [False, True, True])

    def test_vec_s(self):
        self.pet.set_vec_s(["x", "y", "z"])
        self.assertEqual(self.pet.get_vec_s(), ["x", "y", "z"])

    def test_set_and_get_owner(self):
        self.pet.set_own(self.owner)
        own = self.pet.get_own()
        self.assertEqual(own.get_name().decode('utf-8'), "Alice")
        self.assertEqual(own.get_age(), 30)

    def test_set_and_get_arrays(self):
        arr_d = [1.1] * 10000
        arr_d[0] = 1.1
        arr_d[1] = 2.2
        self.pet.set_arr_d(arr_d)
        arr_f = [3.3] * 10000
        arr_f[1] = 4.4
        self.pet.set_arr_f(arr_f)
        arr_i32 = [10] * 10000
        arr_i32[1] = 20
        self.pet.set_arr_i32(arr_i32)
        arr_i64 = [100] * 10000
        arr_i64[1] = 200
        self.pet.set_arr_i64(arr_i64)
        arr_u32 = [1000] * 10000
        arr_u32[1] = 2000
        self.pet.set_arr_u32(arr_u32)
        arr_u64 = [10000] * 10000
        arr_u64[1] = 20000
        self.pet.set_arr_u64(arr_u64)
        arr_bval = [True] * 10000
        arr_bval[1] = False
        self.pet.set_arr_bval(arr_bval)
        arr_s = ["a"] * 10000
        arr_s[1] = "b"
        self.pet.set_arr_s(arr_s)
        got = list(self.pet.get_arr_d())
        self.assertEqual(got[:2], [1.1, 2.2])
        got = list(self.pet.get_arr_f())
        self.assertAlmostEqual(got[0], 3.3, places=6)
        self.assertAlmostEqual(got[1], 4.4, places=6)
        got = list(self.pet.get_arr_i32())
        self.assertEqual(got[:2], [10, 20])
        got = list(self.pet.get_arr_i64())
        self.assertEqual(got[:2], [100, 200])
        got = list(self.pet.get_arr_u32())
        self.assertEqual(got[:2], [1000, 2000])
        got = list(self.pet.get_arr_u64())
        self.assertEqual(got[:2], [10000, 20000])
        got = list(self.pet.get_arr_bval())
        self.assertEqual(got[:2], [True, False])
        got = list(self.pet.get_arr_s())
        self.assertEqual(got[:2], ["a", "b"])
        self.assertEqual(len(got), 10000)

    def test_set_and_get_owner_arrays(self):
        from roboticfluid_py.rf_owner import Owner
        owners = [Owner() for _ in range(10000)]
        for i, o in enumerate(owners[:10]):
            o.set_name(f"ArrOwner{i}")
            o.set_age(100 + i)
        self.pet.set_arr_own(owners)
        arr_owners_new = self.pet.get_arr_own()
        self.assertEqual(len(arr_owners_new), 10000)
        for i, o in enumerate(arr_owners_new[:10]):
            self.assertEqual(o.get_name().decode('utf-8'), f"ArrOwner{i}")
            self.assertEqual(o.get_age(), 100 + i)

    def test_set_and_get_owner_vectors(self):
        # Test set_vec_own and get_vec_own
        owners = []
        for i in range(2):
            o = Owner()
            o.set_name(f"VecOwner{i}")
            o.set_age(200 + i)
            owners.append(o)
        self.pet.set_vec_own(owners)
        vec_owners_new = self.pet.get_vec_own()
        self.assertEqual(len(vec_owners_new), 2)
        for i, o in enumerate(vec_owners_new):
            self.assertEqual(o.get_name().decode('utf-8'), f"VecOwner{i}")
            self.assertEqual(o.get_age(), 200 + i)

    def test_type_errors(self):
        with self.assertRaises(TypeError):
            self.pet.set_s(123)
        with self.assertRaises(TypeError):
            self.pet.set_i32("not an int")
        with self.assertRaises(TypeError):
            self.pet.set_arr_d(["not", "floats"])
        with self.assertRaises(TypeError):
            self.pet.set_vec_s([1, 2, 3])

    def test_own(self):
        from roboticfluid_py.rf_owner import Owner
        o = Owner()
        o.set_name("TestOwner")
        o.set_age(11)
        self.pet.set_own(o)
        got = self.pet.get_own()
        self.assertEqual(got.get_name().decode('utf-8'), "TestOwner")
        self.assertEqual(got.get_age(), 11)

    def test_arr_own(self):
        from roboticfluid_py.rf_owner import Owner
        arr = [Owner() for _ in range(10000)]
        for i, o in enumerate(arr[:2]):
            o.set_name(f"ArrOwner{i}")
            o.set_age(i)
        self.pet.set_arr_own(arr)
        got = self.pet.get_arr_own()
        self.assertEqual(len(got), 10000)
        self.assertEqual(got[0].get_name().decode('utf-8'), "ArrOwner0")
        self.assertEqual(got[1].get_name().decode('utf-8'), "ArrOwner1")

    def test_vec_own(self):
        from roboticfluid_py.rf_owner import Owner
        vec = []
        for i in range(3):
            o = Owner()
            o.set_name(f"VecOwner{i}")
            o.set_age(i+10)
            vec.append(o)
        self.pet.set_vec_own(vec)
        got = self.pet.get_vec_own()
        self.assertEqual(len(got), 3)
        for i, o in enumerate(got):
            self.assertEqual(o.get_name().decode('utf-8'), f"VecOwner{i}")
            self.assertEqual(o.get_age(), i+10)

    def test_own_v2(self):
        from roboticfluid_py.rf_owner import OwnerV2
        o = OwnerV2()
        o.set_name("TestOwnerV2")
        o.set_age(22)
        self.pet.set_own_v2(o)
        got = self.pet.get_own_v2()
        self.assertEqual(got.get_name().decode('utf-8'), "TestOwnerV2")
        self.assertEqual(got.get_age(), 22)

    def test_arr_own_v2(self):
        from roboticfluid_py.rf_owner import OwnerV2
        arr = [OwnerV2() for _ in range(10000)]
        for i, o in enumerate(arr[:10]):
            o.set_name(f"ArrOwnerV2_{i}")
            o.set_age(i+20)
        self.pet.set_arr_own_v2(arr)
        got = self.pet.get_arr_own_v2()
        self.assertEqual(len(got), 10000)
        for i, o in enumerate(got[:10]):
            self.assertEqual(o.get_name().decode('utf-8'), f"ArrOwnerV2_{i}")
            self.assertEqual(o.get_age(), i+20)

    def test_vec_own_v2(self):
        from roboticfluid_py.rf_owner import OwnerV2
        vec = []
        for i in range(4):
            o = OwnerV2()
            o.set_name(f"VecOwnerV2_{i}")
            o.set_age(i+30)
            vec.append(o)
        self.pet.set_vec_own_v2(vec)
        got = self.pet.get_vec_own_v2()
        self.assertEqual(len(got), 4)
        for i, o in enumerate(got):
            self.assertEqual(o.get_name().decode('utf-8'), f"VecOwnerV2_{i}")
            self.assertEqual(o.get_age(), i+30)

    def test_own_v3(self):
        from roboticfluid_py.rf_owner.nested import OwnerV3
        o = OwnerV3()
        o.set_name("TestOwnerV3")
        o.set_age(33)
        self.pet.set_own_v3(o)
        got = self.pet.get_own_v3()
        self.assertEqual(got.get_name().decode('utf-8'), "TestOwnerV3")
        self.assertEqual(got.get_age(), 33)

    def test_arr_own_v3(self):
        from roboticfluid_py.rf_owner.nested import OwnerV3
        arr = [OwnerV3() for _ in range(10000)]
        for i, o in enumerate(arr[:10]):
            o.set_name(f"ArrOwnerV3_{i}")
            o.set_age(i+40)
        self.pet.set_arr_own_v3(arr)
        got = self.pet.get_arr_own_v3()
        self.assertEqual(len(got), 10000)
        for i, o in enumerate(got[:10]):
            self.assertEqual(o.get_name().decode('utf-8'), f"ArrOwnerV3_{i}")
            self.assertEqual(o.get_age(), i+40)

    def test_vec_own_v3(self):
        from roboticfluid_py.rf_owner.nested import OwnerV3
        vec = []
        for i in range(5):
            o = OwnerV3()
            o.set_name(f"VecOwnerV3_{i}")
            o.set_age(i+50)
            vec.append(o)
        self.pet.set_vec_own_v3(vec)
        got = self.pet.get_vec_own_v3()
        self.assertEqual(len(got), 5)
        for i, o in enumerate(got):
            self.assertEqual(o.get_name().decode('utf-8'), f"VecOwnerV3_{i}")
            self.assertEqual(o.get_age(), i+50)

    def test_own_v4(self):
        from roboticfluid_py import OwnerV4
        o = OwnerV4()
        o.set_name("TestOwnerV4")
        o.set_age(44)
        self.pet.set_own_v4(o)
        got = self.pet.get_own_v4()
        self.assertEqual(got.get_name().decode('utf-8'), "TestOwnerV4")
        self.assertEqual(got.get_age(), 44)

    def test_arr_own_v4(self):
        from roboticfluid_py import OwnerV4
        arr = [OwnerV4() for _ in range(10000)]
        for i, o in enumerate(arr[:10]):
            o.set_name(f"ArrOwnerV4_{i}")
            o.set_age(i+60)
        self.pet.set_arr_own_v4(arr)
        got = self.pet.get_arr_own_v4()
        self.assertEqual(len(got), 10000)
        for i, o in enumerate(got[:10]):
            self.assertEqual(o.get_name().decode('utf-8'), f"ArrOwnerV4_{i}")
            self.assertEqual(o.get_age(), i+60)

    def test_vec_own_v4(self):
        from roboticfluid_py import OwnerV4
        vec = []
        for i in range(6):
            o = OwnerV4()
            o.set_name(f"VecOwnerV4_{i}")
            o.set_age(i+70)
            vec.append(o)
        self.pet.set_vec_own_v4(vec)
        got = self.pet.get_vec_own_v4()
        self.assertEqual(len(got), 6)
        for i, o in enumerate(got):
            self.assertEqual(o.get_name().decode('utf-8'), f"VecOwnerV4_{i}")
            self.assertEqual(o.get_age(), i+70)

    def test_pet_type(self):
        from roboticfluid_py.rf_pet import PetType
        self.pet.set_pet_type(PetType.DOG)
        self.assertEqual(self.pet.get_pet_type(), PetType.DOG)
        self.pet.set_pet_type(PetType.CAT)
        self.assertEqual(self.pet.get_pet_type(), PetType.CAT)

    def test_arr_pet_type(self):
        from roboticfluid_py.rf_pet import PetType
        arr = [PetType.DOG] * 10000
        arr[1] = PetType.CAT
        self.pet.set_arr_pet_type(arr)
        got = self.pet.get_arr_pet_type()
        self.assertEqual(list(got[:2]), [PetType.DOG, PetType.CAT])
        self.assertEqual(len(got), 10000)

    def test_vec_pet_type(self):
        from roboticfluid_py.rf_pet import PetType
        vec = [PetType.DOG, PetType.CAT, PetType.DOG]
        self.pet.set_vec_pet_type(vec)
        got = self.pet.get_vec_pet_type()
        self.assertEqual(list(got), vec)

    def test_arr_u8(self):
        arr = [i % 256 for i in range(10000)]
        self.pet.set_arr_u8(arr)
        got = self.pet.get_arr_u8()
        self.assertEqual(list(got[:10]), arr[:10])
        self.assertEqual(len(got), 10000)

    def test_type_error_arr_d(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_d([1.1] * 9999)
        with self.assertRaises(TypeError):
            self.pet.set_arr_d([1.1] * 10001)

    def test_type_error_arr_f(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_f([1.0])
        with self.assertRaises(TypeError):
            self.pet.set_arr_f([1.0, 2.0, 3.0])

    def test_type_error_arr_i32(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_i32([1])
        with self.assertRaises(TypeError):
            self.pet.set_arr_i32([1, 2, 3])

    def test_type_error_arr_i64(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_i64([1])
        with self.assertRaises(TypeError):
            self.pet.set_arr_i64([1, 2, 3])

    def test_type_error_arr_u32(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_u32([1])
        with self.assertRaises(TypeError):
            self.pet.set_arr_u32([1, 2, 3])

    def test_type_error_arr_u64(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_u64([1])
        with self.assertRaises(TypeError):
            self.pet.set_arr_u64([1, 2, 3])

    def test_type_error_arr_bval(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_bval([True])
        with self.assertRaises(TypeError):
            self.pet.set_arr_bval([True, False, True])

    def test_type_error_arr_s(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_s(["a"])
        with self.assertRaises(TypeError):
            self.pet.set_arr_s(["a", "b", "c"])

    def test_type_error_arr_own(self):
        from roboticfluid_py.rf_owner import Owner
        with self.assertRaises(TypeError):
            self.pet.set_arr_own([Owner()])
        with self.assertRaises(TypeError):
            self.pet.set_arr_own([Owner() for _ in range(11)])

    def test_type_error_arr_own_v2(self):
        from roboticfluid_py.rf_owner import OwnerV2
        with self.assertRaises(TypeError):
            self.pet.set_arr_own_v2([OwnerV2()])
        with self.assertRaises(TypeError):
            self.pet.set_arr_own_v2([OwnerV2() for _ in range(11)])

    def test_type_error_arr_own_v3(self):
        from roboticfluid_py.rf_owner.nested import OwnerV3
        with self.assertRaises(TypeError):
            self.pet.set_arr_own_v3([OwnerV3()])
        with self.assertRaises(TypeError):
            self.pet.set_arr_own_v3([OwnerV3() for _ in range(11)])

    def test_type_error_arr_own_v4(self):
        from roboticfluid_py import OwnerV4
        with self.assertRaises(TypeError):
            self.pet.set_arr_own_v4([OwnerV4()])
        with self.assertRaises(TypeError):
            self.pet.set_arr_own_v4([OwnerV4() for _ in range(11)])

    def test_type_error_arr_pet_type(self):
        from roboticfluid_py.rf_pet import PetType
        with self.assertRaises(TypeError):
            self.pet.set_arr_pet_type([PetType.DOG])
        with self.assertRaises(TypeError):
            self.pet.set_arr_pet_type([PetType.DOG, PetType.CAT, PetType.DOG])

    def test_type_error_arr_u8(self):
        with self.assertRaises(TypeError):
            self.pet.set_arr_u8([1]*99)
        with self.assertRaises(TypeError):
            self.pet.set_arr_u8([1]*101)

if __name__ == "__main__":
    unittest.main() 