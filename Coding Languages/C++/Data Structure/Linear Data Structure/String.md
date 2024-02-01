>[!note]
>*线性表强调对表中单个元素的操作，而字符串强调对整体进行操作*

字符串的基本方法
- `length()`：返回字符串长度
- `disp()`：输出所有字符
- `equal(s1, s2), greater(s1, s2), lesser(s1, s2)`：按字母序(或ASCII码)判断两个字符串的大小
- `copy(s1, s2)`：将$s_2$的值复制给$s_1$
- `cat(s1, s2)`：将$s_2$连接到$s_1$的末尾
- `substr(s, start, len)`：取子串
- `insert(s1, start, s2)`：插入字符串
- `remove(s, start, end)`：删除子串

# 一、顺序实现

顺序字符串类的声明：
```c++
class seqString
{
private:
	char* data;
	int len;
public:
	seqString(const char* s = "");
	seqString(const seqString& s);
	~seqString() { delete[] data; }
	int length() const { return len; }
	const seqString& operator=(const seqString& s);
	seqString substr(int start, int num) const;
	void insert(int start, const seqString& s);
	void remove(int start, int num);
	
	friend seqString operator+(const seqString& s1, const seqString& s2);
	friend bool operator==(const seqString& s1, const seqString& s2);
	friend bool operator!=(const seqString& s1, const seqString& s2);
	friend bool operator>(const seqString& s1, const seqString& s2);
	friend bool operator>=(const seqString& s1, const seqString& s2);
	friend bool operator<(const seqString& s1, const seqString& s2);
	friend bool operator<=(const seqString& s1, const seqString& s2);
	friend ostream& operator<<(ostream& os, const seqString& s);
}
```

顺序字符串类的方法定义

`seqString()`
```c++
seqString::seqString(const char* s = "")
{
	while(s[len] != '\0')
		++len;
	data = new char[len + 1];
	for(int i = 0; i < len; ++i)
		data[i] = s[i];
	data[len] = '\0';
}

seqString::seqString(const seqString& s)
{
	len = s.len;
	data = new char[len + 1];
	for(int i = 0; i < len; ++i)
		data[i] = s.data[i];
	data[len] = '\0';
}
```

`operator=()`
```c++
const seqString& seqString::operator=(const seqString& s)
{
	if(*this == s)
		return *this;
	delete[] data;
	len = s.len;
	for(int i = 0; i <= len; ++i)
		data[i] = s.data[i];
}
```

`substr()`
```c++
seqString seqString::substr(int start, int num) const
{
	if(!(start >= 0 && start < len))
		return "";
	seqString tmp;
	tmp.len = (start + num > len) ? len - start : num;
	delete tmp.data;
	tmp.data = new char[tmp.len + 1];
	for(int i = 0; i < tmp.len; ++i)
		tmp.data[i] = data[start + i];
	tmp.data[tmp.len] = '\0';
	return tmp;
}
```

`insert()`
```c++
void seqString::insert(int start, const seqString& s)
{
	if(start > len || start < 0)
		return;
	len += s.len;
	char* tmp = data;
	data = new char[len + 1];
	for(int i = 0; i < start; ++i)
		data[i] = tmp[i];
	for(int i = 0; i < s.len; ++i)
		data[i + start] = s.data[i];
	for(int i = start; tmp[i] != '\0'; ++i)
		data[i + s.len] = tmp[i];
	data[len] = '\0';
	delete tmp;
}
```

`remove()`
```c++
void seqString::remove(int start, int num)
{
	if(start >= len - 1 || start < 0)
		return;
	if(start + num >= len)
	{
		data[start] = '\0';
		len = start;
	}
	else
	{
		for(len = start; data[len + num] != '\0'; ++len)
			data[len] = data[len + num];
		data[len] = '\0';
	}
}
```
余下的方法不作笔记


# 二、链接实现

![[字符串的链接存储.png]]

这种方式使得insert和remove方法易于实现，但浪费空间（因为数据本身只占用一个字节，但指针却要占多个字节），可以使用块状链接存储

![[字符串的块状链接存储.png]]

块状链表提高了空间的利用率，但insert和remove方法都会引起大量的数据移动，为提高insert和remove方法的效率，可以为每个块多分配一些空闲空间

![[块状链表.png]]

![[块状链接字符串的分裂节点.png]]

![[块状链接字符串的插入子串.png]]

![[块状链接字符串的归并节点.png]]

链接串类的定义：
```c++
class linkString
{
private:
	struct node
	{
		int size; // 记录当前节点中所含字符的个数
		char* data;
		node* next;
		node(int s = 1, node* n = nullptr): size(s), next(n) {}
	};
	node* head; // 头节点，不包含字符
	int len; // 总长度
	int nodeSize; // 记录节点中所含字符个数的最大值
	
	void clear();
	void findPos(int start, int& pos, node* &p) const;
	void split(node* p, int pos);
	void merge(node* p);
public:
	linkString(const char* s = "");
	linkString(const linkString& s);
	~linkString();
	int length() const;
	linkString &operator=(const linkString& s);
	linkString substr(int start, int num) const;
	void insert(int start, const linkString& s);
	void remove(int start, int num);
	
	friend seqString operator+(const linkString& s1, const linkString& s2);
	friend bool operator==(const linkString& s1, const linkString& s2);
	friend bool operator!=(const linkString& s1, const linkString& s2);
	friend bool operator>(const linkString& s1, const linkString& s2);
	friend bool operator>=(const linkString& s1, const linkString& s2);
	friend bool operator<(const linkString& s1, const linkString& s2);
	friend bool operator<=(const linkString& s1, const linkString& s2);
	friend ostream& operator<<(ostream& os, const linkString& s);
};
```

