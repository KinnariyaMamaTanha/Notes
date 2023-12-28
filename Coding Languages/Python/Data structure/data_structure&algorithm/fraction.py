from math import gcd
class fraction(object):
    def __init__(self, num: int, den: int):
        fact = gcd(num, den)
        self.num = num // fact
        self.den = den // fact
        
    def __str__(self):
        if self.den != 1:
            return str(self.num) + "/" + str(self.den)
        else:
            return str(self.num)
        
    def __add__(self, f):
        num = self.num * f.den + self.den * f.num
        den = self.den * f.den
        fact = gcd(num, den)
        num //= fact
        den //= fact
        if den < 0:
            den, num = -den, -num
        return fraction(num, den)

    def __eq__(self, f):
        return self.den == f.den and self.num == f.num

    def __bool__(self):
        return self.num != 0
