#pragma once

#include "Vector2.h"
#include <vector>

using namespace std;

class Node
{
	public:
		int x = 0;
		int y = 0;

		int h = 0;	// heuristic (distance to destination)
		int g = 0;	// movement cost
		int f = 0;

		bool solid = false;
		bool closed = false;
		Node* parent = nullptr; // a node to get to this one
		vector<Node*> neighbours;

		int getF()
		{
			return g + h;
		}

		// heap members
		int heapIndex = 0;
		int compareTo(Node* other){
			if (getF() < other->getF())
				return 1;
			else if (getF() > other->getF())
				return -1;
			else
			{
				if (h < other->h)
					return 1;
				else if (h > other->h)
					return -1;
				else 
					return 0;
			}
		}
};

class gzHeap
{
	public:
		gzHeap(int maxHeapSize = 16);

		Node* pop();
		bool contains(Node* item);
		int getCount();

		void add(Node* item);
		void sortUp(Node* item);
		void sortDown(Node* item);
		void swap(Node* itemA, Node* itemB);
		void updateItem(Node* item);


	protected:
		vector<Node*> items;
		int itemCount = 0;
		int maxSize = 0;
};

