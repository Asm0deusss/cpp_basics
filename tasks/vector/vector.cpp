#include "vector.h"

void Vector::Iterator::CheckNull(const Vector::Iterator& ptr) const {
    if (ptr.ptr_ == nullptr) {
        throw std::exception();
    }
}
Vector::Iterator::Iterator(Vector::ValueType* pointer) {
    ptr_ = pointer;
}

Vector::Iterator::Iterator() {
    ptr_ = nullptr;
}

Vector::ValueType& Vector::Iterator::operator*() const {
    CheckNull(*this);
    return *ptr_;
}

Vector::ValueType* Vector::Iterator::operator->() const {
    CheckNull(*this);
    return ptr_;
}

Vector::Iterator& Vector::Iterator::operator=(Vector::Iterator other) {
    ptr_ = other.ptr_;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator++() {
    CheckNull(*this);
    ++ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int) {
    CheckNull(*this);
    Iterator copy = *this;
    ++ptr_;
    return copy;
}

Vector::Iterator& Vector::Iterator::operator--() {
    CheckNull(*this);
    --ptr_;
    return *this;
}

Vector::Iterator Vector::Iterator::operator--(int) {
    CheckNull(*this);
    Iterator copy = *this;
    --ptr_;
    return copy;
}

Vector::Iterator Vector::Iterator::operator+(Vector::DifferenceType shift) {
    CheckNull(*this);
    Iterator copy = *this;
    copy.ptr_ += shift;
    return copy;
}

Vector::DifferenceType Vector::Iterator::operator-(Vector::Iterator other) {
    return std::distance(other.ptr_, ptr_);
}

Vector::Iterator& Vector::Iterator::operator+=(Vector::DifferenceType shift) {
    CheckNull(*this);
    ptr_ += shift;
    return *this;
}

Vector::Iterator& Vector::Iterator::operator-=(Vector::DifferenceType shift) {
    CheckNull(*this);
    ptr_ -= shift;
    return *this;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const {
    return ptr_ == other.ptr_;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::Iterator::operator<=>(const Vector::Iterator& other) const {
    if (ptr_ == other.ptr_) {
        return std::strong_ordering::equal;
    } else if (ptr_ < other.ptr_) {
        return std::strong_ordering::less;
    } else {
        return std::strong_ordering::greater;
    }
}

void Vector::TryNew(Vector::Iterator& data, size_t size) {
    Iterator tmp = Vector::Iterator(new int[size]);
    data = tmp;
}

Vector::Vector() {
    size_ = 0;
    capacity_ = 0;
}

Vector::Vector(size_t size) {
    TryNew(data_, size);
    size_ = size;
    capacity_ = size;
    for (auto i = data_; i < data_ + size; ++i) {
        *i = 0;
    }
}

Vector::Vector(std::initializer_list<ValueType> list) {
    TryNew(data_, list.size());
    size_ = list.size();
    capacity_ = list.size();
    auto j = list.begin();
    for (auto i = data_; i < data_ + size_; ++i, ++j) {
        *i = *j;
    }
}

Vector::Vector(const Vector& other) {
    TryNew(data_, other.size_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    auto j = other.data_;
    for (auto i = data_; i < data_ + size_; ++i, ++j) {
        *i = *j;
    }
}

Vector& Vector::operator=(const Vector& other) {
    delete[] data_.ptr_;
    TryNew(data_, other.size_);
    size_ = other.size_;
    capacity_ = other.capacity_;
    auto j = other.data_;
    for (auto i = data_; i < data_ + size_; ++i, ++j) {
        *i = *j;
    }
    return *this;
}
Vector::~Vector() {
    delete[] data_.ptr_;
}

Vector::Iterator Vector::Begin() {
    return data_;
}

Vector::Iterator Vector::End() {
    return data_ + size_;
}

Vector::SizeType Vector::Size() const {
    return size_;
}

Vector::SizeType Vector::Capacity() const {
    return capacity_;
}

const Vector::ValueType* Vector::Data() const {
    return data_.ptr_;
}

Vector::ValueType& Vector::operator[](size_t position) {
    return *(data_.ptr_ + position);
}

const Vector::ValueType& Vector::operator[](size_t position) const {
    return *(data_.ptr_ + position);
}

bool Vector::operator==(const Vector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    Iterator j = other.data_;
    for (auto i = data_.ptr_; i != data_.ptr_ + size_; ++i, ++j) {
        if (*i != *j) {
            return false;
        }
    }
    return true;
}

bool Vector::operator!=(const Vector& other) const {
    return !(*this == other);
}

std::strong_ordering Vector::operator<=>(const Vector& other) const {
    size_t i = 0;
    size_t j = 0;
    while (i < size_ && j < other.size_) {
        if ((*this)[i] < other[j]) {
            return std::strong_ordering::less;
        } else if ((*this)[i] > other[j]) {
            return std::strong_ordering::greater;
        }
        ++i;
        ++j;
    }
    if (size_ < other.size_) {
        return std::strong_ordering::less;
    } else if (size_ > other.size_) {
        return std::strong_ordering::greater;
    }
    return std::strong_ordering::equal;
}

void Vector::Clear() {
    if (data_.ptr_ != nullptr) {
        for (size_t i = 0; i < size_; ++i) {
            (*this)[i] = 0;
        }
    }
    size_ = 0;
}

void Vector::PushBack(const Vector::ValueType& new_element) {
    if (capacity_ == 0) {
        TryNew(data_, 1);
        *(data_.ptr_) = new_element;
        size_ = 1;
        capacity_ = 1;
    } else {
        if (size_ == capacity_) {
            Iterator tmp = Iterator(data_);
            capacity_ *= 2;
            TryNew(data_, capacity_);
            for (size_t i = 0; i < size_; ++i) {
                (*this)[i] = *(tmp + i);
            }
            delete[] tmp.ptr_;
        }
        (*this)[size_] = new_element;
        ++size_;
    }
}

void Vector::PopBack() {
    *(data_.ptr_ + size_ - 1) = 0;
    --size_;
}

void Vector::Reserve(Vector::SizeType new_capacity) {
    if (new_capacity > capacity_) {
        Iterator tmp = data_;
        TryNew(data_, new_capacity);
        for (size_t i = 0; i < size_; ++i) {
            (*this)[i] = *(tmp + i);
        }
        delete[] tmp.ptr_;
        capacity_ = new_capacity;
    }
}

void Swap(auto& i, auto& j) {
    auto tmp = i;
    i = j;
    j = tmp;
}

void Vector::Swap(Vector& other) {
    ::Swap(data_, other.data_);
    ::Swap(size_, other.size_);
    ::Swap(capacity_, other.capacity_);
}

Vector::Iterator Vector::begin() {
    return data_;
}

Vector::Iterator Vector::end() {
    return data_ + size_;
}
