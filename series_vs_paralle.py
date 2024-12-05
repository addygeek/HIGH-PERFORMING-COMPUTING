import matplotlib.pyplot as plt

# Data from the table (Processors and parallel performance in GFlops/s)
processors = [1, 2, 4, 8, 16]
parallel_performance = [4.0, 7.6, 14.9, 23.1, 35.6]

# Serial performance (sequential performance with 1 processor)
serial_performance = [4.0] * len(processors)

# Speedup (Parallel vs Serial)
speedup_parallel = [serial_performance[0] / p for p in parallel_performance]

# Parallel Efficiency (Parallel vs Serial)
efficiency_parallel = [speedup_parallel[i] / processors[i] for i in range(len(processors))]

# Ideal speedup (Equal to number of processors)
ideal_speedup = processors
ideal_efficiency = [1] * len(processors)

# Plotting comparison

plt.figure(figsize=(12, 6))

# Subplot 1: Speedup comparison (Serial vs Parallel)
plt.subplot(1, 2, 1)
plt.plot(processors, [serial_performance[0] / p for p in serial_performance], label="Serial Speedup", marker='o', linestyle='--')
plt.plot(processors, speedup_parallel, label="Parallel Speedup", marker='o')
plt.plot(processors, ideal_speedup, label="Ideal Speedup", linestyle='--')
plt.xlabel('Number of Processors')
plt.ylabel('Speedup')
plt.title('Speedup: Serial vs Parallel')
plt.legend()

# Subplot 2: Parallel Efficiency comparison
plt.subplot(1, 2, 2)
plt.plot(processors, efficiency_parallel, label="Parallel Efficiency", marker='o')
plt.plot(processors, ideal_efficiency, label="Ideal Efficiency", linestyle='--')
plt.xlabel('Number of Processors')
plt.ylabel('Efficiency')
plt.title('Parallel Efficiency vs Processors')
plt.legend()

plt.tight_layout()
plt.show()

