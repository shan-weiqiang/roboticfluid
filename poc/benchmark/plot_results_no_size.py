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

# Debug: Print available method names
print("Available method names in CSV:")
print(df['name'].unique())
print("\nSerialization methods found:")
print(serialize_data['name'].unique())
print("\nDeserialization methods found:")
print(deserialize_data['name'].unique())

# Debug: Check for roboticfluid methods specifically
print("\nLooking for roboticfluid methods:")
roboticfluid_serialize = df[df['name'].str.contains('roboticfluid.*dump', case=False)]
roboticfluid_deserialize = df[df['name'].str.contains('roboticfluid.*load', case=False)]
print("Roboticfluid serialize methods found:", roboticfluid_serialize['name'].unique())
print("Roboticfluid deserialize methods found:", roboticfluid_deserialize['name'].unique())

# Define method mappings with more flexible matching
serialize_methods = {}
deserialize_methods = {}

# Find actual method names in the data
for name in serialize_data['name'].unique():
    if ('roboticfluid' in name.lower() or 'rototicfluid' in name.lower()) and 'dump' in name.lower():
        serialize_methods[name] = 'roboticfluid'
    elif 'protobuf' in name.lower() and 'serialize' in name.lower():
        serialize_methods[name] = 'protobuf'
    elif 'fastdds' in name.lower() and 'serialize' in name.lower():
        serialize_methods[name] = 'fastdds'

for name in deserialize_data['name'].unique():
    if ('roboticfluid' in name.lower() or 'rototicfluid' in name.lower()) and 'load' in name.lower():
        deserialize_methods[name] = 'roboticfluid'
    elif 'protobuf' in name.lower() and 'deserialize' in name.lower():
        deserialize_methods[name] = 'protobuf'
    elif 'fastdds' in name.lower() and 'deserialize' in name.lower():
        deserialize_methods[name] = 'fastdds'

print("\nFinal method mappings:")
print("Serialization:", serialize_methods)
print("Deserialization:", deserialize_methods)

# Create single figure with histogram plots (one above, one below)
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(16, 10))

# Get unique FastDDS data sizes
all_data_sizes = sorted(df['data_size_mb'].unique())

# Prepare data for histogram
serialize_hist_data = {}
deserialize_hist_data = {}

# Collect data for each method and data size
for data_size in all_data_sizes:
    for method_name, label in serialize_methods.items():
        method_data = serialize_data[(serialize_data['name'] == method_name) & 
                                   (serialize_data['data_size_mb'] == data_size)]
        if not method_data.empty:
            if label not in serialize_hist_data:
                serialize_hist_data[label] = {'sizes': [], 'times': []}
            serialize_hist_data[label]['sizes'].append(data_size)
            serialize_hist_data[label]['times'].append(method_data['total'].iloc[0])
    
    for method_name, label in deserialize_methods.items():
        method_data = deserialize_data[(deserialize_data['name'] == method_name) & 
                                     (deserialize_data['data_size_mb'] == data_size)]
        if not method_data.empty:
            if label not in deserialize_hist_data:
                deserialize_hist_data[label] = {'sizes': [], 'times': []}
            deserialize_hist_data[label]['sizes'].append(data_size)
            deserialize_hist_data[label]['times'].append(method_data['total'].iloc[0])

# Plot serialization histogram (top)
x_pos = np.arange(len(all_data_sizes))
width = 0.25

# Define the order: roboticfluid (left), fastdds (middle), protobuf (right)
bar_order = ['roboticfluid', 'fastdds', 'protobuf']
bar_positions = [0, 1, 2]  # Left, middle, right

# Define distinct colors for better visibility
colors = {
    'roboticfluid': '#E74C3C',  # Bright red
    'fastdds': '#2ECC71',       # Bright green
    'protobuf': '#3498DB'       # Bright blue
}

# Plot time bars
for i, (label, data) in enumerate(serialize_hist_data.items()):
    if label in bar_order:
        bar_idx = bar_order.index(label)
        times = []
        for size in all_data_sizes:
            if size in data['sizes']:
                idx = data['sizes'].index(size)
                times.append(data['times'][idx])
            else:
                times.append(0)  # No data for this size
        
        bars = ax1.bar(x_pos + bar_positions[bar_idx]*width, times, width, 
                      label=label, alpha=0.8, edgecolor='black', color=colors[label])
        
        # Add value annotations on top of each bar
        for j, (bar, time) in enumerate(zip(bars, times)):
            if time > 0:  # Only annotate if there's actual data
                ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height(), 
                        f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax1.set_xlabel('FastDDS Serialized Data Size (MB)')
ax1.set_ylabel('Total Time for 100 Operations (seconds)')
ax1.set_title('Serialization Performance Comparison by FastDDS Data Size')
ax1.set_xticks(x_pos + width)
ax1.set_xticklabels([f'{size:.6f}' for size in all_data_sizes], rotation=45, ha='right')
if ax1.get_legend_handles_labels()[0]:  # Only show legend if there are plotted bars
    ax1.legend()
ax1.grid(True, alpha=0.3)

# Plot deserialization histogram (bottom)
for i, (label, data) in enumerate(deserialize_hist_data.items()):
    if label in bar_order:
        bar_idx = bar_order.index(label)
        times = []
        for size in all_data_sizes:
            if size in data['sizes']:
                idx = data['sizes'].index(size)
                times.append(data['times'][idx])
            else:
                times.append(0)  # No data for this size
        
        bars = ax2.bar(x_pos + bar_positions[bar_idx]*width, times, width, 
                      label=label, alpha=0.8, edgecolor='black', color=colors[label])
        
        # Add value annotations on top of each bar
        for j, (bar, time) in enumerate(zip(bars, times)):
            if time > 0:  # Only annotate if there's actual data
                ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height(), 
                        f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax2.set_xlabel('FastDDS Serialized Data Size (MB)')
ax2.set_ylabel('Total Time for 100 Operations (seconds)')
ax2.set_title('Deserialization Performance Comparison by FastDDS Data Size')
ax2.set_xticks(x_pos + width)
ax2.set_xticklabels([f'{size:.6f}' for size in all_data_sizes], rotation=45, ha='right')
if ax2.get_legend_handles_labels()[0]:  # Only show legend if there are plotted bars
    ax2.legend()
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('benchmark_performance_only.png', dpi=300, bbox_inches='tight')
plt.show() 