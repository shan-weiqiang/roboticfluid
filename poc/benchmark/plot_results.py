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

print("\nFinal method mappings (main benchmark):")
print("Serialization:", serialize_methods)
print("Deserialization:", deserialize_methods)

# Create figure with subplots - 2 rows, 2 columns
fig, ((ax1, ax2), (ax3, ax4)) = plt.subplots(2, 2, figsize=(16, 12))
fig.suptitle('Benchmark Results: Roboticfluid vs Protobuf vs FastDDS', fontsize=16, fontweight='bold')

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
            serialize_hist_data[label]['times'].append(method_data['total'].iloc[0] * 1000)  # Convert to milliseconds
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
            deserialize_hist_data[label]['times'].append(method_data['total'].iloc[0] * 1000)  # Convert to milliseconds
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

# Plot setup
x_pos = np.arange(len(all_container_sizes))
width = 0.3  # Make bars wider since we only have 3 methods now

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

# Plot 1: Serialization Performance (Time)
ax1.set_title('Serialization Performance (Time)', fontweight='bold')
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
                      label=label, alpha=0.8, edgecolor='black', color=colors[label])
        
        # Add value annotations only for protobuf with offset
        if label == 'protobuf':
            for j, (bar, time) in enumerate(zip(bars, times)):
                if time > 0:  # Only annotate if there's actual data
                    offset = label_offsets[label]
                    ax1.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                            f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax1.set_xlabel('Container Size (number of elements)')
ax1.set_ylabel('Time for 1 Operation (milliseconds)')
ax1.set_xticks(x_pos + width)
ax1.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax1.legend()
ax1.grid(True, alpha=0.3)

# Plot 2: Deserialization Performance (Time)
ax2.set_title('Deserialization Performance (Time)', fontweight='bold')
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
                      label=label, alpha=0.8, edgecolor='black', color=colors[label])
        
        # Add value annotations only for protobuf with offset
        if label == 'protobuf':
            for j, (bar, time) in enumerate(zip(bars, times)):
                if time > 0:  # Only annotate if there's actual data
                    offset = label_offsets[label]
                    ax2.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                            f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax2.set_xlabel('Container Size (number of elements)')
ax2.set_ylabel('Time for 1 Operation (milliseconds)')
ax2.set_xticks(x_pos + width)
ax2.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax2.legend()
ax2.grid(True, alpha=0.3)

# Plot 3: Combined Size (Serialization and Deserialization are the same)
ax3.set_title('Serialized Data Size', fontweight='bold')
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
        
        ax3.plot(x_pos + width, payload_sizes_mb, 'o-', 
                label=label, color=colors[label], 
                linewidth=2, markersize=6, alpha=0.7)

ax3.set_xlabel('Container Size (number of elements)')
ax3.set_ylabel('Serialized Size (MB)')
ax3.set_xticks(x_pos + width)
ax3.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax3.legend()
ax3.grid(True, alpha=0.3)

# Hide the fourth subplot since we only need 3 plots
ax4.set_visible(False)

plt.tight_layout()
plt.savefig('benchmark_histogram_comparison.png', dpi=300, bbox_inches='tight')
plt.show()

# Create separate figure for roboticfluid compression comparison
fig2, ((ax5, ax6), (ax7, ax8)) = plt.subplots(2, 2, figsize=(16, 12))
fig2.suptitle('Roboticfluid: Normal vs Compressed Comparison', fontsize=16, fontweight='bold')

# Prepare data for roboticfluid compression comparison
rf_serialize_data = {}
rf_deserialize_data = {}

# Collect data for roboticfluid normal and compressed
for container_size in all_container_sizes:
    # Normal roboticfluid
    normal_serialize = serialize_data[(serialize_data['name'] == 'roboticfluid dump') & 
                                     (serialize_data['container_size'] == container_size)]
    normal_deserialize = deserialize_data[(deserialize_data['name'] == 'roboticfluid load') & 
                                         (deserialize_data['container_size'] == container_size)]
    
    # Compressed roboticfluid
    compressed_serialize = serialize_data[(serialize_data['name'] == 'roboticfluid dump+compress') & 
                                         (serialize_data['container_size'] == container_size)]
    compressed_deserialize = deserialize_data[(deserialize_data['name'] == 'roboticfluid decompress+load') & 
                                            (deserialize_data['container_size'] == container_size)]
    
    if not normal_serialize.empty:
        if 'normal' not in rf_serialize_data:
            rf_serialize_data['normal'] = {'sizes': [], 'times': [], 'payload_sizes': []}
        rf_serialize_data['normal']['sizes'].append(container_size)
        rf_serialize_data['normal']['times'].append(normal_serialize['total'].iloc[0] * 1000)  # Convert to milliseconds
        rf_serialize_data['normal']['payload_sizes'].append(normal_serialize['roboticfluid_size_bytes'].iloc[0])
    
    if not compressed_serialize.empty:
        if 'compressed' not in rf_serialize_data:
            rf_serialize_data['compressed'] = {'sizes': [], 'times': [], 'payload_sizes': []}
        rf_serialize_data['compressed']['sizes'].append(container_size)
        rf_serialize_data['compressed']['times'].append(compressed_serialize['total'].iloc[0] * 1000)  # Convert to milliseconds
        rf_serialize_data['compressed']['payload_sizes'].append(compressed_serialize['roboticfluid_compressed_size_bytes'].iloc[0])
    
    if not normal_deserialize.empty:
        if 'normal' not in rf_deserialize_data:
            rf_deserialize_data['normal'] = {'sizes': [], 'times': [], 'payload_sizes': []}
        rf_deserialize_data['normal']['sizes'].append(container_size)
        rf_deserialize_data['normal']['times'].append(normal_deserialize['total'].iloc[0] * 1000)  # Convert to milliseconds
        rf_deserialize_data['normal']['payload_sizes'].append(normal_deserialize['roboticfluid_size_bytes'].iloc[0])
    
    if not compressed_deserialize.empty:
        if 'compressed' not in rf_deserialize_data:
            rf_deserialize_data['compressed'] = {'sizes': [], 'times': [], 'payload_sizes': []}
        rf_deserialize_data['compressed']['sizes'].append(container_size)
        rf_deserialize_data['compressed']['times'].append(compressed_deserialize['total'].iloc[0] * 1000)  # Convert to milliseconds
        rf_deserialize_data['compressed']['payload_sizes'].append(compressed_deserialize['roboticfluid_compressed_size_bytes'].iloc[0])