链接串的方法实现：

`linkString()`
```c++
linkString::linkString(const char* s = "")
{
	for(len = 0; s[len] != '\0'; ++len); // 计算长度
	
	nodeSize = sqrt(len); // 为每个块分配合适的大小
	head = new node(1);
	node* p = head;
	while(*s) // 因为'\0'的ASCLL码值为0所以可以用来判定是否为结尾
	{
		p = p->next = new node(nodeSize);
		for(; p->size < nodeSize && *s; ++p->size, ++s)
			p->data[p->size] = *s;
	}
}

linkString::linkString(const linkString& s)
{
	len = size.len();
	nodeSize = s.nodeSize;
	head = new node(1);
	node* p = head;
	node* sp = s.head->next;
	while(sp != nullptr) // 也可写成while(sp)
	{
		p = p->next = new node(nodeSize);
		for(; p->size < sp->size; ++p->size)
			p->data[p->size] = sp->data[p->size];
		sp = sp->next;
	}
}
```

`clear()`
```c++
linkString::clear()
{
	node* p = head, *tmp;
	while(p != nullptr)
	{
		tmp = p->next;
		delete p;
		p = tmp;
	}
}
```

`~linkString()`
```c++
linkString::~linkString()
{
	clear();
	delete head;
}
```

`length()`
```c++
int linkString::length() const
{
	return len;
}
```

`operator=()`
```c++
linkString& linkString::operator=(const linkString& s)
{
	if(this == &s)
		return *this;
	clear();
	node* p = head;
	node* sp = head->next;
	len = s.len;
	nodeSize = s.nodeSize;
	while(sp != nullptr)
	{
		p = p->next;
		for(;p->size < sp->size; ++p->size)
			p->data[p->size] = sp->data[sp->size];
		sp = sp->next;
	}
	return *this;
}
```

`fingPos()`
```c++
void linkString::findPos(int start, int& pos, node* &p) const
// 第2、3个参数是返回参数，pos是第start个字符在其所在块的位置，p指向该字符所在的块
{
	int count = 0;
	p = head->next;
	while(count < start)
	{
		if(count + p->size < start)
		{
			count += p->size;
			p = p->next;
		}
		else
		{
			pos = start - count;
			return;
		}
	}
}
```

`substr()`
```c++
linkString linkString::substr(int start, int num) const
{
	linkString tmp;
	int count = 0, pos;
	node* p, * tp = tmp.head;
	if(start < 0 || start >= len - 1)
		return tmp;
	num = (start + num > len) ? len - start : num;
	tmp.len = num;
	tmp.nodeSize = sqrt(num);
	
	findPos(start, pos, p);
	
	for(int i = 0; i < tmp.len; ++i)
	{
		tp = tp->next = new node(tmp.nodeSize);
		for(; tp->size < tmp.nodeSize && i < tmp.len; ++tp->size, ++i)
		{
			if(pos == p->size)
			{
				p = p->next;
				pos = 0;
			}
			tp->data[tp->size] = p->data[pos++];
		}
	}
	return tmp;
}
```

`split()`
```c++
void linkStrig::split(node* p, int pos) // p指向需要被分裂的节点，pos为分裂的位置
{
	p->next = new node(nodeSize, p->next);
	for(int i = pos; i < p->size; ++i)
		p->next->data[i - pos] = p->data[pos];
	p->next->size = p->size - pos;
	p->size = pos;
}
```

`merge()`
```c++
void linkString::merge(node* p) // 如果p指向的节点可以与后继合并，则合并
{
	if(p->size + p->next->size <= nodeSize)
	{
		node* tmp = p->next;
		for(int i = 0; i < tmp->size; ++i)
			p->data[p->size + i + 1] = tmp->data[i];
		p->next = tmp->next;
		p->size += tmp->size;
		delete tmp;
	}
}
```
	
`insert()`
```c++
void linkString::insert(int start, const linkString& s)
{
	if(start < 0 || start > len)
		return;
	node* p;
	int pos;
	findPos(start, pos, p);
	split(p, pos);
	node* tmp = p->next;
	p->next = s.head;
	node* sp = s.head;
	while(sp->next != nullptr)
		sp = sp->next;
	sp->next = tmp;
	merge(sp);
}
```

`remove()`
```c++
void linkString::remove(int start, int num)
{
	if(start < 0 || start >= len - 1)
		return;
	node* p;
	int pos;
	findPos(start, pos, p);
	split(p, pos);
	if(start + num >= len)
	{
		node* q = p->next, * r;
		while(q != nullptr)
		{
			r = q->next;
			delete q;
			q = r;
		}
		p->next = nullptr;
	}
	else
	{
		node* endp;
		int endpos;
		findPos(start + num, endpos, endp);
		split(endp, endpos);
		endp = endp->next;
		node* q = p->next, * r;
		while(q != endp)
		{
			r = q->next;
			delete q;
			q = r;
		}
		p->next = endp;
		merge(p);
	}
}
```

余下方法不作笔记

# 三、字符串的匹配

>*常常需要在一个字符串中寻找是否出现了另外一个字符串*

1. 最简单的方法是线性查找，最坏时间复杂度为$O(mn)$
2. 可以使用KMP算法，最坏时间复杂度为$O(n)$

# 四、STL中的字符串

>*详见[[Coding Languages/C++/Grammars/标准数据类型/字符串#^a7e6d8|字符串]]*
