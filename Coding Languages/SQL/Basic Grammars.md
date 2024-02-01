# Basics

1. 进入命令行中的sqlite3: `sqlite3`
2. 退出命令行: `.quit`

>[!attention] 
>在命令行中使用sqlite3创建的数据库都是`transient in-memory database`，即程序结束后就消亡的数据库

3. 注释语句：
```sql
-- 单行注释，注意要和--空一格
/* 
多行注释
和C++中相同
*/
```

4. SQL中的`/`除法是**整数除法**
5. 布尔语句中的相等使用`=`而非`==`
6. 使用运算符`||`可以连接两个字符串
```sql
sqlite> with wall(n) as (
  ....>   select 99 union select 98 union select 97
  ....> )
  ....> select n || " bottles" from wall;
99 bottles
98 bottles
97 bottles
```

# Table

## 2.1 Create a table

1. 直接使用`select`语句创建一个无名表，语法：
```sql
select <data1> as <column name1>, ..., <datan> as <column namen>; 
```
```sql
sqlite> select 38 as latitude, 122 as longitude, "Berkeley" as name;
38|122|Berkeley
```

>[!note] 
>SQL中的所有语句以分号`;`结尾

2. 当表格有多行时，使用`union`语句：
```sql
sqlite> select 38 as latitude, 122 as longitude, "Berkeley" as name union
   ...> select 23, 123, "SomePlace" union
   ...> select 0, 0, "Center";
0|0|Center
23|123|SomePlace
38|122|Berkeley
```
注意第二行及之后可以省略列名；倒数第一行及之前不能写分号`;`

3. 使用`create`语句创建有名字的表格
```sql
sqlite> create table places as
   ...> select 38 as latitude, 122 as longitude, "Berkeley" as name union
   ...> select 23, 123, "SomePlace" union
   ...> select 0, 0, "Center";
```
当省略名称时，将创建一个无名表格

4. 使用`select`语句，根据已有表格创建一个新表格（见下节）

## 2.2 Select from a table

1. 语法：
```sql
select [column name1], ..., [column namen] from [existing table name]
```
被称为使用现有表格进行**投影**来定义一个新表
```sql
sqlite> create table places as
   ...> select 38 as latitude, 122 as longitude, "Berkeley" as name union
   ...> select 23, 123, "SomePlace" union
   ...> select 0, 0, "Center";
sqlite> select latitude, name from places;
0|Center
23|SomePlace
38|Berkeley
```

2. 当使用`*`代替`[column name]`时，将导入所有列
```sql
sqlite> create table places as
   ...> select 38 as latitude, 122 as longitude, "Berkeley" as name union
   ...> select 23, 123, "SomePlace" union
   ...> select 0, 0, "Center";
sqlite> select * from places;
0|0|Center
23|123|SomePlace
38|122|Berkeley
```

3. 可以使用表达式代替`[column name]`
```sql
sqlite> select name, abs(latitude - longitude) from places;
Center|0
SomePlace|100
Berkeley|84
```

4. 使用`select`语句创建新表
```sql
sqlite> create table places2 as
   ...> select abs(latitude - 60) / 5 as new_name, name from places; -- as命名
sqlite> select * from places2;
12|Center
7|SomePlace
4|Berkeley
sqlite> select new_name from places2;
12
7
4
```

5. `where`子句用于过滤行
```sql
sqlite> create table high as
   ...> select name from places where latitude > 10;
sqlite> select * from high;
SomePlace
Berkeley
sqlite> select name, "is high!" from high; -- select的参数不一定都来源于from后的原表
SomePlace|is high!
Berkeley|is high!
```

6. `order`子句用于为行排序（默认从小到大）
```sql
sqlite> select name, longitude from places order by longitude;
Center|0
Berkeley|122
SomePlace|123
```

7. 目前为止，不包含`union`的完整`select`语法如下：
```sql
with [tables] select [columns] from [names] where [condition] order by [order]
```

其中，`[tables] `部分是一个逗号分隔的列表，其中每个元素都是以下格式的表描述：
```sql
[table name]([column names]) as ([select statement])
```

示例：
```sql
sqlite> with
   ...>   states(city, state) as (
   ...>     select "Berkeley",  "California"    union
   ...>     select "Boston",    "Massachusetts" union
   ...>     select "Cambridge", "Massachusetts" union
   ...>     select "Chicago",   "Illinois"      union
   ...>     select "Pasadena",  "California"
   ...>   )
   ...> select a.city, b.city, a.state from states as a, states as b
   ...>        where a.state = b.state and a.city < b.city;
Berkeley|Pasadena|California
Boston|Cambridge|Massachusetts
```

8. 递归`select`语句。在`with`子句中可能出现递归的情况，如：
```sql
sqlite> with
   ...>   ints(n) as (
(x1...>     select 5 union
(x1...>     select n+1 from ints where n < 15
(x1...>   )
   ...> select n, n*n from ints where n % 2 = 1;
5|25
7|49
9|81
11|121
13|169
15|225
```

构造斐波那契数列：
```sql
sqlite> with
   ...>   fib(prev, next) as (
(x1...>       select 0, 1 union
(x1...>       select next, prev + next from fib where prev <= 1000
(x1...>   )
   ...> select prev from fib;
0
1
1
2
3
5
8
13
21
34
55
89
144
233
377
610
987
1597
```

