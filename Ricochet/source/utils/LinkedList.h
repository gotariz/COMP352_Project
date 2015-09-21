#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "dependencies.h"

template<class T>
struct Node
{
    Node<T>* prev = nullptr;
    Node<T>* next = nullptr;

    T data;
};

template<class T>
class LinkedList
{
    public:
        LinkedList(){}
        virtual ~LinkedList(){}

    protected:
        Node<T>* root = nullptr;
        Node<T>* last = nullptr;

        int size = 0;
    public:
    // implementations
        int getSize()
        {
            return size;
        }

        Node<T>* add(T data)
        {
            // add a new node to the end of the list
            Node<T>* node = new Node<T>;
            node->data = data;
            node->prev = last;
            node->next = nullptr;

            if (last)
            {
                last->next = node;
                last = node;
            }

            if (!root)
            {
                root = node;
                last = node;
            }

            ++size;
            return node;
        }

        Node<T>* insertBefore(Node<T>* n, T data)
        {
            if (!n) return nullptr;
            Node<T>* previous = n->prev;

            Node<T>* node = new Node<T>;
            node->data = data;
            node->prev = previous;
            node->next = n;

            if (previous)
                previous->next = node;
            n->prev = node;

            if (n == root) root = node;

            ++size;
            return node;
        }

        Node<T>* insertAfter(Node<T>* n, T data)
        {
            if (!n) return nullptr;

            Node<T>* next = n->next;

            Node<T>* node = new Node<T>;
            node->data = data;
            node->prev = n;
            node->next = next;

            if (next)
                next->prev = node;
            n->next = node;

            if (n == last)  last = node;

            ++size;

            return node;
        }

        void remove(Node<T>* n)
        {
            if (!n)  return;

            if (n == root)  root = n->next;
            if (n == last)  last = n->prev;

            if (n->prev)    n->prev->next = n->next;
            if (n->next)    n->next->prev = n->prev;

            delete n;
            --size;
        }

        Node<T>* getRoot()
        {
            return root;
        }

        Node<T>* getLast()
        {
            return last;
        }

        void clear()
        {
            Node<T>* n = root;
            while(n)
            {
                remove(n);
                n = getRoot();
            }
        }

};

#endif // LINKEDLIST_H
