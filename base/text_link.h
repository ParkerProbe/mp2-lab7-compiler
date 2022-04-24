#pragma once
template <class T>
struct TextNode
{
    T key = T();
    TextNode** pNext = nullptr;
};
template <class T>
class TextLink
{
    int curr_pos;
    TextNode<T>* root;
    TextNode<T>* current;
    Stack<TextNode<T>*> st;
    TextLink(TextNode* _root = nullptr) :root(_root)
    {}
};