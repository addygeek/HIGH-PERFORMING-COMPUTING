import threading
import random

vector_list = []
num_vectors = 100
num_threads = 4
cross_parts = []
dot_parts = []
mutex = threading.Lock()

# Initialize the vector list with random values
for i in range(num_vectors):
    vector = []
    for j in range(3):
        vector.append(random.randint(0, 100))
    vector_list.append(vector)

def compute_cross_product(vec1, vec2):
    return [
        vec1[1] * vec2[2] - vec1[2] * vec2[1],
        vec1[2] * vec1[0] - vec1[0] * vec2[2],
        vec1[0] * vec2[1] - vec1[1] * vec2[0]
    ]

def compute_dot_product(vec1, vec2):
    return vec1[0] * vec2[0] + vec1[1] * vec2[1] + vec1[2] * vec2[2]

def worker_thread(thread_id):
    left = int(thread_id * num_vectors / num_threads)
    right = int((num_vectors / num_threads) * (thread_id + 1))
    print("Running thread id", str(thread_id))
    
    cross_result = vector_list[left]
    for vector in vector_list[left + 1:right]:
        cross_result = compute_cross_product(cross_result, vector)
    
    dot_result = 0
    for vector in vector_list[left:right]:
        dot_result += compute_dot_product(vector_list[0], vector)

    with mutex:
        cross_parts.append(cross_result)
        dot_parts.append(dot_result)

def final_computation():
    cross_result = cross_parts[0]
    for vector in cross_parts[1:]:
        cross_result = compute_cross_product(cross_result, vector)
    print("Final Cross product is", cross_result)
    
    dot_result = sum(dot_parts)
    print("Final Dot product is", dot_result)

# Create and start threads
threads = []
for i in range(num_threads):
    thread_instance = threading.Thread(target=worker_thread, args=(i,))
    threads.append(thread_instance)
    thread_instance.start()

# Wait for all threads to complete
for t in threads:
    t.join()

# Final computation in a separate thread
final_thread = threading.Thread(target=final_computation)
final_thread.start()
final_thread.join()

print("Exit")