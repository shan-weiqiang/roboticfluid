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

# Convert total time from 100 operations to 1 operation (divide by 100)
df['total'] = df['total'] / 100

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

# Define method mappings - EXCLUDE compressed versions from main benchmark
serialize_methods = {}
deserialize_methods = {}

# Find actual method names in the data (excluding compressed)
for name in serialize_data['name'].unique():
    if 'roboticfluid dump' in name.lower() and 'compress' not in name.lower():
        serialize_methods[name] = 'roboticfluid'
    elif 'protobuf' in name.lower() and 'serialize' in name.lower():
        serialize_methods[name] = 'protobuf'
    elif 'fastdds' in name.lower() and 'serialize' in name.lower():
        serialize_methods[name] = 'fastdds'

for name in deserialize_data['name'].unique():
    if 'roboticfluid load' in name.lower() and 'decompress' not in name.lower():
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
            serialize_hist_data[label]['times'].append(method_data['total'].iloc[0] * 1000)  # Convert to milliseconds
    
    for method_name, label in deserialize_methods.items():
        method_data = deserialize_data[(deserialize_data['name'] == method_name) & 
                                     (deserialize_data['data_size_mb'] == data_size)]
        if not method_data.empty:
            if label not in deserialize_hist_data:
                deserialize_hist_data[label] = {'sizes': [], 'times': []}
            deserialize_hist_data[label]['sizes'].append(data_size)
            deserialize_hist_data[label]['times'].append(method_data['total'].iloc[0] * 1000)  # Convert to milliseconds

# Plot serialization histogram (top)
x_pos = np.arange(len(all_data_sizes))
width = 0.25

# Define the order: roboticfluid (left), fastdds (center), protobuf (right)
bar_order = ['roboticfluid', 'fastdds', 'protobuf']
bar_positions = [0, 1, 2]  # Left, center, right

# Define distinct colors for better visibility
colors = {
    'roboticfluid': '#E74C3C',  # Bright red
    'fastdds': '#2ECC71',       # Bright green
    'protobuf': '#3498DB'       # Bright blue
}

