import mmap
import os
import ctypes
import numpy as np
from roboticfluid import SharedStruct

SHM_NAME = "/roboticfluid_shm"
SHM_SIZE = ctypes.sizeof(ctypes.c_double) * 1 + ctypes.sizeof(ctypes.c_float) * 1 + ctypes.sizeof(ctypes.c_int32) * 1 + ctypes.sizeof(ctypes.c_int64) * 1 + ctypes.sizeof(ctypes.c_uint32) * 1 + ctypes.sizeof(ctypes.c_uint64) * 1 + ctypes.sizeof(ctypes.c_bool) * 1 + 1024  # crude estimate for string/arrays

fd = os.open(f"/dev/shm{SHM_NAME}", os.O_RDWR)
mm = mmap.mmap(fd, SHM_SIZE)

# Get the address of the mmap buffer
buf = (ctypes.c_char * SHM_SIZE).from_buffer(mm)
addr = ctypes.addressof(buf)

# Map the shared struct using pybind11
obj = SharedStruct.from_address(addr)

# Write to fields using pybind11 (this will be visible to C++)
obj.d = 1.23
obj.f = 4.56
obj.i32 = 7
obj.i64 = 8
obj.u32 = 9
obj.u64 = 10
obj.bval = True
obj.s = "hello from python"

# Write to arrays and vectors
arr = obj.arr_d
arr[0] = 10.0
arr[1] = 20.0
arr[2] = 30.0
arr[3] = 40.0

obj.vec_d = np.array([100.0, 200.0, 300.0], dtype=np.float64)

print("Python wrote:")
print("d:", obj.d)
print("f:", obj.f)
print("i32:", obj.i32)
print("i64:", obj.i64)
print("u32:", obj.u32)
print("u64:", obj.u64)
print("bval:", obj.bval)
print("s:", obj.s)
print("arr_d:", obj.arr_d)
print("vec_d:", obj.vec_d)

mm.close()
os.close(fd) 