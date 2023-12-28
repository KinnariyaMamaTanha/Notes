class stack(object):
    def __init__(self):
        self.data = []
    
    def pop(self):
        return self.data.pop()
    def push(self, item):
        self.data.append(item)
    def empty(self):
        return len(self.data) == 0
    def length(self):
        return len(self.data)
    def top(self):
        return self.data[len(self.data) - 1]


