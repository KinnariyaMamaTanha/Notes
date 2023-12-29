from heap import heap

a = heap(greater=True)
for i in range(5):
    a.push(float(input()))
    print(a)

for i in range(5):
    print(a.pop())
    print(a)
