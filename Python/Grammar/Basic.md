# Expressions

## 1. Call Expressions

basic structure:
`operator(operant1, operant2, ..., operantn)`

e.g: `max(2, 4)`  `pow(2, 100)`

## 2. Assignment Expressions

1. Names can bind to values and **functions**, e.g: `f = max`(The type of `f` is *builtin_function_or_method*)
2. One can bind function names to values: `max = 5`(But the max function can't be used with the name max after that)

# Name and Environment

>Names can binds to values. The memory to keep track of the names, values and bindings is called **environment**

1. **Intrinsic name**: the name appearing in the function.
2. **Bound name**: the name in a frame.

![[Frame and Environment.png]]

Frame is different from environment. Take the picture above as an example:

There are two environments: the global one in which the expression `square(-2)` is evaluated, and the second one created for by calling `square`. Both `x` and `mul` are bound in the second environment, but in different frames.

And if a function is called for two times in the same environment, it will create two frames in the same environment. The variables with the same name in different frames are different from each other.

3. **Name Evaluation.** A name evaluates to the value bound to that name in the earliest frame of the current environment in which that name is found.
4. **Scope**: The parameter names of a function must remain local to the body of the function and the _scope_ of a local name is limited to the body of the user-defined function that defines it.

# None

None in Python is a special value which means "nothing". When a function doesn't explicitly have a return value, it returns None.

Take `print()` for example, when you run the following codes:
```python
print(print(1), print(2))
```
you will get the output:
```python
1
2
None None
```
Because the function `print()` implicitly returns the value **None**

The same is for user-defined functions, like:
```python
def square(x):
	x * x

print(square(4))
```
You will not get the result 16, instead, the output is:
```python
None
```
for the function `square` returns **None** implicitly.
