#pragma once
#include "stack.h"
#include "list.h"
template <class T>
class TText;
template <class T>

class TTextNode
{
protected:
    T content;
    TTextNode* pNext, * pDown;
    friend TText<T>;
public:
    TTextNode(T con, TTextNode* next = NULL, TTextNode* down = NULL) : pNext(next), pDown(down), content(con) {}
    T get_content() { return content; }
    void set_content(T tmp) { content = tmp; }
};
template <class T>
class TText
{
protected:
    TTextNode<T>* pFirst;//tree root
    TTextNode<T>* pCurrent;//current node
    Stack <TTextNode<T>*> Path;//trajectory stack
public:
    bool set_first_node(T tmp);
    bool go_first_node();// to the first node
    bool go_down_node();// to the next node Down
    bool go_next_node();// to the next node  Next
    bool go_prev_node();// to prev. link
    T get_node();// current node access
    bool set_node(T tmp);//replacing the contents of the current node
    bool ins_down_node(T tmp);//insert ro lower sublevel
    bool del_down_node();//delete from lower sublevel
    bool ins_next_node(T tmp);//insert to same sublevel
    bool del_next_node();//delete from same sublevel
    bool ins_down_section(T tmp);// insert new lower sublevel
    bool del_down_section();//delete lower sublevel
    bool ins_next_section(T tmp);//insert new same sublevel
    bool del_next_section();//delete same sublevel
};
template <class T>
bool TText<T>::set_first_node(T tmp)
{
    pFirst = new TTextNode<T>(tmp, NULL, NULL);
    pCurrent = pFirst;
    return true;
}
template <class T>
bool TText<T>::go_first_node()//
{
    while (!Path.is_empty())
        Path.get_top();
    pCurrent = pFirst;
    if (pCurrent != NULL)
        return true;
    return false;
}
template <class T>
bool TText<T>::go_down_node()//
{
    if (pCurrent != NULL)
        if (pCurrent->pDown = NULL)
        {
            Path.add(pCurrent);
            pCurrent = pCurrent->pDown;
            return true;
        }
    return false;
}
template <class T>
bool TText<T>::go_next_node()//
{
    if (pCurrent != NULL)
        if (pCurrent->pNext != NULL)
        {
            Path.add(pCurrent);
            pCurrent = pCurrent->pNext;
            return true;
        }
    return false;
}
template <class T>
bool TText<T>::go_prev_node()//
{
    if (Path.is_empty())
        return false;
    pCurrent = Path.get_top();
    return true;
}
template <class T>
T TText<T>::get_node()//
{
    if (pCurrent == NULL)
    {
        Token t;
        return t;
    }
    return  pCurrent->get_content();
}
template <class T>
bool TText<T>::set_node(T tmp)//
{
    if (pCurrent == NULL)
        return NULL;
    pCurrent->set_content(tmp);
    return true;
}
template <class T>
bool TText<T>::ins_down_node(T tmp)//
{
    if (pCurrent == NULL)
        return false;
    TTextNode<T>* pd = pCurrent->pDown;
    TTextNode<T>* pl = new TTextNode<T>(tmp, pd, NULL);
    pCurrent->pDown = pl;
    return true;
}
template <class T>
bool TText<T>::ins_down_section(T tmp)//
{
    if (pCurrent == NULL)
        return false;
    TTextNode<T>* pd = pCurrent->pDown;
    TTextNode<T>* pl = new TTextNode<T>(tmp, NULL, pd);
    pCurrent->pDown = pl;
    return true;
}
template <class T>
bool TText<T>::ins_next_node(T tmp)//
{
    if (pCurrent == NULL)
        return false;
    TTextNode<T>* pd = pCurrent->pNext;
    TTextNode<T>* pl = new TTextNode<T>(tmp, pd, NULL);
    pCurrent->pNext = pl;
    return true;
}
template <class T>
bool TText<T>::ins_next_section(T tmp)//
{
    if (pCurrent == NULL)
        return false;
    TTextNode<T>* pd = pCurrent->pNext;
    TTextNode<T>* pl = new TTextNode<T>(tmp, NULL, pd);
    pCurrent->pNext = pl;
    return true;
}
template <class T>
bool TText<T>::del_down_node()//
{
    if (pCurrent == NULL)
        return false
    else if (pCurrent->pDown != NULL)
    {
        TTextNode<T>* pd = pCurrent->pDown;
        TTextNode<T>* pl = pd->pNext;
        if (pd->pDown == NULL)
        {
            pCurrent->pDown = pl;
            return true;
        }
    }
    return false;
}
template <class T>
bool TText<T>::del_down_section()
{
    if (pCurrent == NULL)
        return false
    else if (pCurrent->pDown != NULL)
    {
        TTextNode<T>* pd = pCurrent->pDown;
        TTextNode<T>* pl = pd->pNext;
        pCurrent->pDown = pl;
        return true;
    }
    return false;
}
template <class T>
bool TText<T>::del_next_node()//
{
    if (pCurrent == NULL)
        return false
    else if (pCurrent->pNext != NULL)
    {
        TTextNode<T>* pd = pCurrent->pNext;
        TTextNode<T>* pl = pd->pNext;
        if (pd->pDown == NULL)
        {
            pCurrent->pNext = pl;
            return true;
        }
    }
    return false;
}
template <class T>
bool TText<T>::del_next_section()//
{
    if (pCurrent == NULL)
        return false
    else if (pCurrent->pNext != NULL)
    {
        TTextNode<T>* pd = pCurrent->pNext;
        TTextNode<T>* pl = pd->pNext;
        pCurrent->pNext = pl;
        return true;
    }
    return false;
}