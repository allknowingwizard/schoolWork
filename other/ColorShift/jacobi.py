import numpy as np

ITERATION_LIMIT = 50

# initialize the matrix
A = np.array([[1., 2.],
              [3., 4.]])
# initialize the RHS vector
b = np.array([3., 7.])
# prints the system
#print("System:")
def jacobi(A, b):
    for i in range(A.shape[0]):
        row = ["{}*x{}".format(A[i, j], j + 1) for j in range(A.shape[1])]
        #print(" + ".join(row), "=", b[i])
    #print()

    x = np.zeros_like(b)
    for it_count in range(ITERATION_LIMIT):
        #print("Current solution:", x)
        x_new = np.zeros_like(x)

        for i in range(A.shape[0]):
            s1 = np.dot(A[i, :i], x[:i])
            s2 = np.dot(A[i, i + 1:], x[i + 1:])
            x_new[i] = (b[i] - s1 - s2) / A[i, i]

        if np.allclose(x, x_new, atol=1e-10, rtol=0.):
            break

        x = x_new

    #print("Solution:")
    #print(x)
    error = np.dot(A, x) - b
    #print("Error:")
    #print(error)
    return x

print(jacobi(A,b));
