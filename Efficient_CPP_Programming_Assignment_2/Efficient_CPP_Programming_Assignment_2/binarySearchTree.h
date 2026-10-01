#pragma once
#include "node.h"
#include "stack.h"

#include <stdexcept>
#include <iterator>
#include <ostream>
#include <cstddef>

template <typename Key, typename Value>
class BinarySearchTree
{
public:

    class Iterator
    {
    public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = value_type*;
        using reference = value_type&;

        Iterator(Node<Key, Value>* root);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

        Iterator& operator++();
        Iterator operator++(int);

        reference operator*();
        const value_type& operator*() const;

        pointer operator->();
        const value_type* operator->() const;

    private:

        Node<Key, Value>* current{ nullptr };
        Stack<Node<Key, Value>*> path;

        void pushLeftBranch(Node<Key, Value>* node);
        void setCurrentFromPath();
    };

    class ConstIterator
    {
    public:

        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;

        ConstIterator(const Node<Key, Value>* root);

        bool operator==(const ConstIterator& other) const;
        bool operator!=(const ConstIterator& other) const;

        ConstIterator& operator++();
        ConstIterator operator++(int);

        reference operator*() const;
        pointer operator->() const;

    private:

        const Node<Key, Value>* current{ nullptr };
        Stack<const Node<Key, Value>*> path;

        void pushLeftBranch(const Node<Key, Value>* node);
        void setCurrentFromPath();
    };

    BinarySearchTree() = default;
    ~BinarySearchTree();

    BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);

    BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    Value& operator[](const Key& key);
    const Value& operator[](const Key& key) const;

    bool empty() const;
    void clear();
    bool insert(const Key& key, const Value& value);
    bool remove(const Key& key);
    bool contains(const Key& key) const;

    Iterator begin();
    Iterator end();

    ConstIterator begin() const;
    ConstIterator end() const;

private:

    Node<Key, Value>* root{ nullptr };

    void clear(Node<Key, Value>* current);
    Node<Key, Value>* findNode(Node<Key, Value>* current, const Key& key) const;
    Node<Key, Value>*& findNodeReference(Node<Key, Value>*& current, const Key& key);
    bool insert(Node<Key, Value>*& current, const Key& key, const Value& value);
    bool remove(Node<Key, Value>*& current, const Key& key);
    Node<Key, Value>*& findMinNodeReference(Node<Key, Value>*& current);
    Node<Key, Value>* clone(const Node<Key, Value>* current) const;
};

