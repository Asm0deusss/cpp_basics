#pragma once
#include <iostream>
#include <memory>

struct StringRef {
    StringRef(const char* s, const size_t str_size);
    ~StringRef();
    size_t size = 0;
    char* str_ptr = nullptr;
};

class ProxiObg {
public:
    ProxiObg(char& s, std::shared_ptr<StringRef>& ptr) : sym_ptr_(&s), parent_ptr_(&ptr){};
    char& operator=(const char s);
    bool operator==(const char s) const;
    bool operator!=(const char s) const;
    operator char();

private:
    char* sym_ptr_;
    std::shared_ptr<StringRef>* parent_ptr_;
};

class CowString {
public:
    class IterConst {
    public:
        IterConst(const std::shared_ptr<StringRef>* ptr, size_t pos);
        bool operator!=(const IterConst& other) const;
        char& operator*() const;
        IterConst& operator++();

    private:
        const std::shared_ptr<StringRef>* begin_ptr_;
        size_t cur_size_ = 0;
    };

    class IterNoConst {
    public:
        IterNoConst(char* pointer, std::shared_ptr<StringRef>& ptr) : pos_(pointer - ptr->str_ptr), parent_(&ptr){};
        ProxiObg operator*();
        IterNoConst& operator++();
        bool operator!=(const IterNoConst& other) const;

    private:
        size_t pos_;
        std::shared_ptr<StringRef>* parent_;
    };

    CowString(std::string_view str);
    CowString(const CowString& other);
    CowString(CowString&& other);

    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other);

    char*& GetData() const;
    const IterConst begin() const;  // NOLINT
    const IterConst end() const;    // NOLINT
    IterNoConst begin();            // NOLINT
    IterNoConst end();              // NOLINT

    ProxiObg operator[](size_t pos);
    const char At(size_t pos) const;

    CowString operator+(const CowString& other) const;
    CowString& operator+=(const CowString& other);
    bool operator==(const std::string_view& other) const;
    bool operator!=(const std::string_view& other) const;
    CowString operator+(const std::string_view& other) const;
    CowString& operator+=(const std::string_view& other);
    operator std::string_view();

private:
    std::shared_ptr<StringRef> ptr_;
};
