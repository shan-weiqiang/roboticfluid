import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read the CSV file
df = pd.read_csv('benchmark_results.csv', sep=';', quotechar='"')

# Clean up column names and data
df.columns = df.columns.str.strip().str.replace('"', '')
df['name'] = df['name'].str.strip().str.replace('"', '')
df['data_size_mb'] = df['data_size_mb'].astype(float)
df['total'] = df['total'].astype(float)

# Separate serialization and deserialization data
serialize_data = df[df['name'].str.contains('dump|serialize', case=False)]
deserialize_data = df[df['name'].str.contains('load|deserialize', case=False)]

# Create figure with two subplots
fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(15, 6))

# Plot serialization
serialize_methods = {
    'rototicfluid dump': 'roboticfluid',
    'Protobuf serialize': 'protobuf', 
    'FastDDS serialize': 'fastdds'
}

for method_name, label in serialize_methods.items():
    method_data = serialize_data[serialize_data['name'] == method_name]
    if not method_data.empty:
        ax1.plot(method_data['data_size_mb'], method_data['total'], 
                marker='o', label=label, linewidth=2, markersize=6)

ax1.set_xlabel('Data Size (MB)')
ax1.set_ylabel('Total Time (seconds)')
ax1.set_title('Serialization Performance')
ax1.legend()
ax1.grid(True, alpha=0.3)
ax1.set_yscale('log')  # Use log scale for better visualization

# Plot deserialization
deserialize_methods = {
    'roboticfluid load': 'roboticfluid',
    'Protobuf deserialize': 'protobuf',
    'FastDDS deserialize': 'fastdds'
}

for method_name, label in deserialize_methods.items():
    method_data = deserialize_data[deserialize_data['name'] == method_name]
    if not method_data.empty:
        ax2.plot(method_data['data_size_mb'], method_data['total'], 
                marker='s', label=label, linewidth=2, markersize=6)

ax2.set_xlabel('Data Size (MB)')
ax2.set_ylabel('Total Time (seconds)')
ax2.set_title('Deserialization Performance')
ax2.legend()
ax2.grid(True, alpha=0.3)
ax2.set_yscale('log')  # Use log scale for better visualization

plt.tight_layout()
plt.savefig('benchmark_comparison.png', dpi=300, bbox_inches='tight')
plt.show()

# Print summary statistics
print("=== Serialization Performance Summary ===")
for method_name, label in serialize_methods.items():
    method_data = serialize_data[serialize_data['name'] == method_name]
    if not method_data.empty:
        avg_time = method_data['total'].mean()
        print(f"{label}: Average time = {avg_time:.6f} seconds")

print("\n=== Deserialization Performance Summary ===")
for method_name, label in deserialize_methods.items():
    method_data = deserialize_data[deserialize_data['name'] == method_name]
    if not method_data.empty:
        avg_time = method_data['total'].mean()
        print(f"{label}: Average time = {avg_time:.6f} seconds") 