## 2.3 Join the tables

1. 一个n行的表和一个m行的表直接进行连接，将产生一个m\*n行的新表
```sql
sqlite> create table cities as
   ...> select 38 as latitude, 122 as longitude, "Berkeley" as name union
   ...> select 42,             71,               "Cambridge"        union
   ...> select 45,             93,               "Minneapolis";
sqlite> create table temps as
   ...> select "Berkeley" as city, 68 as temp union
   ...> select "Chicago"         , 59         union
   ...> select "Minneapolis"     , 55;
sqlite> select * from cities, temps;
38|122|Berkeley|Berkeley|68
38|122|Berkeley|Chicago|59
38|122|Berkeley|Minneapolis|55
42|71|Cambridge|Berkeley|68
42|71|Cambridge|Chicago|59
42|71|Cambridge|Minneapolis|55
45|93|Minneapolis|Berkeley|68
45|93|Minneapolis|Chicago|59
45|93|Minneapolis|Minneapolis|55
```

2. 使用`where`子句进行筛选：
```sql
sqlite> select name, latitude, temp from cities, temps where name = city;
Berkeley|38|68
Minneapolis|45|55
```

3. 在`from`子句中使用`as`为表命别名，并用点表达式表示特定的列
```sql
sqlite> select a.city, b.city, a.temp - b.temp
   ...>        from temps as a, temps as b where a.city < b.city;
Berkeley|Chicago|10
Berkeley|Minneapolis|15
Chicago|Minneapolis|5
```

4. 之前介绍的`union`关键字也是连接表的一种方法

>[!note] 
>`union`用于连接行，`join`用于连接列

## 2.4 Aggregation and grouping

### 2.4.1 Aggregation

1. 函数`min`，`max`，`count`，`sum`返回列中的最小、最大、数量、总和
2. `distinct`关键字用于聚合时不统计相同值的行
```sql
sqlite> create table animals as
  ....>   select "dog" as name, 4 as legs, 20 as weight union
  ....>   select "cat"        , 4        , 10           union
  ....>   select "ferret"     , 4        , 10           union
  ....>   select "t-rex"      , 2        , 12000        union
  ....>   select "penguin"    , 2        , 10           union
  ....>   select "bird"       , 2        , 6;
sqlite> select max(legs) from animals;
4
sqlite> select sum(weight) from animals;
12056
sqlite> select min(legs), max(weight) from animals where name <> "t-rex";
2|20

--The distinct keyword ensures that no repeated values in a column are included in the aggregation. Only two distinct values of legs appear in the animals table. The special count(*) syntax counts the number of rows.
sqlite> select count(legs) from animals;
6 -- 'legs' has 6 values(but not distinct).
sqlite> select count(*) from animals;
6 -- There are 6 rows in animal.
sqlite> select count(distinct legs) from animals;
2 -- 'legs' has two distinct values
```

### 2.4.2 Grouping

1. `group by`子句和`having`子句用于将行按照某种方式分为若干组，并对这些组进行`select`操作
```sql
sqlite> select legs, max(weight) from animals group by legs;
2|12000
4|20
sqlite> select weight from animals group by weight having count(*) > 1;
10
```
- 上述第一例中，`group by legs`表示将表`animals`的所有行按照`legs`的值进行分组，并对每一个组进行`select legs max(weight)`操作，最后得出结论：`legs = 2`的`animal`的`max(weight)`为12000；`legs = 4`的`animal`的`max(weight)`为20
- 第二例中，`group by weight having count(*) > 1`表示将表`animal`按照`count(weight) > 1`来分组（这里只有`weight = 10`时满足），并对每一个组进行`select weight`操作，亦即，找出所有重复出现过的`weight`值

2. `group by`子句中可以拥有多个列参数或表达式，为每一个产生的唯一值进行分组
```sql
sqlite> select max(name) from animals group by legs, weight order by name;
bird
dog
ferret
penguin
t-rex
sqlite> select max(name), legs, weight from animals group by legs, weight
  ....>   having max(weight) < 100;
bird|2|6
penguin|2|10
ferret|4|10
dog|4|20
sqlite> select count(*), weight/legs from animals group by weight/legs;
2|2
1|3
2|5
1|6000
```
通常将分组依据也列入新表，以便查看

3. `having`子句可以包含和`where`子句相同的过滤条件，也可包含聚合函数的调用。为了获得最快的执行速度和最清晰的语言使用方式，应将基于其内容过滤单个行的条件放在 `where` 子句中，而只有在需要聚合条件时才应使用 `having` 子句（例如指定组的最小计数）。
4. 当使用`group by`子句时，列描述中可以包含不进行聚合的表达式，但是当对应于聚合的行不明确时，将会返回不确定的值，如：
```sql
sqlite> select name, count(legs) from animals group by legs
dog|4
t-rex|2
sqlite> select name, count(legs) from animals group by legs
cat|4
bird|2
```

>[!summary] 
>至此，我们得到`select`语句的完整形式为：
>1. `with [tables] select [column expressions] as [alias] from [names] as [alias] where [conditions] order by [expression] group by [expressions] having [conditions];`
>2. `select [value1] as [name1], ..., [valuen] as [namen] union ... union ...;`
