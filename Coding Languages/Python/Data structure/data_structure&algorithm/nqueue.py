class nqueue(object):
    def __init__(self):
        self.data = []
        
    def push(self, item):
        self.data.append(item)

    def push_front(self, item):
        self.data.insert(0, item)
        
    def pop(self):
        if self.empty():
            return None
        else:
            return self.data.pop(0)

    def pop_back(self):
        if self.empty():
            return None
        else:
            return self.data.pop()

    def empty(self) -> bool:
        return len(self.data) == 0

    def length(self) -> int:
        return len(self.data)

    def size(self) -> int:
        return self.length()

    def front(self):
        if self.empty():
            return None
        else:
            return self.data[0]

    def back(self):
        if self.empty():
            return None
        else:
            return self.data[len(self.data) - 1]
        
    def __str__(self):
        return "new_queue" + str(self.data)

    def __bool__(self):
        return self.empty()

    def __getitem__(self, i):
        return self.data[i]
    
    def __contains__(self, item):
        for i in  range(len(self.data)):
            if self.data[i] == item:
                return True
        return False