# Plot setup for compression comparison
x_pos_rf = np.arange(len(all_container_sizes))
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

# Plot 5: Roboticfluid Serialization Performance (Time)
ax5.set_title('Roboticfluid Serialization Performance (Time)', fontweight='bold')
for label, data in rf_serialize_data.items():
    times = []
    for size in all_container_sizes:
        if size in data['sizes']:
            idx = data['sizes'].index(size)
            times.append(data['times'][idx])
        else:
            times.append(0)
    
    bars = ax5.bar(x_pos_rf + (0 if label == 'normal' else width_rf), times, width_rf, 
                  label=label, alpha=0.8, edgecolor='black', color=rf_colors[label])
    
    # Add value annotations with offset
    for j, (bar, time) in enumerate(zip(bars, times)):
        if time > 0:
            offset = rf_label_offsets[label]
            ax5.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                    f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax5.set_xlabel('Container Size (number of elements)')
ax5.set_ylabel('Time for 1 Operation (milliseconds)')
ax5.set_xticks(x_pos_rf + width_rf/2)
ax5.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax5.legend()
ax5.grid(True, alpha=0.3)

# Plot 6: Roboticfluid Deserialization Performance (Time)
ax6.set_title('Roboticfluid Deserialization Performance (Time)', fontweight='bold')
for label, data in rf_deserialize_data.items():
    times = []
    for size in all_container_sizes:
        if size in data['sizes']:
            idx = data['sizes'].index(size)
            times.append(data['times'][idx])
        else:
            times.append(0)
    
    bars = ax6.bar(x_pos_rf + (0 if label == 'normal' else width_rf), times, width_rf, 
                  label=label, alpha=0.8, edgecolor='black', color=rf_colors[label])
    
    # Add value annotations with offset
    for j, (bar, time) in enumerate(zip(bars, times)):
        if time > 0:
            offset = rf_label_offsets[label]
            ax6.text(bar.get_x() + bar.get_width()/2, bar.get_height() + offset, 
                    f'{time:.3f}', ha='center', va='bottom', fontsize=8)

ax6.set_xlabel('Container Size (number of elements)')
ax6.set_ylabel('Time for 1 Operation (milliseconds)')
ax6.set_xticks(x_pos_rf + width_rf/2)
ax6.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax6.legend()
ax6.grid(True, alpha=0.3)

# Plot 7: Roboticfluid Serialized Data Size
ax7.set_title('Roboticfluid Serialized Data Size', fontweight='bold')
for label, data in rf_serialize_data.items():
    payload_sizes = []
    for size in all_container_sizes:
        if size in data['sizes']:
            idx = data['sizes'].index(size)
            payload_sizes.append(data['payload_sizes'][idx])
        else:
            payload_sizes.append(0)
    
    # Convert to MB for better readability
    payload_sizes_mb = [size / (1024 * 1024) for size in payload_sizes]
    
    ax7.plot(x_pos_rf + width_rf/2, payload_sizes_mb, 'o-', 
            label=label, color=rf_colors[label], 
            linewidth=2, markersize=6, alpha=0.7)

ax7.set_xlabel('Container Size (number of elements)')
ax7.set_ylabel('Serialized Size (MB)')
ax7.set_xticks(x_pos_rf + width_rf/2)
ax7.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax7.legend()
ax7.grid(True, alpha=0.3)

# Plot 8: Compression Ratio
ax8.set_title('Compression Ratio (Normal/Compressed)', fontweight='bold')
compression_ratios = []
for size in all_container_sizes:
    normal_size = 0
    compressed_size = 0
    
    if 'normal' in rf_serialize_data and size in rf_serialize_data['normal']['sizes']:
        idx = rf_serialize_data['normal']['sizes'].index(size)
        normal_size = rf_serialize_data['normal']['payload_sizes'][idx]
    
    if 'compressed' in rf_serialize_data and size in rf_serialize_data['compressed']['sizes']:
        idx = rf_serialize_data['compressed']['sizes'].index(size)
        compressed_size = rf_serialize_data['compressed']['payload_sizes'][idx]
    
    if normal_size > 0 and compressed_size > 0:
        ratio = normal_size / compressed_size
        compression_ratios.append(ratio)
    else:
        compression_ratios.append(0)

ax8.plot(x_pos_rf + width_rf/2, compression_ratios, 'o-', 
        color='#9B59B6', linewidth=2, markersize=6, alpha=0.7)
ax8.set_xlabel('Container Size (number of elements)')
ax8.set_ylabel('Compression Ratio')
ax8.set_xticks(x_pos_rf + width_rf/2)
ax8.set_xticklabels([f'{size}' for size in all_container_sizes], rotation=45, ha='right')
ax8.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('roboticfluid_compression_comparison.png', dpi=300, bbox_inches='tight')
plt.show() 