
   
#ifndef __HASHTABLELIST_H__
#define __HASHTABLELIST_H__

#include "table.h"
#include "table_string.h"
#include <string>
#include <vector>
#include "list.h"



template <class T>
class HashTableList : public Table<T>
{
private:
    int size;
    int curr_index;
    int curr_pos_num;
    std::vector<List<TableString<T>*>*> table;
    ListIterator<TableString<T>*> curr_pos;

    unsigned int Hash(const std::string& key);

public:
    HashTableList(int _size = DEFAULT_SIZE)
        :  size(_size), curr_index(0), curr_pos_num(0),
        table(_size, nullptr), curr_pos()
    {
        for(int i = 0; i < _size; i++) {
            table[i] = new List<TableString<T>*>;
        }
        curr_pos = table[0]->begin();
    }

    ~HashTableList() = default;

    inline int get_size()
    {
        return size;
    }

    TableBody<T>* find(const std::string& key);
    TableString<T>* find_str(const std::string& key);
    bool insert(const std::string& key, TableBody<T>& data);
    bool erase(const std::string& key);
    bool is_full() const;
    bool reset();
    bool is_tab_ended() const;
    bool go_next();
    TableString<T>* get_value();
    bool set_current_pos(int pos);
    int get_current_pos() const ;
    int hash_string(const std::string& key);
};

#endif