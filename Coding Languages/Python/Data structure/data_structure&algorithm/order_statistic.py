import sort

# ===============================================================================
# Order Statistic
# ===============================================================================
def __random_select(A: list, left: int, right: int, i: int):
    # i is from 0 to len(A) - 1, use randomized algorithm
    if left == right:
        return A[left]
    middle = sort.__random_partition(A, left, right)
    k = middle - left
    if k == i:
        return A[left + k]
    elif k > i:
        return __random_select(A, left, middle - 1, i)
    else:
        return __random_select(A, middle + 1, right, i - k - 1)

def __select(A: list, left: int, right: int, i: int):
    if left == right:
        return A[left]
    n = (right - left) // 5 + 1
    B = []
    for i in range(0, n - 1):
        B.append(__median(A, left + 5 * i, left + 5 * i + 4))
    B.append(__median(A, left + 5 * (n - 1), right))
    x = __median(B, 0, len(B) - 1)
    middle = sort.__partition_for_select(A, left, right, x)
    k = middle - left
    if i == k:
        return A[middle]
    elif i < k:
        return __select(A, left, middle - 1, i)
    else:
        return __select(A, middle + 1, right, i - k - 1)
    
def __median(A: list, left: int, right: int, func = __random_select):
    return func(A, left, right, (right - left) // 2)

def order_statistic(A: list, index: int, func = __select):
    # index is from 1 to len(A)
    return func(A, 0, len(A) - 1, index - 1)

