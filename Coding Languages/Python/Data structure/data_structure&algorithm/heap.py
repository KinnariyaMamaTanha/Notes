class heap(object):
    def __init__(self, greater: bool = False):
        """"The heap is a binary heap by default, whose 0th position does not store any item.
            It is a maximal heap if greater = 1, otherwise a minimal heap"""
        self.data = [-1]
        self.greater = greater
        
    def __percolateDown(self, hole: int) -> None:
        tmp = self.data[hole]
        l = len(self.data)
        nxt = hole * 2
        if self.greater:
            while nxt < l:
                if nxt + 1 < l and self.data[nxt] < self.data[nxt + 1]:
                    nxt += 1
                if tmp < self.data[nxt]:
                    self.data[hole] = self.data[nxt]
                    hole, nxt = nxt, nxt * 2
                else:
                    break
        else:
            while nxt < l:
                if nxt + 1 < l and self.data[nxt] > self.data[nxt + 1]:
                    nxt += 1
                if tmp > self.data[nxt]:
                    self.data[hole] = self.data[nxt]
                    hole, nxt = nxt, nxt * 2
                else:
                    break
        self.data[hole] = tmp
    
    def push(self, item):
        self.data.append(item)
        hole = len(self.data) - 1
        if self.greater:
            while hole > 1 and item > self.data[hole // 2]:
                self.data[hole] = self.data[hole // 2]
                hole //= 2
        else:
            while hole > 1 and item < self.data[hole // 2]:
                self.data[hole] = self.data[hole // 2]
                hole //= 2
        self.data[hole] = item
    
    def pop(self):
        tmp = self.data[1]
        if self.length() == 1:
            self.data.pop()
            return tmp
        self.data[1] = self.data[self.length()]
        self.data.pop()
        self.__percolateDown(1)
        return tmp
    
    def length(self) -> int:
        return len(self.data) - 1
    
    def empty(self) -> bool:
        return self.length() == 0

    def heapify(self):
        l = self.length() // 2
        for i in self.data[l:1:-1]:
            self.__percolateDown(i)
        
    def __contains__(self, item):
        for x in self.data:
            if x == item:
                return True
        return False
    
    def __str__(self):
        if self.empty():
            return "binary_heap()"
        s = "binary_heap("
        for item in self.data[1:self.length()]:
            s += str(item) + ", "
        s += str(self.data[self.length()])
        return s + ")"

            
