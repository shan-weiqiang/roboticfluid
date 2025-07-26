import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Read the CSV file
df = pd.read_csv('benchmark_results.csv', sep=';', quotechar='"')

# Clean up column names and data
df.columns = df.columns.str.strip().str.replace('"', '')
df['name'] = df['name'].str.strip().str.replace('"', '')
df['container_size'] = df['container_size'].astype(int)
df['protobuf_size_bytes'] = df['protobuf_size_bytes'].astype(float)
df['roboticfluid_size_bytes'] = df['roboticfluid_size_bytes'].astype(float)
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

# Create single figure with dual-axis plots (one above, one below)
fig, (ax1, ax2) = plt.subplots(2, 1, figsize=(16, 12))

# Get unique container sizes
all_container_sizes = sorted(df['container_size'].unique())

# Prepare data for histogram
serialize_hist_data = {}
deserialize_hist_data = {}

# Collect data for each method and container size
for container_size in all_container_sizes:
    for method_name, label in serialize_methods.items():
        method_data = serialize_data[(serialize_data['name'] == method_name) & 
                                   (serialize_data['container_size'] == container_size)]
        if not method_data.empty:
            if label not in serialize_hist_data:
                serialize_hist_data[label] = {'sizes': [], 'times': [], 'payload_sizes': []}
            serialize_hist_data[label]['sizes'].append(container_size)
            serialize_hist_data[label]['times'].append(method_data['total'].iloc[0])
            # Get payload size based on method
            if label == 'protobuf':
                serialize_hist_data[label]['payload_sizes'].append(method_data['protobuf_size_bytes'].iloc[0])
            elif label == 'roboticfluid':
                serialize_hist_data[label]['payload_sizes'].append(method_data['roboticfluid_size_bytes'].iloc[0])
            elif label == 'fastdds':
                # For FastDDS, we need to get the size from the data_size_mb column converted to bytes
                fastdds_size_mb = method_data['data_size_mb'].iloc[0]
                fastdds_size_bytes = fastdds_size_mb * 1024 * 1024
                serialize_hist_data[label]['payload_sizes'].append(fastdds_size_bytes)
    
    for method_name, label in deserialize_methods.items():
        method_data = deserialize_data[(deserialize_data['name'] == method_name) & 
                                     (deserialize_data['container_size'] == container_size)]
        if not method_data.empty:
            if label not in deserialize_hist_data:
                deserialize_hist_data[label] = {'sizes': [], 'times': [], 'payload_sizes': []}
            deserialize_hist_data[label]['sizes'].append(container_size)
            deserialize_hist_data[label]['times'].append(method_data['total'].iloc[0])
            # Get payload size based on method
            if label == 'protobuf':
                deserialize_hist_data[label]['payload_sizes'].append(method_data['protobuf_size_bytes'].iloc[0])
            elif label == 'roboticfluid':
                deserialize_hist_data[label]['payload_sizes'].append(method_data['roboticfluid_size_bytes'].iloc[0])
            elif label == 'fastdds':
                # For FastDDS, we need to get the size from the data_size_mb column converted to bytes
                fastdds_size_mb = method_data['data_size_mb'].iloc[0]
                fastdds_size_bytes = fastdds_size_mb * 1024 * 1024
                deserialize_hist_data[label]['payload_sizes'].append(fastdds_size_bytes)

# Plot serialization histogram (top) with dual axes
x_pos = np.arange(len(all_container_sizes))
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

# Create dual axes for serialization plot
ax1_twin = ax1.twinx()

# Plot time bars (left y-axis)
for i, (label, data) in enumerate(serialize_hist_data.items()):
    if label in bar_order:
        bar_idx = bar_order.index(label)
        times = []
        for size in all_container_sizes:
            if size in data['sizes']:
                idx = data['sizes'].index(size)
                times.append(data['times'][idx])
            else:
                times.append(0)  # No data for this size
        
        bars = ax1.bar(x_pos + bar_positions[bar_idx]*width, times, width, 
                      label=f'{label} (time)', alpha=0.8, edgecolor='black', color=colors[label])
        
        # Add value annotations on top of each bar
        for j, (bar, time) in enumerate(zip(bars, times)):
            if time > 0:  # Only annotate if there's actual data
                ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height(), 
                        f'{time:.3f}', ha='center', va='bottom', fontsize=8)

