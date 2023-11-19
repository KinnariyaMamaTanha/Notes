def insertion_sort(a, size):
    for j in range(1, size):
        key = a[j]
        i = j - 1
        while i >= 0 and a[i] > key:
            a[i + 1] = a[i]
            i -= 1
    a[i + 1] = key