# Define label offsets for better positioning
label_offsets = {
    'roboticfluid': 0.5,  # Offset for left bar
    'fastdds': 0.5,       # Offset for center bar
    'protobuf': 0.5       # Offset for right bar
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
        
        # Add value annotations on top of each bar with offset
        for j, (bar, time) in enumerate(zip(bars, times)):
            if time > 0:  # Only annotate if there's actual data
                offset = label_offsets[label]
                ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                        f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax1.set_xlabel('FastDDS Serialized Data Size (MB)')
ax1.set_ylabel('Time for 1 Operation (milliseconds)')
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
        
        # Add value annotations on top of each bar with offset
        for j, (bar, time) in enumerate(zip(bars, times)):
            if time > 0:  # Only annotate if there's actual data
                offset = label_offsets[label]
                ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                        f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax2.set_xlabel('FastDDS Serialized Data Size (MB)')
ax2.set_ylabel('Time for 1 Operation (milliseconds)')
ax2.set_title('Deserialization Performance Comparison by FastDDS Data Size')
ax2.set_xticks(x_pos + width)
ax2.set_xticklabels([f'{size:.6f}' for size in all_data_sizes], rotation=45, ha='right')
if ax2.get_legend_handles_labels()[0]:  # Only show legend if there are plotted bars
    ax2.legend()
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('benchmark_performance_only.png', dpi=300, bbox_inches='tight')
plt.show()

# Create separate figure for roboticfluid compression comparison
fig2, (ax3, ax4) = plt.subplots(2, 1, figsize=(16, 10))
fig2.suptitle('Roboticfluid: Normal vs Compressed Comparison', fontsize=16, fontweight='bold')

# Prepare data for roboticfluid compression comparison
rf_serialize_data = {}
rf_deserialize_data = {}

# Collect data for roboticfluid normal and compressed
for data_size in all_data_sizes:
    # Normal roboticfluid
    normal_serialize = serialize_data[(serialize_data['name'] == 'roboticfluid dump') & 
                                     (serialize_data['data_size_mb'] == data_size)]
    normal_deserialize = deserialize_data[(deserialize_data['name'] == 'roboticfluid load') & 
                                         (deserialize_data['data_size_mb'] == data_size)]
    
    # Compressed roboticfluid
    compressed_serialize = serialize_data[(serialize_data['name'] == 'roboticfluid dump+compress') & 
                                         (serialize_data['data_size_mb'] == data_size)]
    compressed_deserialize = deserialize_data[(deserialize_data['name'] == 'roboticfluid decompress+load') & 
                                            (deserialize_data['data_size_mb'] == data_size)]
    
    if not normal_serialize.empty:
        if 'normal' not in rf_serialize_data:
            rf_serialize_data['normal'] = {'sizes': [], 'times': []}
        rf_serialize_data['normal']['sizes'].append(data_size)
        rf_serialize_data['normal']['times'].append(normal_serialize['total'].iloc[0] * 1000)  # Convert to milliseconds
    
    if not compressed_serialize.empty:
        if 'compressed' not in rf_serialize_data:
            rf_serialize_data['compressed'] = {'sizes': [], 'times': []}
        rf_serialize_data['compressed']['sizes'].append(data_size)
        rf_serialize_data['compressed']['times'].append(compressed_serialize['total'].iloc[0] * 1000)  # Convert to milliseconds
    
    if not normal_deserialize.empty:
        if 'normal' not in rf_deserialize_data:
            rf_deserialize_data['normal'] = {'sizes': [], 'times': []}
        rf_deserialize_data['normal']['sizes'].append(data_size)
        rf_deserialize_data['normal']['times'].append(normal_deserialize['total'].iloc[0] * 1000)  # Convert to milliseconds
    
    if not compressed_deserialize.empty:
        if 'compressed' not in rf_deserialize_data:
            rf_deserialize_data['compressed'] = {'sizes': [], 'times': []}
        rf_deserialize_data['compressed']['sizes'].append(data_size)
        rf_deserialize_data['compressed']['times'].append(compressed_deserialize['total'].iloc[0] * 1000)  # Convert to milliseconds

# Plot setup for compression comparison
x_pos_rf = np.arange(len(all_data_sizes))
width_rf = 0.35

# Colors for roboticfluid comparison
rf_colors = {
    'normal': '#E74C3C',      # Red
    'compressed': '#F39C12'   # Orange
}

# Define label offsets for roboticfluid comparison
rf_label_offsets = {
    'normal': 0.5,      # Offset for normal bar
    'compressed': 0.5   # Offset for compressed bar
}

# Plot roboticfluid serialization histogram (top)
for label, data in rf_serialize_data.items():
    times = []
    for size in all_data_sizes:
        if size in data['sizes']:
            idx = data['sizes'].index(size)
            times.append(data['times'][idx])
        else:
            times.append(0)
    
    bars = ax3.bar(x_pos_rf + (0 if label == 'normal' else width_rf), times, width_rf, 
                  label=label, alpha=0.8, edgecolor='black', color=rf_colors[label])
    
    # Add value annotations with offset
    for j, (bar, time) in enumerate(zip(bars, times)):
        if time > 0:
            offset = rf_label_offsets[label]
            ax3.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                    f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax3.set_xlabel('FastDDS Serialized Data Size (MB)')
ax3.set_ylabel('Time for 1 Operation (milliseconds)')
ax3.set_title('Roboticfluid Serialization Performance Comparison')
ax3.set_xticks(x_pos_rf + width_rf/2)
ax3.set_xticklabels([f'{size:.6f}' for size in all_data_sizes], rotation=45, ha='right')
ax3.legend()
ax3.grid(True, alpha=0.3)

# Plot roboticfluid deserialization histogram (bottom)
for label, data in rf_deserialize_data.items():
    times = []
    for size in all_data_sizes:
        if size in data['sizes']:
            idx = data['sizes'].index(size)
            times.append(data['times'][idx])
        else:
            times.append(0)
    
    bars = ax4.bar(x_pos_rf + (0 if label == 'normal' else width_rf), times, width_rf, 
                  label=label, alpha=0.8, edgecolor='black', color=rf_colors[label])
    
    # Add value annotations with offset
    for j, (bar, time) in enumerate(zip(bars, times)):
        if time > 0:
            offset = rf_label_offsets[label]
            ax4.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                    f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax4.set_xlabel('FastDDS Serialized Data Size (MB)')
ax4.set_ylabel('Time for 1 Operation (milliseconds)')
ax4.set_title('Roboticfluid Deserialization Performance Comparison')
ax4.set_xticks(x_pos_rf + width_rf/2)
ax4.set_xticklabels([f'{size:.6f}' for size in all_data_sizes], rotation=45, ha='right')
ax4.legend()
ax4.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('roboticfluid_compression_comparison_no_size.png', dpi=300, bbox_inches='tight')
plt.show() 