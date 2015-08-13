#include "gzHeap.h"

gzHeap::gzHeap(int maxHeapSize)
{
	items = vector<Node*>(maxHeapSize);
}

void gzHeap::add(Node* item)
{
	item->heapIndex = itemCount;
	items[itemCount] = item;
	sortUp(item);
	++itemCount;
}

void gzHeap::sortUp(Node* item)
{
	int parentIndex = (item->heapIndex - 1) / 2;

	bool working = true;
	while (working)
	{
		Node* parent = items[parentIndex];
		if (item->compareTo(parent) > 0)
		{
			swap(item, parent);
		}
		else
		{
			working = false;
		}

		parentIndex = (item->heapIndex - 1) / 2;
	}
}

void gzHeap::sortDown(Node* item)
{
	while (true)
	{
		int childIndexLeft = item->heapIndex * 2 + 1;
		int childIndexRight = item->heapIndex * 2 + 2;
		int swapIndex = 0;

		if (childIndexLeft < itemCount)
		{
			swapIndex = childIndexLeft;
			if (childIndexRight < itemCount)
			{
				if (items[childIndexLeft]->compareTo(items[childIndexRight]) < 0) {
					swapIndex = childIndexRight;
				}
			}

			if (item->compareTo(items[swapIndex]) < 0)
			{
				swap(item,items[swapIndex]);
			}
			else
			{
				return;
			}

		}
		else
		{
			return;
		}
	}
}

void gzHeap::swap(Node* itemA, Node* itemB)
{
	items[itemA->heapIndex] = itemB;
	items[itemB->heapIndex] = itemA;
	int itemAIndex = itemA->heapIndex;
	itemA->heapIndex = itemB->heapIndex;
	itemB->heapIndex = itemAIndex;
}

void gzHeap::updateItem(Node* item)
{
	sortUp(item);
}

Node* gzHeap::pop()
{
	Node* first = items[0];
	--itemCount;
	items[0] = items[itemCount];
	items[0]->heapIndex = 0;
	sortDown(items[0]);
	return first;
}

bool gzHeap::contains(Node* item)
{
	return item == items[item->heapIndex];
}

int gzHeap::getCount()
{
	return itemCount;
}
