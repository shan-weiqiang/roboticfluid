#!/usr/bin/env python3
"""
Demo script to test LZ4 compression with roboticfluid serialization
"""

import sys
import os
import time
import statistics

# Add the build directory to Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'build'))

try:
    import rf_pet
    print("✓ Successfully imported rf_pet module")
except ImportError as e:
    print(f"✗ Failed to import rf_pet module: {e}")
    print("Please build the project first: cd build && cmake .. && make")
    sys.exit(1)

def test_compression():
    """Test compression functionality"""
    print("\n=== LZ4 Compression Demo ===")
    
    # Create a Pet object with realistic data
    pet = rf_pet.Pet()
    
    # Set basic values
    pet.set_d(3.14159)
    pet.set_f(2.71828)
    pet.set_i32(42)
    pet.set_i64(123456789012345)
    pet.set_u32(123456)
    pet.set_u64(9876543210)
    pet.set_bval(True)
    pet.set_s("Hello, World! This is a test string for compression.")
    
    # Fill arrays with repeated data (good for compression)
    import array
    import numpy as np
    
    # Fill numeric arrays with repeated values
    arr_d = array.array('d', [1.234] * 10000)
    pet.set_arr_d(arr_d)
    
    arr_f = array.array('f', [2.345] * 10000)
    pet.set_arr_f(arr_f)
    
    arr_i32 = array.array('i', [42] * 10000)
    pet.set_arr_i32(arr_i32)
    
    arr_u32 = array.array('I', [123] * 10000)
    pet.set_arr_u32(arr_u32)
    
    # Fill string arrays with repeated strings
    arr_s = ["repeated_string"] * 10000
    pet.set_arr_s(arr_s)
    
    # Fill boolean arrays
    arr_bval = [True] * 10000
    pet.set_arr_bval(arr_bval)
    
    # Fill vectors with some data
    vec_d = [1.1, 2.2, 3.3, 4.4, 5.5] * 1000  # 5000 elements
    pet.vec_d = vec_d
    
    vec_s = ["vector_string"] * 1000
    pet.vec_s = vec_s
    
    print("✓ Created Pet object with test data")
    
    # Test regular serialization
    print("\n--- Regular Serialization ---")
    start_time = time.time()
    uncompressed = pet.dump()
    serialize_time = (time.time() - start_time) * 1000  # Convert to ms
    
    print(f"Uncompressed size: {len(uncompressed):,} bytes ({len(uncompressed)/1024/1024:.2f} MB)")
    print(f"Serialization time: {serialize_time:.2f} ms")
    
    # Test compressed serialization
    print("\n--- Compressed Serialization ---")
    start_time = time.time()
    compressed = pet.dump_compressed()
    compress_time = (time.time() - start_time) * 1000  # Convert to ms
    
    print(f"Compressed size: {len(compressed):,} bytes ({len(compressed)/1024/1024:.2f} MB)")
    print(f"Compression time: {compress_time:.2f} ms")
    
    # Calculate compression statistics
    compression_ratio = (1 - len(compressed) / len(uncompressed)) * 100
    speed_ratio = serialize_time / compress_time if compress_time > 0 else float('inf')
    
    print(f"\n--- Compression Statistics ---")
    print(f"Compression ratio: {compression_ratio:.1f}%")
    print(f"Size reduction: {len(uncompressed) - len(compressed):,} bytes")
    print(f"Speed ratio (uncompressed/compressed): {speed_ratio:.2f}x")
    
    # Test decompression
    print("\n--- Decompression Test ---")
    pet2 = rf_pet.Pet()
    
    start_time = time.time()
    success = pet2.load_compressed(compressed, len(uncompressed))
    decompress_time = (time.time() - start_time) * 1000  # Convert to ms
    
    if success:
        print(f"✓ Decompression successful!")
        print(f"Decompression time: {decompress_time:.2f} ms")
        
        # Verify data integrity
        if (pet.get_d() == pet2.get_d() and 
            pet.get_f() == pet2.get_f() and 
            pet.get_i32() == pet2.get_i32() and 
            pet.get_s() == pet2.get_s()):
            print("✓ Data integrity verified!")
        else:
            print("✗ Data integrity check failed!")
    else:
        print("✗ Decompression failed!")
    
    # Performance comparison
    print(f"\n--- Performance Summary ---")
    print(f"Total time (serialize + compress): {serialize_time + compress_time:.2f} ms")
    print(f"Total time (decompress + deserialize): {decompress_time:.2f} ms")
    print(f"Compression overhead: {compress_time:.2f} ms")
    print(f"Decompression overhead: {decompress_time:.2f} ms")
    
    return compression_ratio, speed_ratio

def benchmark_compression():
    """Run multiple compression tests to get statistics"""
    print("\n=== Compression Benchmark ===")
    
    ratios = []
    speeds = []
    
    for i in range(5):
        print(f"\nRun {i+1}/5:")
        ratio, speed = test_compression()
        ratios.append(ratio)
        speeds.append(speed)
    
    print(f"\n=== Benchmark Results ===")
    print(f"Average compression ratio: {statistics.mean(ratios):.1f}%")
    print(f"Min compression ratio: {min(ratios):.1f}%")
    print(f"Max compression ratio: {max(ratios):.1f}%")
    print(f"Average speed ratio: {statistics.mean(speeds):.2f}x")

if __name__ == "__main__":
    try:
        # Single test
        test_compression()
        
        # Uncomment for full benchmark
        # benchmark_compression()
        
    except Exception as e:
        print(f"Error: {e}")
        import traceback
        traceback.print_exc() 