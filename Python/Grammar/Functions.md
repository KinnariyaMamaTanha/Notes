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
6. The formal parameter could be function, too.(**Higher-order Function**)
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

7. A function can return two values:
```python
def func(x, y):
	return x // y, x % y 
```

8. You can define a function inside another function:
```python
def A(x)；
	i = 0
	def AA(y):
		return y + x
	……
```
And you can use the formal parameter of the outer function straightly in the inner function, like the `x` above. (Just like a new global environment)

Another thing to pay attention to is that you can write the following code outside the function `A` above:
```python
A(a)(b)
```
It's a call expression in which the operator is a call expression. Actually, it equals to `AA(b)` with x bounded to a, and it will return x+y for sure.

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

# Errors

1. Using `assert` to give a warning and break the current code block:

```python
assert boolean-statement: expression
```
When the boolean statement is **true**, nothing will happen, or it will return the value of the `expression`

```python
def div(x, y):
	assert y != 0: 'The divisor couldn\'t be 0'
	return x / y
```

Then  when you use the function wrongly with x = 1 and y = 0, it will return an error statement: 'The divisor couldn't be 0'

