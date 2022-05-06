#pragma once
#include "stack.h"
#include "list.h"
template <class T>
class TTextNode
{
protected:
    T content;
    TTextNode *pNext, *pDown;
public:
    TextNode(TextNode* next = NULL, TextNode* down = NULL);
    TextNode* get_next() { return pNext; }
    TextNode* get_down() { return pDown; }

};
template <class T>
class TText
{
protected:
    TTextNode * pFirst;//корень дерева
    TTextNode * pCurrent;//текущее звено
    Stack <TTextNode> Path;//стек траектории
public:
    void go_first_node();// к первому звену
    void go_down_node();// к след. звену по  Down
    void go_next_node();// к след. звену по Next
    void go_prev_node();// к пред. звену
    T get_node();// доступ текущего звена
    T set_node(T tmp);//замена содержимого текущего звена
    void ins_down_node(T tmp);//вставка на нижний подуровень 
    void del_down_node();//удаление на нижний подуровень 
    void ins_next_node(T tmp);//вставка на тот же подуровень 
    void del_next_node();//удаление на тот же подуровень 
    void ins_down_section(T tmp);//вставка нового подуровня
    void del_down_section();//удаление нового подуровня
    void ins_next_section(T tmp);//вставка на том же подуровне
    void del_next_section();//удаление на том же подуровня
};