#pragma region ConstIterator implementation

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::ConstIterator::ConstIterator(const Node<Key, Value>* root)
{
    pushLeftBranch(root);
    setCurrentFromPath();
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator
BinarySearchTree<Key, Value>::ConstIterator::operator++(int)
{
    ConstIterator temp{ *this };
    ++(*this);
    return temp;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator&
BinarySearchTree<Key, Value>::ConstIterator::operator++()
{
    if (current == nullptr)
    {
        return *this;
    }

    if (current->right != nullptr)
    {
        pushLeftBranch(current->right);
    }

    setCurrentFromPath();
    return *this;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator::reference
BinarySearchTree<Key, Value>::ConstIterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing end iterator");
    }

    return current->data;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator::pointer
BinarySearchTree<Key, Value>::ConstIterator::operator->() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing end iterator");
    }

    return &current->data;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator==(const ConstIterator& other) const
{
    return current == other.current;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::ConstIterator::operator!=(const ConstIterator& other) const
{
    return !(*this == other);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::ConstIterator::setCurrentFromPath()
{
    if (path.empty())
    {
        current = nullptr;
    }
    else
    {
        current = path.top();
        path.pop();
    }
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::ConstIterator::pushLeftBranch(const Node<Key, Value>* node)
{
    while (node != nullptr)
    {
        path.push(node);
        node = node->left;
    }
}

#pragma endregion

#pragma region Iterator implementation

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::Iterator::Iterator(Node<Key, Value>* root)
{
    pushLeftBranch(root);
    setCurrentFromPath();
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator
BinarySearchTree<Key, Value>::Iterator::operator++(int)
{
    Iterator temp{ *this };
    ++(*this);
    return temp;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator&
BinarySearchTree<Key, Value>::Iterator::operator++()
{
    if (current == nullptr)
    {
        return *this;
    }

    if (current->right != nullptr)
    {
        pushLeftBranch(current->right);
    }

    setCurrentFromPath();
    return *this;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator::reference
BinarySearchTree<Key, Value>::Iterator::operator*()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing end iterator");
    }

    return current->data;
}

template <typename Key, typename Value>
const typename BinarySearchTree<Key, Value>::Iterator::value_type&
BinarySearchTree<Key, Value>::Iterator::operator*() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing end iterator");
    }

    return current->data;
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator::pointer
BinarySearchTree<Key, Value>::Iterator::operator->()
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing end iterator");
    }

    return &current->data;
}

template <typename Key, typename Value>
const typename BinarySearchTree<Key, Value>::Iterator::value_type*
BinarySearchTree<Key, Value>::Iterator::operator->() const
{
    if (current == nullptr)
    {
        throw std::out_of_range("Dereferencing end iterator");
    }

    return &current->data;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator==(const Iterator& other) const
{
    return current == other.current;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::Iterator::setCurrentFromPath()
{
    if (path.empty())
    {
        current = nullptr;
    }
    else
    {
        current = path.top();
        path.pop();
    }
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::Iterator::pushLeftBranch(Node<Key, Value>* node)
{
    while (node != nullptr)
    {
        path.push(node);
        node = node->left;
    }
}

#pragma endregion

#pragma region Rule of 5 implementation

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::operator=(const BinarySearchTree& other)
{
    if (this == &other)
    {
        return *this;
    }

    clear();
    root = clone(other.root);

    return *this;
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(const BinarySearchTree& other)
    : root(clone(other.root))
{
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::operator=(BinarySearchTree&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    clear();
    root = other.root;
    other.root = nullptr;

    return *this;
}

template <typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree(BinarySearchTree&& other) noexcept
    : root(other.root)
{
    other.root = nullptr;
}

#pragma endregion

#pragma region Stream output

template <typename Key, typename Value>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<Key, Value>& tree)
{
    os << "[";

    bool first = true;

    for (const auto& elem : tree)
    {
        if (!first)
        {
            os << ", ";
        }

        os << "(" << elem.first << ": " << elem.second << ")";
        first = false;
    }

    os << "]";

    return os;
}

#pragma endregion

#pragma region Iterator access

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator
BinarySearchTree<Key, Value>::begin() const
{
    return ConstIterator(root);
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::ConstIterator
BinarySearchTree<Key, Value>::end() const
{
    return ConstIterator(nullptr);
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator
BinarySearchTree<Key, Value>::begin()
{
    return Iterator(root);
}

template <typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Iterator
BinarySearchTree<Key, Value>::end()
{
    return Iterator(nullptr);
}

#pragma endregion

#pragma region Public interface

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::remove(const Key& key)
{
    return remove(root, key);
}

template <typename Key, typename Value>
const Value& BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value>* node = findNode(root, key);

    if (node == nullptr)
    {
        throw std::out_of_range("Key not found in BinarySearchTree");
    }

    return node->data.second;
}

template <typename Key, typename Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value>*& node = findNodeReference(root, key);

    if (node == nullptr)
    {
        node = new Node<Key, Value>(key, Value());
    }

    return node->data.second;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::contains(const Key& key) const
{
    return findNode(root, key) != nullptr;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::insert(const Key& key, const Value& value)
{
    return insert(root, key, value);
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root == nullptr;
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    clear(root);
    root = nullptr;
}

#pragma endregion

#pragma region Private helpers implementation

template <typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::clone(const Node<Key, Value>* current) const
{
    if (current == nullptr)
    {
        return nullptr;
    }

    Node<Key, Value>* newNode = new Node<Key, Value>(current->data.first, current->data.second);
    newNode->left = clone(current->left);
    newNode->right = clone(current->right);

    return newNode;
}

template <typename Key, typename Value>
Node<Key, Value>*& BinarySearchTree<Key, Value>::findMinNodeReference(Node<Key, Value>*& current)
{
    if (current->left == nullptr)
    {
        return current;
    }

    return findMinNodeReference(current->left);
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::remove(Node<Key, Value>*& current, const Key& key)
{
    if (current == nullptr)
    {
        return false;
    }

    if (key < current->data.first)
    {
        return remove(current->left, key);
    }

    if (current->data.first < key)
    {
        return remove(current->right, key);
    }

    if (current->left == nullptr && current->right == nullptr)
    {
        delete current;
        current = nullptr;
        return true;
    }

    if (current->left == nullptr)
    {
        Node<Key, Value>* nodeToDelete = current;
        current = current->right;
        delete nodeToDelete;
        return true;
    }

    if (current->right == nullptr)
    {
        Node<Key, Value>* nodeToDelete = current;
        current = current->left;
        delete nodeToDelete;
        return true;
    }

    Node<Key, Value>*& successor = findMinNodeReference(current->right);
    Node<Key, Value>* nodeToReplace = current;

    if (successor == current->right)
    {
        current = successor;
        current->left = nodeToReplace->left;
    }
    else
    {
        Node<Key, Value>* detachedSuccessor = successor;
        successor = successor->right;

        detachedSuccessor->left = nodeToReplace->left;
        detachedSuccessor->right = nodeToReplace->right;
        current = detachedSuccessor;
    }

    delete nodeToReplace;
    return true;
}

template <typename Key, typename Value>
bool BinarySearchTree<Key, Value>::insert(Node<Key, Value>*& current, const Key& key, const Value& value)
{
    if (current == nullptr)
    {
        current = new Node<Key, Value>(key, value);
        return true;
    }

    if (key == current->data.first)
    {
        return false;
    }

    if (key < current->data.first)
    {
        return insert(current->left, key, value);
    }

    return insert(current->right, key, value);
}

template <typename Key, typename Value>
Node<Key, Value>*& BinarySearchTree<Key, Value>::findNodeReference(Node<Key, Value>*& current, const Key& key)
{
    if (current == nullptr)
    {
        return current;
    }

    if (key == current->data.first)
    {
        return current;
    }

    if (key < current->data.first)
    {
        return findNodeReference(current->left, key);
    }

    return findNodeReference(current->right, key);
}

//Kicsit redundáns, de ebben az esetben a két függvény eltérõ felelõssége (nem módosítható pointer vs modosítható pointer referencia) miatt a külön implementációt jobbnak éreztem 
template <typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::findNode(Node<Key, Value>* current, const Key& key) const
{
    if (current == nullptr)
    {
        return nullptr;
    }

    if (key == current->data.first)
    {
        return current;
    }

    if (key < current->data.first)
    {
        return findNode(current->left, key);
    }

    return findNode(current->right, key);
}

template <typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear(Node<Key, Value>* current)
{
    if (current == nullptr)
    {
        return;
    }

    clear(current->left);
    clear(current->right);
    delete current;
}

#pragma endregion

