#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <cstdio>
#include <cstdlib>
#include <cstring>

template <typename T>
struct ListNode {
    T data;
    ListNode<T>* next;
    ListNode<T>* prev;

    ListNode() : next(nullptr), prev(nullptr) {}
    ListNode(const T& d) : data(d), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~LinkedList() {
        clear();
    }

    void clear() {
        ListNode<T>* current = head;
        while (current != nullptr) {
            ListNode<T>* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    int size() const { return count; }

    bool isEmpty() const { return count == 0; }

    ListNode<T>* getHead() const { return head; }

    ListNode<T>* getTail() const { return tail; }

    void append(const T& data) {
        ListNode<T>* node = new ListNode<T>(data);
        if (tail == nullptr) {
            head = tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        count++;
    }

    bool removeAt(int index) {
        if (index < 0 || index >= count) return false;
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            head = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            tail = current->prev;
        }
        delete current;
        count--;
        return true;
    }

    bool removeNode(ListNode<T>* node) {
        if (node == nullptr) return false;
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        } else {
            head = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        } else {
            tail = node->prev;
        }
        delete node;
        count--;
        return true;
    }

    T* getAt(int index) {
        if (index < 0 || index >= count) return nullptr;
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }

    int indexOf(bool (*predicate)(const T&)) {
        ListNode<T>* current = head;
        int index = 0;
        while (current != nullptr) {
            if (predicate(current->data)) return index;
            current = current->next;
            index++;
        }
        return -1;
    }

    ListNode<T>* find(bool (*predicate)(const T&)) {
        ListNode<T>* current = head;
        while (current != nullptr) {
            if (predicate(current->data)) return current;
            current = current->next;
        }
        return nullptr;
    }

    void sort(int (*compare)(const T&, const T&)) {
        if (count <= 1) return;
        for (ListNode<T>* i = head; i != nullptr; i = i->next) {
            for (ListNode<T>* j = i->next; j != nullptr; j = j->next) {
                if (compare(i->data, j->data) > 0) {
                    T temp = i->data;
                    i->data = j->data;
                    j->data = temp;
                }
            }
        }
    }
};

#endif
