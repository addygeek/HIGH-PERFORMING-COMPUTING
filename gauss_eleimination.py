import numpy as np

def gaussian_elimination(A, b):
    """
    Solves the system of linear equations Ax = b using Gaussian elimination.
    
    Parameters:
    A (ndarray): Coefficient matrix (n x n)
    b (ndarray): Right-hand side vector (n x 1)
    
    Returns:
    x (ndarray): Solution vector (n x 1)
    """
    n = len(b)
    
    # Augmented matrix [A|b]
    augmented_matrix = np.hstack((A, b.reshape(-1, 1)))
    
    # Forward elimination
    for i in range(n):
        # Partial pivoting: Swap rows to make the diagonal element largest
        max_row = np.argmax(abs(augmented_matrix[i:, i])) + i
        augmented_matrix[[i, max_row]] = augmented_matrix[[max_row, i]]
        
        # Make the diagonal element 1 and eliminate below
        for j in range(i + 1, n):
            factor = augmented_matrix[j, i] / augmented_matrix[i, i]
            augmented_matrix[j, i:] -= factor * augmented_matrix[i, i:]
    
    # Back-substitution
    x = np.zeros(n)
    for i in range(n - 1, -1, -1):
        x[i] = (augmented_matrix[i, -1] - np.dot(augmented_matrix[i, i + 1:n], x[i + 1:n])) / augmented_matrix[i, i]
    
    return x

# Example usage:
A = np.array([[2.0, 1.0, -1.0],
              [-3.0, -1.0, 2.0],
              [-2.0, 1.0, 2.0]])

b = np.array([8.0, -11.0, -3.0])

solution = gaussian_elimination(A, b)
print("Solution:", solution)
