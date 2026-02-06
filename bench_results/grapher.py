import matplotlib.pyplot as plt
import re
import os

def run_analysis(input_file, output_img):
    labels, glm_vals, vmath_vals = [], [], []
    # Key: Op ID -> {GLM: time, VMATH: time}
    data_map = {}

    if not os.path.exists(input_file):
        print(f"Error: {input_file} not found.")
        return

    # Extract ID, Name, and Value (Assumes: ID: Name - Value)
    pattern = re.compile(r"([GF])(\d+): (.*?) - ([\d\.]+)")

    with open(input_file, 'r') as f:
        for line in f:
            match = pattern.search(line)
            if match:
                lib, op_id, name, val = match.groups()
                op_id = int(op_id)
                if op_id not in data_map:
                    data_map[op_id] = {'name': name, 'G': None, 'F': None}
                data_map[op_id][lib] = float(val)

    # Sort by Op ID and prepare data for side-by-side comparison
    sorted_ids = sorted([i for i in data_map if data_map[i]['G'] and data_map[i]['F']])
    
    indices = range(len(sorted_ids))
    g_data = [data_map[i]['G'] for i in sorted_ids]
    f_data = [data_map[i]['F'] for i in sorted_ids]
    tick_labels = [f"Op {i}\n({data_map[i]['name'][:10]}...)" for i in sorted_ids]

    plt.figure(figsize=(14, 7))
    plt.bar([i - 0.2 for i in indices], g_data, 0.4, label='GLM', color='#3498db')
    plt.bar([i + 0.2 for i in indices], f_data, 0.4, label='VMath', color='#e67e22')

    plt.xlabel('Operation ID (Common Tests)')
    plt.ylabel('Time (Lower is Better)')
    plt.title('Performance Comparison: GLM vs VMath')
    plt.xticks(indices, tick_labels, rotation=45, fontsize=8)
    plt.legend()
    plt.grid(axis='y', linestyle='--', alpha=0.6)
    
    plt.tight_layout()
    plt.savefig(output_img)
    print(f"Analysis complete. Chart saved to {output_img}")

if __name__ == "__main__":
    run_analysis('bench_results/performance.txt', 'bench_results/comparison.png')