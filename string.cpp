#include <iostream>
#include <cstring>

class String {
private:
    size_t sz = 0;
    size_t mem_sz = 1;
    char* str;


    void swap(String& s) {
        std::swap(sz, s.sz);
        std::swap(mem_sz, s.mem_sz);
        std::swap(str, s.str);
    }

    bool check(const String& s1, size_t sz) const {
        for (size_t i = 0; i < sz; ++i)
            if (str[i] != s1.str[i])
                return false;
        return true;
    }

    int get_mem_sz(int sz) const {
        int new_sz = 1;
        while (new_sz < sz)
            new_sz *= 2;
        return new_sz;
    }

    size_t temp_find(const String& substring, size_t start, size_t finish, size_t step) const {
        for (size_t i = start; i != finish; i += step){
            String new_str = (*this).substr(i, substring.sz);
            if (new_str.check(substring, substring.sz))
                return i;
        }
        return sz;
    }

public:
    String(): str(new char[mem_sz]) {}
    String(char symbol) : String(1, symbol) {}

    String(int size, char symbol) : sz(size), mem_sz(get_mem_sz(size)), str(new char[mem_sz]) {
        memset(str, symbol, size);
    }


    String(const char* ss) : sz(strlen(ss)), mem_sz(get_mem_sz(sz)), str(new char[mem_sz]) {
        memcpy(str, ss, sz);
    }

    String(const String& ss) : sz(ss.sz), mem_sz(ss.mem_sz), str(new char[mem_sz]) {
        memcpy(str, ss.str, mem_sz);
    }


    String& operator=(const String& ss) & {
        String cpy(ss);
        swap(cpy);
        return *this;
    }


    char operator[](int index) const {
        return str[index];
    }

    char& operator[](int index) {
        return str[index];
    }


    String& operator+=(const String& ss) {
        if (mem_sz >= ss.sz + sz){
            memcpy(str + sz, ss.str, ss.sz);
            sz += ss.sz;
            return *this;
        }
        mem_sz = get_mem_sz(ss.sz + sz);
        char* new_str = new char[mem_sz];
        memcpy(new_str, str, sz);
        memcpy(new_str + sz, ss.str, ss.sz);
        delete[] str;
        sz += ss.sz;
        str = new char[mem_sz];
        memcpy(str, new_str, mem_sz);
        delete[] new_str;
        return *this;
    }

    void push_back(char symbol) {
        if (sz + 1 >= mem_sz){
            char* tmp_str = new char[sz];
            memcpy(tmp_str, str, sz);
            delete[] str;
            mem_sz *= 2;
            str = new char[mem_sz];
            memcpy(str, tmp_str, sz);
            delete[] tmp_str;
        }
        str[sz++] = symbol;
    }


    size_t find(const String& substring) const {
        return temp_find(substring, 0, sz - substring.sz, 1);
    }

    size_t rfind(const String& substring) const {
        return temp_find(substring, sz - substring.sz, 0, -1);
    }

    String substr(int start, int count) const {
        String new_str;
        new_str.mem_sz = get_mem_sz(count);
        delete[] new_str.str;
        new_str.str = new char[new_str.mem_sz];
        new_str.sz = count;
        memcpy(new_str.str, str + start, count);
        return new_str;
    }


    void pop_back() {
        --sz;
    }

    friend std::ostream& operator<<(std::ostream& out, const String& ss) {
        for (size_t i = 0; i < ss.sz; ++i)
            out << ss.str[i];
        return out;
    }

    friend std::istream& operator>>(std::istream& in, String& ss) {
        ss.clear();
        char symbol;
        while (true){
            symbol = in.get();
            if (!isspace(symbol)){
                ss.push_back(symbol);
                break;
            }
        }
        while (true){
            symbol = in.get();
            if (isspace(symbol) || symbol == EOF)
                break;
            ss.push_back(symbol);
        }
        return in;
    }

    char back() const {
        return str[sz - 1];
    }

    char& back() {
        return str[sz - 1];
    }

    char front() const {
        return str[0];
    }

    char& front() {
        return str[0];
    }

    size_t length() const {
        return sz;
    }

    bool empty() const {
        return sz == 0;
    }

    void clear() {
        sz = 0;
    }

    ~String() {
        delete[] str;
    }

    friend bool operator==(const String&, const String&);
};

String operator+(const String& s1, const String& s2) {
    String new_str(s1);
    new_str += s2;
    return new_str;
}

bool operator==(const String& s1, const String& s2) {
    if (s1.sz != s2.sz)
        return false;
    for (size_t i = 0; i < s1.sz; ++i)
        if (s1.str[i] != s2.str[i])
            return false;
    return true;
}




