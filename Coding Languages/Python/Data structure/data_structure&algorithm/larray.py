class larray(object):
    class node:
        def __init__(self, data = None, nxt = None, pre = None):
            self.data = data
            self.next = nxt
            self.prev = pre
            
    def __init__(self):
        self.head = larray.node()
        self.tail = larray.node()
        self.head.next = self.tail
        self.tail.prev = self.head
        
    def __move(self, i: int) -> node:
        """Return the ith node of the linked array. If i exceeds the scope, return the head or the tail"""
        if i >= 0:
            p = self.head.next
            while i and p != self.tail:
                p = p.next
                i -= 1
        else:
            p = self.tail
            while i and p != self.head:
                p = p.prev
                i += 1
        return p
        
    def empty(self):
        return self.head.next == self.tail
    
    def length(self):
        p = self.head.next
        length = 0
        while p != None:
            length += 1
            p = p.next
        return length
    
    def size(self):
        return self.length()
    
    def pop(self, i: int):
        """Pop out and return the ith node. If i exceeds the scope, return None"""
        p = self.__move(i)
        if p != self.head and p != self.tail:
            p.next.prev = p.prev
            p.prev.next = p.next
            return p
        else:
            return None
            
    def push(self, data, i: int):
        """Push the data to the ith position. If i exceeds the scope, push data to the head or the tail"""
        if self.empty():
            tmp = larray.node(data, self.tail, self.head)
            self.head.next = tmp
            self.tail.prev = tmp
            return True
        p = self.__move(i)
        if p == self.head:
            tmp = larray.node(data, self.head.next, self.head)
            self.head.next.prev = tmp
            self.head.next = tmp
        elif p == self.tail:
            tmp = larray.node(data, self.tail, self.tail.prev)
            self.tail.prev.next = tmp
            self.tail.prev = tmp
        else:
            tmp = larray.node(data, p, p.prev)
            p.prev.next = tmp
            p.prev = tmp
        return True
    
    def index(self, item):
        """Return the position of item. If not existing, return -1"""
        p = self.head.next
        i = 0
        while p != self.tail:
            if p.data == item:
                return i
            i += 1
            p = p.next
        return -1
            
    def __str__(self):
        s = "linked_array("
        p = self.head.next
        while p.next != self.tail:
            s += str(p.data) + ", "
            p = p.next
        s += str(p.data)
        return s + ")"
    
    def __contains__(self, item):
        p = self.head.next
        while p != self.tail:
            if p.data == item:
                return True
            p = p.next
        return False
        
        
        
            
            
