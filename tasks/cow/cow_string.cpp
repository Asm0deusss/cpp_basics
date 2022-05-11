#include "cow_string.h"

StringRef::StringRef(const char* s, const size_t str_size) {
    size = str_size;
    str_ptr = new char[str_size];
    for (size_t i = 0; i < str_size; ++i) {
        str_ptr[i] = s[i];
    }
}

StringRef::~StringRef() {
    delete[] str_ptr;
}

// IterNoConst
bool CowString::IterNoConst::operator!=(const IterNoConst& other) const {
    if (pos_ != other.pos_) {
        return true;
    }
    return false;
}

ProxiObg CowString::IterNoConst::operator*() {
    return ProxiObg(*((*parent_)->str_ptr + pos_), *parent_);
}

CowString::IterNoConst& CowString::IterNoConst::operator++() {
    ++pos_;
    return *this;
}

// ProxiObg
char& ProxiObg::operator=(char s) {
    size_t pos = sym_ptr_ - (*parent_ptr_)->str_ptr;
    if (*sym_ptr_ != s && parent_ptr_->use_count() != 1) {
        *parent_ptr_ = std::make_shared<StringRef>((*parent_ptr_)->str_ptr, (*parent_ptr_)->size);
    }
    (*parent_ptr_)->str_ptr[pos] = s;
    return (*parent_ptr_)->str_ptr[pos];
}

bool ProxiObg::operator==(const char s) const {
    if (s == *sym_ptr_) {
        return true;
    }
    return false;
}

bool ProxiObg::operator!=(const char s) const {
    return !(*this == s);
}
ProxiObg::operator char() {
    return *sym_ptr_;
}

// CowString
CowString::CowString(std::string_view str) {
    ptr_ = std::make_shared<StringRef>(str.begin(), str.size());
}

CowString::CowString(const CowString& other) {
    ptr_ = other.ptr_;
}

CowString::CowString(CowString&& other) {
    ptr_ = std::move(other.ptr_);
}

CowString& CowString::operator=(const CowString& other) {
    ptr_ = other.ptr_;
    return *this;
}

CowString& CowString::operator=(CowString&& other) {
    ptr_ = std::move(other.ptr_);
    return *this;
}

char*& CowString::GetData() const {
    return (*ptr_).str_ptr;
}

const CowString::IterConst CowString::begin() const {
    return IterConst(&ptr_, 0);
}
const CowString::IterConst CowString::end() const {
    return IterConst(&ptr_, ptr_->size);
}
CowString::IterNoConst CowString::begin() {
    return IterNoConst(ptr_->str_ptr, ptr_);
}
CowString::IterNoConst CowString::end() {
    return IterNoConst(ptr_->str_ptr + ptr_->size, ptr_);
}
ProxiObg CowString::operator[](size_t pos) {
    return ProxiObg(ptr_->str_ptr[pos], ptr_);
}
const char CowString::At(size_t pos) const {
    return ptr_->str_ptr[pos];
}

CowString CowString::operator+(const CowString& other) const {
    std::string s = std::string(ptr_->str_ptr, ptr_->str_ptr + ptr_->size) +
                    std::string(other.ptr_->str_ptr, other.ptr_->str_ptr + other.ptr_->size);
    CowString upd(s);
    return upd;
}

CowString& CowString::operator+=(const CowString& other) {
    if (other.ptr_->size == 0) {
        return *this;
    }
    *this = *this + other;
    return *this;
}

CowString::operator std::string_view() {
    return std::string_view(ptr_->str_ptr, ptr_->size);
}

bool CowString::operator==(const std::string_view& other) const {
    if (other.size() != ptr_->size) {
        return false;
    }
    for (size_t i = 0; i < other.size(); ++i) {
        if (other[i] != ptr_->str_ptr[i]) {
            return false;
        }
    }
    return true;
}

bool CowString::operator!=(const std::string_view& other) const {
    return !(*this == other);
}
CowString CowString::operator+(const std::string_view& other) const {
    if (other.empty()) {
        return (*this);
    }
    std::string s = std::string(ptr_->str_ptr, ptr_->str_ptr + ptr_->size) + std::string(other.begin(), other.end());
    CowString upd(s);
    return upd;
}

CowString& CowString::operator+=(const std::string_view& other) {
    *this = *this + other;
    return *this;
}

// IterConst
bool CowString::IterConst::operator!=(const CowString::IterConst& other) const {
    if (cur_size_ != other.cur_size_) {
        return true;
    }
    return false;
}
char& CowString::IterConst::operator*() const {
    return *((*begin_ptr_)->str_ptr + cur_size_);
}
CowString::IterConst::IterConst(const std::shared_ptr<StringRef>* ptr, size_t pos) {
    begin_ptr_ = ptr;
    cur_size_ = pos;
}
CowString::IterConst& CowString::IterConst::operator++() {
    ++cur_size_;
    return *this;
}
