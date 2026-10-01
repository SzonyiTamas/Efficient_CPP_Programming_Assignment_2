#pragma once

#include <utility>

template <typename Key, typename Value>
struct Node
{
    std::pair<const Key, Value> data;
    Node* left{ nullptr };
    Node* right{ nullptr };

    Node(const Key& key, const Value& value);
};

template <typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value)
    : data(key, value)
{
}

