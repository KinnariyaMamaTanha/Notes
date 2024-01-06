import random

# ==============================================================================
# Quick sort
# ==============================================================================
def __partition(A: list, left: int, right: int) -> int:
    i, j = left, right
    while i < j:
        while i < j and A[j] >= A[left]:
            j -= 1 # Find the first element from right to left which is smaller than A[left]
        while i < j and A[i] <= A[left]:
            i += 1 # Find the first element from left to right which is smaller than A[left]
        A[i], A[j] = A[j], A[i]
    A[i], A[left] = A[left], A[i]
    return i

def __partition_for_select(A: list, left: int, right: int, x):
    i = left
    while A[i] != x:
        i += 1
    A[i], A[left] = A[left], A[i]
    return __partition(A, left, right)
        
def __quick_sort(A: list, left: int, right: int) -> None:
    if left >= right:
        return None
    middle = __partition(A, left, right)
    __quick_sort(A, left, middle - 1)
    __quick_sort(A, middle + 1, right)
    
# ===============================================================================
# Random Quick Sort
# ===============================================================================
def __random_partition(A: list, left: int, right: int) -> int:
    tmp_index = random.randint(left, right)
    A[left], A[tmp_index] = A[tmp_index], A[left]
    return __partition(A, left, right)
    
def __random_quick_sort(A: list, left: int, right: int) -> None:
    if left >= right:
        return
    middle = __random_partition(A, left, right)
    __random_quick_sort(A, left, middle - 1)
    __random_quick_sort(A, middle + 1, right)
    
def quick_sort(A:list, func = __random_quick_sort) -> None:
    func(A, 0, len(A) - 1)

# ===============================================================================
# Counting sort
# ===============================================================================

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
    
