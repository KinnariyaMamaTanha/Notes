#include <iostream>
#include "darray.h"
#include "larray.h"
#include "nstack.h"
#include "nqueue.h"
#include "heap.h"
using namespace std;
int main()
{
	dheap<int> a(3);
	int tmp;
	for (int i = 0; i < 10; ++i)
	{
		cin >> tmp;
		a.push(tmp);
		cout << a << endl;
	}
	cout << a << endl;
	cout << a.front() << endl;
	a.pop();
	cout << a << endl;
	a.push(-1);
	cout << a << endl;
	a[2] = 40;
	a.heapify();
	cout << a << endl;
	cout << a[-6] << endl;
	return 0;
}
// 2 -10 20 0 -9 3 14 0 30 6