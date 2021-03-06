#pragma once
const int MaxStackSize = 2000;

template <class T>
class Stack
{
    T* pMem;
    int size;
    int top;
public:
    Stack();
    ~Stack();
    void add(T tmp);

    T get_top();
    T info_top();
    bool is_empty();
    bool is_full();
    void set_size(int s);
    int get_size();
};

template <class T>
Stack<T>::Stack()
{
    size = MaxStackSize;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    pMem = new T[size];
}
template <class T>
Stack<T>:: ~Stack()
{
    delete[] pMem;
}
template <class T>
void Stack<T>::add(T tmp)
{
    if (top + 1 >= size)
        throw size;
    pMem[++top] = tmp;
}
template <class T>
T Stack<T>::get_top()
{
    if (is_empty() == true)
    {
        throw 0;
    }
    return (pMem[top--]);
}
template <class T>
T Stack<T>::info_top()
{
    if (is_empty() == true)
    {
        throw 0;
    }
    return (pMem[top]);
}
template <class T>
bool Stack<T>::is_empty()
{
    if (top == -1)
        return true;
    else {
        return false;
    }
}
template <class T>
bool Stack<T>::is_full()
{
    if (top == size - 1) {
        return true;
    }
    else {
        return false;
    }
}
template <class T>
void Stack<T>::set_size(int s)
{
    size = s;
    top = -1;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    delete[] pMem;
    pMem = new T[size];
}
template <class T>
int Stack<T>::get_size()
{
    return size;
}