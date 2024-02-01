# 一、条件语句

> 和C++中基本一致

## 1.1 if语句

```java
public class ClassName {
	public static void main(String[] args){
		int x = 5;
		if (x < 10){
			System.out.print(x);
		} else if (x < 20){
			x += 10;
		} else {
			x += 20;
		}
	}
}
```

## 1.2 switch语句

语法：
```java
switch (<expression>) {
	case <case1>: 
		<statements>
		// break;
	...
	default: 
		<statements>
}
```
- `case`后的标签只能是字符串常量或字面量
- `default`分支不需要`break`
- `<statements>`运行规则和C++中相同

# 二、循环语句

> 和C++中基本一致

1. `break`和`continue`用法同C++一致

## 2.1 while循环

```java
while (<condition>){
	<statements>
}
```

## 2.2 for循环

1. 使用索引的for循环
```java
for (<initial-expr>; <boolean-expr>; <expr>){
	<statements>
}
```
2. 不使用索引的for循环
```java
for (<typename> c: s){
	<statements>
}
```