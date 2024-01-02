"""Base convertion function."""
from nstack import nstack


def base_convert(number: str | int, new_base: int) -> str:
    """Convert a decimal number to numbers.with any other bases under 10."""
    tmp = nstack()
    number = int(number)
    while number != 0:
        tmp.push(number % new_base)
        number //= new_base
    res = str()
    while not tmp.empty():
        res += str(tmp.pop())
    return res
