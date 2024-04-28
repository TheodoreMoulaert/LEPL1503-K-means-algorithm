import time
import subprocess
import matplotlib.pyplot as plt
import numpy as np

# Function to run the k_means.py with given arguments and return execution time
def run_kmeans(input_file, k, picking_limit, distance, quiet):
    start_time = time.time()
    process = subprocess.Popen(['python', 'k_means.py', input_file, '-k', str(k), '-p', str(picking_limit),
                                '--distance', distance, '-q' if quiet else ''],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.communicate()
    end_time = time.time()
    execution_time = end_time - start_time
    return execution_time

# Function to run the k_means.py with given arguments multiple times and return average execution time
def run_kmeans_multiple(input_file, k, picking_limit, distance, quiet, num_executions=10):
    execution_times = []
    for _ in range(num_executions):
        execution_time = run_kmeans(input_file, k, picking_limit, distance, quiet)
        execution_times.append(execution_time)
    return np.mean(execution_times)  # Calculate average execution time

# Test scenarios
input_file = "test1000000.bin"  # Update with your binary input file path
k_values = [2, 4, 6, 8, 10]  # Varying number of clusters
picking_limit = 1000000  # Assuming all vectors are considered for initialization
distance = "manhattan"  # or "euclidean"
quiet = True
num_executions = 100  # Number of executions for each value of k

# Calculate average execution times for each value of k
average_execution_times = []
for k in k_values:
    average_execution_time = run_kmeans_multiple(input_file, k, picking_limit, distance, quiet, num_executions)
    average_execution_times.append(average_execution_time)

# Print average execution times for each value of k
for k, execution_time in zip(k_values, average_execution_times):
    print(f"k={k}, average execution time={execution_time} seconds")

# Plotting

plt.plot(k_values, average_execution_times, marker='o')
plt.xlabel('Number of Clusters (k)')
plt.ylabel('Average Execution Time (seconds)')
plt.title('Average Execution Time vs Number of Clusters (k)')
plt.grid(True)
plt.show()
