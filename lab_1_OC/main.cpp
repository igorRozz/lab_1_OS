#include "alloc.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void test(alloc* alloc, size_t mSize, void* ptrs[], size_t* ptrsCount, size_t iterCount)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < iterCount; i++)
	{
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
		cout << (i + 1);
		cout << " iteration\n";
		int a;
		if (*ptrsCount == 0)
		{
			a = 0;
		}
		else
		{
			a = (int)rand() * 3 / RAND_MAX;
			if (a == 3)
			{
				a--;
			}
		}
		switch (a)
		{
		case 0:
		{
			size_t s = (size_t)(rand() * (mSize / 20) / RAND_MAX);
			if (s == 0)
			{
				s++;
			}
			cout << "mem_alloc(";
			cout << s;
			cout << ")\n";
			void* ptr = alloc->mem_alloc(s);
			if (ptr != NULL)
			{
				ptrs[*ptrsCount] = ptr;
				*ptrsCount = *ptrsCount + 1;
			}
			cout << "ptr = ";
			cout << ptr;
			cout << "\n";
			break;
		}
		case 1:
		{
			size_t e = (size_t)(rand() * (*ptrsCount) / RAND_MAX);
			cout << "mem_free(";
			cout << ptrs[e];
			cout << ")\n";
			alloc->mem_free(ptrs[e]);
			for (int i = e + 1; i < *ptrsCount; i++)
			{
				ptrs[i - 1] = ptrs[i];
			}
			*ptrsCount = *ptrsCount - 1;
			break;
		}
		case 2:
		{
			size_t s = (size_t)(rand() * (mSize / 20) / RAND_MAX);
			srand((unsigned)time(NULL));
			size_t e = (size_t)(rand() * (*ptrsCount) / RAND_MAX);
			cout << "mem_realloc(";
			cout << ptrs[e];
			cout << ", ";
			cout << s;
			cout << ")\n";
			void* ptr = alloc->mem_realloc(ptrs[e], s);
			if (ptr != NULL)
			{
				ptrs[e] = ptr;
			}
			cout << "ptr = ";
			cout << ptr;
			cout << "\n";
			break;
		}
		}
		alloc->mem_dump();
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
	}
}

int main()
{
	const size_t mSize = 4096;
	alloc alloc(mSize);
	void* ptrs[341];
	size_t ptrsCount = 0;
	int a = -1;

	cout << "Rozum Ihor IS-73\n";

	while (a != 0)
	{
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
		cout << "Memory size: ";
		cout << mSize;
		
			cout << "\n";
		alloc.mem_dump();
		cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n";
		cout << "Choose the action:\n";
		cout << "1 - Test alloc\n";
		cout << "2 - Allocate memory\n";
		if (ptrsCount != 0)
		{
			cout << "3 - Free memory\n";
			cout << "4 - Reallocate memory\n";
		}
		cout << "0 - Exit\n";
		cout << "> ";
		cin >> a;
		switch (a)
		{
		case 1:
		{
			size_t iterCount;
			cout << "Enter the number of iterations.\n";
			cout << "> ";
			cin >> iterCount;
			test(&alloc, mSize, ptrs, &ptrsCount, iterCount);
			break;
		}
		case 2:
		{
			size_t size;
			cout << "Enter the size of memory to allocate.\n";
			cout << "> ";
			cin >> size;
			void* ptr = alloc.mem_alloc(size);
			if (ptr != NULL)
			{
				ptrs[ptrsCount++] = ptr;
			}
			cout << "ptr = ";
			cout << ptr;
			cout << "\n";
			break;
		}
		case 3:
		{
			cout << "Choose block of memory to free:\n";
			for (int i = 0; i < ptrsCount; i++)
			{
				cout << i;
				cout << " - ";
				cout << ptrs[i];
				cout << "\n";
			}
			cout << "> ";
			int n;
			cin >> n;
			if (n < ptrsCount)
			{
				alloc.mem_free(ptrs[n]);
				for (int i = n + 1; i < ptrsCount; i++)
				{
					ptrs[i - 1] = ptrs[i];
				}
				ptrsCount--;
			}
			break;
		}
		case 4:
		{
			cout << "Choose block of memory to reallocate:\n";
			for (int i = 0; i < ptrsCount; i++)
			{
				cout << i;
				cout << " - ";
				cout << ptrs[i];
				cout << "\n";
			}
			cout << "> ";
			int n;
			cin >> n;
			if (n < ptrsCount)
			{
				size_t size;
				cout << "Enter the size of memory to reallocate.\n";
				
					cout << "> ";
				cin >> size;
				void* ptr = alloc.mem_realloc(ptrs[n], size);
				if (ptr != NULL)
				{
					ptrs[n] = ptr;
				}
				cout << "ptr = ";
				cout << ptr;
				cout << "\n";
			}
			break;
		}
		}
		cin.get();
	}
	return 0;
}
