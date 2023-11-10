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

# Importing Functions

1. syntax:

`from <LibraryName> import <functionName> as <abbreviationName>`

e.g: `from math import pi as p`