# Plot payload size lines (right y-axis)
for i, (label, data) in enumerate(serialize_hist_data.items()):
    if label in bar_order:
        payload_sizes = []
        for size in all_container_sizes:
            if size in data['sizes']:
                idx = data['sizes'].index(size)
                payload_sizes.append(data['payload_sizes'][idx])
            else:
                payload_sizes.append(0)  # No data for this size
        
        # Convert to MB for better readability
        payload_sizes_mb = [size / (1024 * 1024) for size in payload_sizes]
        
        line = ax1_twin.plot(x_pos + width, payload_sizes_mb, 'o-', 
                     label=f'{label} (size)', color=colors[label], 
                     linewidth=2, markersize=6, alpha=0.7)
        
        # Add arrow annotations only for roboticfluid
        if label == 'roboticfluid':
            for j, (x, y) in enumerate(zip(x_pos + width, payload_sizes_mb)):
                if y > 0:  # Only annotate if there's actual data
                    ax1_twin.annotate(f'{y:.2f} MB', 
                                    xy=(x, y), xytext=(x - 2.0, y + 1.5),
                                    arrowprops=dict(arrowstyle='->', color=colors[label], alpha=0.7),
                                    fontsize=8, color=colors[label])

ax1.set_xlabel('Container Size (number of elements)')
ax1.set_ylabel('Total Time for 100 Operations (seconds)', color='black')
ax1_twin.set_ylabel('Serialized Payload Size (MB)', color='black')
ax1.set_title('Serialization Performance and Payload Size Comparison\n(Container size vs Time and Serialized Data Size)')
ax1.set_xticks(x_pos + width)
ax1.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax1.grid(True, alpha=0.3)

# Combine legends from both axes
lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax1_twin.get_legend_handles_labels()
ax1.legend(lines1 + lines2, labels1 + labels2, loc='upper left')

# Plot deserialization histogram (bottom) with dual axes
ax2_twin = ax2.twinx()

# Plot time bars (left y-axis)
for i, (label, data) in enumerate(deserialize_hist_data.items()):
    if label in bar_order:
        bar_idx = bar_order.index(label)
        times = []
        for size in all_container_sizes:
            if size in data['sizes']:
                idx = data['sizes'].index(size)
                times.append(data['times'][idx])
            else:
                times.append(0)  # No data for this size
        
        bars = ax2.bar(x_pos + bar_positions[bar_idx]*width, times, width, 
                      label=f'{label} (time)', alpha=0.8, edgecolor='black', color=colors[label])
        
        # Add value annotations on top of each bar
        for j, (bar, time) in enumerate(zip(bars, times)):
            if time > 0:  # Only annotate if there's actual data
                ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height(), 
                        f'{time:.3f}', ha='center', va='bottom', fontsize=8)

# Plot payload size lines (right y-axis)
for i, (label, data) in enumerate(deserialize_hist_data.items()):
    if label in bar_order:
        payload_sizes = []
        for size in all_container_sizes:
            if size in data['sizes']:
                idx = data['sizes'].index(size)
                payload_sizes.append(data['payload_sizes'][idx])
            else:
                payload_sizes.append(0)  # No data for this size
        
        # Convert to MB for better readability
        payload_sizes_mb = [size / (1024 * 1024) for size in payload_sizes]
        
        line = ax2_twin.plot(x_pos + width, payload_sizes_mb, 'o-', 
                     label=f'{label} (size)', color=colors[label], 
                     linewidth=2, markersize=6, alpha=0.7)
        
        # Add arrow annotations only for roboticfluid
        if label == 'roboticfluid':
            for j, (x, y) in enumerate(zip(x_pos + width, payload_sizes_mb)):
                if y > 0:  # Only annotate if there's actual data
                    ax2_twin.annotate(f'{y:.2f} MB', 
                                    xy=(x, y), xytext=(x - 2.0, y + 1.5),
                                    arrowprops=dict(arrowstyle='->', color=colors[label], alpha=0.7),
                                    fontsize=8, color=colors[label])

ax2.set_xlabel('Container Size (number of elements)')
ax2.set_ylabel('Total Time for 100 Operations (seconds)', color='black')
ax2_twin.set_ylabel('Serialized Payload Size (MB)', color='black')
ax2.set_title('Deserialization Performance and Payload Size Comparison\n(Container size vs Time and Serialized Data Size)')
ax2.set_xticks(x_pos + width)
ax2.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax2.grid(True, alpha=0.3)

# Combine legends from both axes
lines1, labels1 = ax2.get_legend_handles_labels()
lines2, labels2 = ax2_twin.get_legend_handles_labels()
ax2.legend(lines1 + lines2, labels1 + labels2, loc='upper left')

plt.tight_layout()
plt.savefig('benchmark_histogram_comparison.png', dpi=300, bbox_inches='tight')
plt.show() 