#pragma once

#include <ostream>
#include <string>

using std::string;

template <class T>
class TableString;

template <class T>
class Table;

template <class T>
class HashTableList;

template <class T>
struct TableBody
{
    T* data;
    TableBody()
        :  data(nullptr)
    {}
    TableBody(const T& data_)
    {
        data = new T(data_);
    }

    ~TableBody() = default;
};

template <class T>
class TableString
{
private:
    string key;
    TableBody<T> body; 
public:
    TableString()
        :key("I"), body()
    {}

    TableString(string key_, TableBody<T>& body_)
        : key(key_), body(body_)
    {
        const int k_MAX_NAME = 16;
        //const int k_MAX_POLY_STRING = 102;
        if (key_.size() > k_MAX_NAME)
            throw EqException(error_codes::k_OVERFLOW);
        for (int i = 0; i < key.size(); i++)
        {

            char c = key[i];
            if (c == 'I')
                throw EqException(error_codes::k_USING_RESERVED_NAME);
            if (c == 'd' && (key[i + 1] == 'x' || key[i + 1] == 'y' || key[i + 1] == 'z'))
                throw EqException(error_codes::k_USING_RESERVED_NAME);
            if (c >= '9' + 1 && c <= '9' + 7)
                throw EqException(error_codes::k_USING_PUNCTUATION_MARKS);
        }
    }

    TableString(const TableString& other) = default; 
    ~TableString() = default;

    TableString& operator=(const TableString& other) = default;

    bool operator==(const TableString& other)
    {
        return key == other.key;
    }
    bool operator!=(const TableString& other)
    {
        return key != other.key;
    }

    bool operator<(const TableString& other)
    {
        return key < other.key;
    }

    bool operator>(const TableString& other)
    {
        return key > other.key;
    }

    inline string get_key() const
    {
        return key;
    }

    inline T* get_data() const
    {
        return body.data;
    }

    void print(std::ostream& os) const
    {
        os << key << " " << body.poly_string << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os, const TableString* ts);

    friend class Table<T>;
    friend class HashTableList<T>;
};

