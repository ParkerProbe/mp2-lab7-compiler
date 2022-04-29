#pragma once
#include "stack.h"
#include "list.h"
template <class T>
class TTextNode
{
protected:
    T content;
    TextNode *pNext, *pDown;
public:
    TextNode(T s = NULL, TextNode* next = NULL, TextNode* down = NULL);
    TextNode* get_next() { return pNext; }
    TextNode* get_down() { return pDown; }

};
template <class T>
class TText
{
protected:
    TTextNode * pFirst;//������ ������
    TTextNode * pCurrent;//������� �����
    TStack <TTextNode> Path;//���� ����������
public:
    void go_first_node();// � ������� �����
    void go_down_node();// � ����. ����� ��  Down
    void go_next_node();// � ����. ����� �� Next
    void go_prev_node();// � ����. �����
    T get_node();// ������ �������� �����
    T set_node(T tmp);//������ ����������� �������� �����
    void ins_down_node(T tmp);//������� �� ������ ���������� 
    void del_down_node(T tmp);//�������� �� ������ ���������� 
    void ins_next_node(T tmp);//������� �� ��� �� ���������� 
    void del_next_node(T tmp);//�������� �� ��� �� ���������� 
    void ins_down_section(T tmp);//������� ������ ���������
    void del_down_section(T tmp);//�������� ������ ���������
    void ins_next_section(T tmp);//������� �� ��� �� ���������
    void del_next_section(T tmp);//�������� �� ��� �� ���������
};