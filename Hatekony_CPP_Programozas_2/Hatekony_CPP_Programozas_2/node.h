#pragma once

template <typename Key, typename Value>
struct Node
{
    Key key;
    Value value;
    Node* left{ nullptr };
    Node* right{ nullptr };

    Node(const Key& key, const Value& value);
};

template <typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value)
    : key(key)
    , value(value)
{
}

