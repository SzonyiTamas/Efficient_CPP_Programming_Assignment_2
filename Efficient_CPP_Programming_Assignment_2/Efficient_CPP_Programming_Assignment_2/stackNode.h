#pragma once

template <typename T>
struct StackNode
{
    T data;
    StackNode* next{ nullptr };

    StackNode(const T& data);
};

template <typename T>
StackNode<T>::StackNode(const T& data)
    : data(data)
{
}