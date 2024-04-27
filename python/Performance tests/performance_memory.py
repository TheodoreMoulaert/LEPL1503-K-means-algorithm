import subprocess
import matplotlib.pyplot as plt
from memory_profiler import profile, memory_usage

# Function to run the k_means.py with given arguments and profile memory usage
@profile
def run_kmeans(input_file, k, picking_limit, distance, quiet):
    process = subprocess.Popen(['python', 'k_means.py', input_file, '-k', str(k), '-p', str(picking_limit),
                                '--distance', distance, '-q' if quiet else ''],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.communicate()

# Function to parse memory usage data
def parse_memory_usage(mem_usage_output):
    mem_usage_data = []
    for line in mem_usage_output.split('\n'):
        if line.strip():
            time, mem = line.split()
            mem_usage_data.append((float(time), float(mem)))
    return mem_usage_data

# Test scenario
if __name__ == "__main__":
    input_file = "test100.bin"  # Update with your binary input file path
    k = 10
    picking_limit = 1000000
    distance = "manhattan"
    quiet = True

    # Profile memory usage
    mem_usage_profiled = memory_usage((run_kmeans, (input_file, k, picking_limit, distance, quiet)))

    # Plot memory usage
    plt.plot(mem_usage_profiled)
    plt.xlabel('Time (s)')
    plt.ylabel('Memory Usage (MiB)')
    plt.title('Memory Usage Over Time')
    plt.grid(True)
    plt.show()
