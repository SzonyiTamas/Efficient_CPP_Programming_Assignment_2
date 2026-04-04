#pragma once

#include "stackNode.h"

template <typename T>
class Stack
{
public:

    Stack();
    ~Stack();

    Stack(const Stack& other);
    Stack& operator=(const Stack& other);

    Stack(Stack&& other) noexcept;
    Stack& operator=(Stack&& other) noexcept;

    bool empty() const;
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;

private:

    StackNode<T>* topNode{ nullptr };

    void clear();
    StackNode<T>* clone(const StackNode<T>* current) const;
};

#pragma region Rule of 5 implementation

template <typename T>
Stack<T>::Stack()
{
}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
Stack<T>::Stack(Stack&& other) noexcept
    : topNode(other.topNode)
{
    other.topNode = nullptr;
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
{
    if (this == &other)
    {
        return *this;
    }

    clear();
    topNode = clone(other.topNode);

    return *this;
}

template <typename T>
Stack<T>::Stack(const Stack& other)
    : topNode(clone(other.topNode))
{
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    clear();
    topNode = other.topNode;
    other.topNode = nullptr;

    return *this;
}

#pragma endregion

#pragma region Public interface

template <typename T>
bool Stack<T>::empty() const
{
    return topNode == nullptr;
}

template <typename T>
void Stack<T>::push(const T& value)
{
    StackNode<T>* newNode = new StackNode<T>(value);
    newNode->next = topNode;
    topNode = newNode;
}

template <typename T>
void Stack<T>::pop()
{
    if (topNode == nullptr)
    {
        return;
    }

    StackNode<T>* nodeToDelete = topNode;
    topNode = topNode->next;
    delete nodeToDelete;
}

template <typename T>
const T& Stack<T>::top() const
{
    return topNode->data;
}

template <typename T>
T& Stack<T>::top()
{
    return topNode->data;
}

#pragma endregion

#pragma region Private helpers

template <typename T>
void Stack<T>::clear()
{
    while (topNode != nullptr)
    {
        StackNode<T>* nodeToDelete = topNode;
        topNode = topNode->next;
        delete nodeToDelete;
    }
}

template <typename T>
StackNode<T>* Stack<T>::clone(const StackNode<T>* current) const
{
    if (current == nullptr)
    {
        return nullptr;
    }

    StackNode<T>* newHead = new StackNode<T>(current->data);
    StackNode<T>* newCurrent = newHead;
    const StackNode<T>* originalCurrent = current->next;

    while (originalCurrent != nullptr)
    {
        newCurrent->next = new StackNode<T>(originalCurrent->data);
        newCurrent = newCurrent->next;
        originalCurrent = originalCurrent->next;
    }

    return newHead;
}

#pragma endregion
