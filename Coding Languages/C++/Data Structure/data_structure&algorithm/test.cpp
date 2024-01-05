#include <iostream>
#include "darray.h"
#include "larray.h"
#include "nstack.h"
#include "nqueue.h"
#include "heap.h"
#include "sort.h"
#include "order_statistic.h"
using namespace std;
int main()
{
	int a[] = { 2, 12, 10, 13, 5, 20, 14, 17, 7, 3, 15, 30 };
	cout << order_statistic(a, 10, 4) << endl;
	quick_sort(a, 10);
	for (int i = 0; i < 10; ++i)
		cout << a[i] << ' ';
	return 0;
}
// 2 -10 20 0 -9 3 14 0 30 6