#include <iostream>
#include "darray.h"
#include "larray.h"
#include "nstack.h"
#include "nqueue.h"
#include "heap.h"
#include "sort.h"
using namespace std;
int main()
{
	int a[10] = { 2, -3, -1, 9, -5, 0, 2, 7, -10, 3 };
	quick_sort(a, 10);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << ' ';
	return 0;
}
// 2 -10 20 0 -9 3 14 0 30 6