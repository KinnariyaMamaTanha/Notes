class nstack(object):
    def __init__(self):
        self.data = []
    
    def pop(self):
        if len(self.data) == 0:
            return None
        else:
            return self.data.pop()
    def push(self, item):
        self.data.append(item)
    def empty(self):
        return len(self.data) == 0
    def length(self):
        return len(self.data)
    def top(self):
        if len(self.data) == 0:
            return None
        else:
            return self.data[len(self.data) - 1]

    def size(self):
        return self.length()

    def __str__(self):
        return "new_stack" + str(self.data)

    def __getitem__(self, i):
        return self.data[i]

    def __contains__(self, item):
        for i in  range(len(self.data)):
            if self.data[i] == item:
                return True
        return False

