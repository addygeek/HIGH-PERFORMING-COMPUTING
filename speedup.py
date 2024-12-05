import matplotlib.pyplot as plt

# Data from the table
processors = [1, 2, 4, 8, 16]
seq_performance = [4.0, 7.6, 14.9, 23.1, 35.6]

# Calculate speedup
speedup = [seq_performance[0] / p for p in seq_performance]

# Calculate parallel efficiency
efficiency = [speedup[i] / processors[i] for i in range(len(processors))]

# Ideal speedup and efficiency
ideal_speedup = processors
ideal_efficiency = [1] * len(processors)

# Plotting Speedup vs Processors
plt.figure(figsize=(12, 6))

# Speedup Plot
plt.subplot(1, 2, 1)
plt.plot(processors, speedup, label="Actual Speedup", marker='o')
plt.plot(processors, ideal_speedup, label="Ideal Speedup", linestyle='--')
plt.xlabel('Number of Processors')
plt.ylabel('Speedup')
plt.title('Scalability (Speedup vs Processors)')
plt.legend()

# Parallel Efficiency Plot
plt.subplot(1, 2, 2)
plt.plot(processors, efficiency, label="Actual Efficiency", marker='o')
plt.plot(processors, ideal_efficiency, label="Ideal Efficiency", linestyle='--')
plt.xlabel('Number of Processors')
plt.ylabel('Parallel Efficiency')
plt.title('Parallel Efficiency vs Processors')
plt.legend()

plt.tight_layout()
plt.show()
