#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/*
 * 程序功能: 汽车租赁管理系统
 * 作者: RayChen
 * 日期: 2026-07-13
 * 文件作用: 提供通用双向链表模板类，支持增删查改排序等动态链表操作
 */

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
    /*
     * 函数作用: 构造空链表
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    /*
     * 函数作用: 析构链表，释放所有节点内存
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
    ~LinkedList() {
        clear();
    }

    /*
     * 函数作用: 清空链表，释放所有节点内存
     * 入参: 无
     * 返回值: 无
     * 异常提示: 无
     */
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

    /*
     * 函数作用: 获取链表当前节点数量
     * 入参: 无
     * 返回值: 链表中的节点数量
     * 异常提示: 无
     */
    int size() const { return count; }

    /*
     * 函数作用: 判断链表是否为空
     * 入参: 无
     * 返回值: 为空返回true，否则返回false
     * 异常提示: 无
     */
    bool isEmpty() const { return count == 0; }

    /*
     * 函数作用: 获取链表头节点指针
     * 入参: 无
     * 返回值: 头节点指针，空链表返回nullptr
     * 异常提示: 无
     */
    ListNode<T>* getHead() const { return head; }

    /*
     * 函数作用: 获取链表尾节点指针
     * 入参: 无
     * 返回值: 尾节点指针，空链表返回nullptr
     * 异常提示: 无
     */
    ListNode<T>* getTail() const { return tail; }

    /*
     * 函数作用: 动态链表操作 - 在链表尾部追加新节点
     * 入参: data - 待追加的数据引用
     * 返回值: 无
     * 异常提示: 无
     */
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

    /*
     * 函数作用: 动态链表操作 - 按索引删除节点
     * 入参: index - 待删除节点的索引（从0开始）
     * 返回值: 删除成功返回true，索引越界返回false
     * 异常提示: 无
     */
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

    /*
     * 函数作用: 动态链表操作 - 按节点指针删除节点
     * 入参: node - 待删除节点的指针
     * 返回值: 删除成功返回true，node为空返回false
     * 异常提示: 无
     */
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

    /*
     * 函数作用: 按索引获取节点数据的指针
     * 入参: index - 节点索引（从0开始）
     * 返回值: 数据指针，越界返回nullptr
     * 异常提示: 无
     */
    T* getAt(int index) {
        if (index < 0 || index >= count) return nullptr;
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }

    /*
     * 函数作用: 动态链表操作 - 按条件查找节点索引
     * 入参: predicate - 判断条件的函数指针
     * 返回值: 第一个满足条件的节点索引，未找到返回-1
     * 异常提示: 无
     */
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

    /*
     * 函数作用: 动态链表操作 - 按条件查找节点指针
     * 入参: predicate - 判断条件的函数指针
     * 返回值: 第一个满足条件的节点指针，未找到返回nullptr
     * 异常提示: 无
     */
    ListNode<T>* find(bool (*predicate)(const T&)) {
        ListNode<T>* current = head;
        while (current != nullptr) {
            if (predicate(current->data)) return current;
            current = current->next;
        }
        return nullptr;
    }

    /*
     * 函数作用: 动态链表操作 - 对链表进行冒泡排序
     * 入参: compare - 比较函数指针，返回值>0表示需要交换
     * 返回值: 无
     * 异常提示: 无
     */
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
