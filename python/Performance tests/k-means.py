import time
import psutil
#import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess

# Function to run the k_means.py with given arguments and return execution time and memory consumption
def run_kmeans(input_file, k, picking_limit, distance, quiet):
    start_time = time.time()
    process = subprocess.Popen(['python', 'k_means.py', input_file, '-k', str(k), '-p', str(picking_limit),
                                '--distance', distance, '-q' if quiet else ''],
                                stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    process.communicate()
    end_time = time.time()
    execution_time = end_time - start_time
    process_memory = psutil.Process(process.pid).memory_info().rss / 1024  # in KB
    return execution_time, process_memory

# Function to generate a plot
"""
def generate_plot(x_values, y_values, x_label, y_label, title):
    plt.plot(x_values, y_values, marker='o')
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)
    plt.grid(True)
    plt.show()
"""
# Test scenarios
input_file = "your_input_file_path"
k_values = [2, 4, 6]  # Varying number of clusters
picking_limit_values = [100, 500, 1000]  # Varying picking limits
distance = "manhattan"  # or "euclidean"
quiet = True

execution_times = []
memory_consumptions = []

for k in k_values:
    for picking_limit in picking_limit_values:
        execution_time, memory_consumption = run_kmeans(input_file, k, picking_limit, distance, quiet)
        execution_times.append(execution_time)
        memory_consumptions.append(memory_consumption)

# Plotting execution time
#generate_plot(np.arange(len(execution_times)), execution_times, "Test Case", "Execution Time (s)", "Execution Time Analysis")

# Plotting memory consumption
#generate_plot(np.arange(len(memory_consumptions)), memory_consumptions, "Test Case", "Memory Consumption (KB)", "Memory Consumption Analysis")
