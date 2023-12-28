from timeit import Timer

def test1():
    l = list(range(1000000))
    
def test2():
    l = []
    for i in range(1000000):
        l.append(i)

t1 = Timer("test1()", "from __main__ import test1")
print(t1.timeit(number=10))
t2 = Timer("test2()", "from __main__ import test2")
print(t2.timeit(number=10))
