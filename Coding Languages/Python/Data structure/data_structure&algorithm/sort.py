# ==============================================================================
# Quick sort
#===============================================================================
def __partition(A: list, left: int, right: int):
    i, j = left, right
    while i < j:
        while i < j and A[j] >= A[left]:
            j -= 1 # Find the first element from right to left which is smaller than A[left]
        while i < j and A[i] <= A[right]:
            i += 1 # Find the first element from left to right which is smaller than A[left]
        A[i], A[j] = A[j], A[i]
    A[i], A[left] = A[left], A[i]
    return i

def quick_sort(A: list, left: int, right: int):
    if left >= right:
        return None
    middle = __partition(A, left, right)
    quick_sort(A, left, middle - 1)
    quick_sort(A, middle + 1, right)


#================================================================================
# Counting sort
#================================================================================

def counting_sort(A: list[int], k: int):
    C = []
    for i in range(k + 2):
        C.append(0)
    B = []
    for item in A:
        B.append(item)
        C[item] += 1
    p = 0
    for i in range(0, k + 1):
        while C[i] > 0:
            A[p] = i
            p += 1
            C[i] -= 1
    