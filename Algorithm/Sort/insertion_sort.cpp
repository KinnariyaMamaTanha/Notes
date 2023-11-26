template <class T>
void insertion_sort(T* a, int size)
{
    for(int j = 1; j < size; ++j)
		{
				T key = a[j];
				i = j - 1;
				while(i >= 0 && a[i] > key)
				{
						a[i + 1] = a[i];
						--i;
				}
				a[i + 1] = key;
	  }
}
