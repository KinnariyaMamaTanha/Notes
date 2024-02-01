> 在`for`循环中，如果使用`for (<type> x: <Object>)`，则要求被循环的对象应为可迭代的，这个·`for`循环等价于：

```java
Iterator<type> it = <object>.iterator();
while (it.hasNext()) {
	<type> x = it.next();
	...
}
```

Java提供了`Iterable`接口：
```java
public interface Iterable<T> {
	Iterator<T> iterator();
}
```
包含一个返回`Iterator`接口的方法，而`Iterator`接口(`java.util`中)：
```java
public interface Iterator<T> {
	boolean hasNext();
	T next();
}
```
则若想使某个自定义类成为可迭代的，则可以在其中添加一个实现了`Iterator`接口的私有类，该类再实现`Iterable`接口，定义的`iterator()`函数返回之前定义的私有类
```java
public Iterator<T> iterator() {
	return new <private_Iterator>();
}
```
一个示例：
```java
import java.util.Iterator;

public class ArraySet<T> implements Iterable<T> {
    private T[] items;
    private int size; // the next item to be added will be at position size

    public ArraySet() {
        items = (T[]) new Object[100];
        size = 0;
    }

    /* Returns true if this map contains a mapping for the specified key.
     */
    public boolean contains(T x) {
        for (int i = 0; i < size; i += 1) {
            if (items[i].equals(x)) {
                return true;
            }
        }
        return false;
    }

    /* Associates the specified value with the specified key in this map.
       Throws an IllegalArgumentException if the key is null. */
    public void add(T x) {
        if (x == null) {
            throw new IllegalArgumentException("can't add null");
        }
        if (contains(x)) {
            return;
        }
        items[size] = x;
        size += 1;
    }

    /* Returns the number of key-value mappings in this map. */
    public int size() {
        return size;
    }

    /** returns an iterator (a.k.a. seer) into ME */
	@Override
    public Iterator<T> iterator() {
        return new ArraySetIterator();
    }

    private class ArraySetIterator implements Iterator<T> {
        private int wizPos;

        public ArraySetIterator() {
            wizPos = 0;
        }

		@Override
        public boolean hasNext() {
            return wizPos < size - 1;
        }

		@Override
        public T next() {
            T returnItem = items[wizPos];
            wizPos += 1;
            return returnItem;
        }
    }

    public static void main(String[] args) {
        ArraySet<Integer> aset = new ArraySet<>();
        aset.add(5);
        aset.add(23);
        aset.add(42);

        //iteration
        for (int i : aset) {
            System.out.println(i);
        }
    }
}
```