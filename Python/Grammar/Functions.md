# Basics

1. Two types of functions:
	1. **Pure functions**: Pure functions have the property that applying them has no effects beyond returning a value. Moreover, a pure function must always return the same value when called twice with the same arguments.
	2. **Non-pure functions**: Has side effects, making some changes to the interpreter or computer, like `print`
2. Define new functions:
```python
def <name>(<formal parameters>):
	statements
	return <return expression>
```
3. The function name can be redefined to do another operations:
```python
def g(x):
	return x == 1

def g(x, y):
	return x + y
```
This is different from the function overloads in C++, which means after the redefinition, you can only use `g(x, y)`.

4. **Function signatures**: a description of the formal parameters of a function.
5. **Default argument values**: you can set the default argument value just like that in C++.
6. The formal parameter could be function, too.
```python
square = lambda x: x ** 2
cube = lambda x: x ** 3

def sum(x, term):
	ans = 0
	for i in range(1, x + 1):
		ans += term(i)
	return ans

print(sum(5, square))
print(sum(5, cube))
```

output:
```python
55
225
```

# Importing Functions

1. syntax:

`from <LibraryName> import <functionName> as <abbreviationName>`

e.g: `from math import pi as p`

# Docstring

>*Docstring is used to describe the function, useful!!!*

e.g: 
```python
def pressure(v, t, n):
        """Compute the pressure in pascals of an ideal gas.

        Applies the ideal gas law: http://en.wikipedia.org/wiki/Ideal_gas_law

        v -- volume of gas, in cubic meters
        t -- absolute temperature in degrees kelvin
        n -- particles of gas
        """
        k = 1.38e-23  # Boltzmann's constant
        return n * k * t / v
```
The comments enclosed by three double quotations marks is docstring. When using command `help(pressure)` in Python interpreter, it will show the docstring on the screen.

# Lambda

>*To create a anonymous function, use lambda*

Syntax:
```python
lambda argument-list: expression
```

e.g
```python
square = lambda x: x * x
add = lambda x, y: x + y
sub = lambda x, y: x - y
```
