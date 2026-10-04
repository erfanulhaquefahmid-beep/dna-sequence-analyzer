#ifndef DYNAMIC_ARRAY_HPP
#define DYNAMIC_ARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace DS {

template <typename T>
class DynamicArray {
public:
    // Constructors & Destructor (Rule of 5)
    explicit DynamicArray(std::size_t initialCapacity = 4)
        : data_(nullptr), size_(0), capacity_(initialCapacity < 2 ? 2 : initialCapacity) {
        data_ = new T[capacity_];
    }

    ~DynamicArray() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    DynamicArray(const DynamicArray& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            T* newData = new T[other.capacity_];
            for (std::size_t i = 0; i < other.size_; ++i) {
                newData[i] = other.data_[i];
            }
            delete[] data_;
            data_ = newData;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    // Element Access
    T& operator[](std::size_t index) noexcept {
        return data_[index];
    }

    const T& operator[](std::size_t index) const noexcept {
        return data_[index];
    }

    T& at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray index out of range");
        }
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray index out of range");
        }
        return data_[index];
    }

    T& front() {
        if (isEmpty()) {
            throw std::out_of_range("DynamicArray is empty");
        }
        return data_[0];
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::out_of_range("DynamicArray is empty");
        }
        return data_[0];
    }

    T& back() {
        if (isEmpty()) {
            throw std::out_of_range("DynamicArray is empty");
        }
        return data_[size_ - 1];
    }

    const T& back() const {
        if (isEmpty()) {
            throw std::out_of_range("DynamicArray is empty");
        }
        return data_[size_ - 1];
    }

    // Capacity & Status
    std::size_t size() const noexcept {
        return size_;
    }

    std::size_t capacity() const noexcept {
        return capacity_;
    }

    bool isEmpty() const noexcept {
        return size_ == 0;
    }

    double loadFactor() const noexcept {
        return capacity_ == 0 ? 0.0 : static_cast<double>(size_) / static_cast<double>(capacity_);
    }

    // Modifiers
    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_) {
            return;
        }
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void shrink_to_fit() {
        if (size_ == capacity_) {
            return;
        }
        std::size_t newCapacity = size_ < 2 ? 2 : size_;
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[i]);
        }
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void clear() noexcept {
        size_ = 0;
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void push_back(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        data_[size_++] = std::move(value);
    }

    void pop_back() {
        if (isEmpty()) {
            throw std::underflow_error("DynamicArray is empty, cannot pop_back");
        }
        --size_;
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) {
            throw std::out_of_range("Insertion index out of bounds");
        }
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = value;
        ++size_;
    }

    void insert(std::size_t index, T&& value) {
        if (index > size_) {
            throw std::out_of_range("Insertion index out of bounds");
        }
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        for (std::size_t i = size_; i > index; --i) {
            data_[i] = std::move(data_[i - 1]);
        }
        data_[index] = std::move(value);
        ++size_;
    }

    void removeAt(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Deletion index out of bounds");
        }
        for (std::size_t i = index; i + 1 < size_; ++i) {
            data_[i] = std::move(data_[i + 1]);
        }
        --size_;
    }

    // Pointer Iterators for Range-based for loops
    T* begin() noexcept { return data_; }
    T* end() noexcept { return data_ + size_; }
    const T* begin() const noexcept { return data_; }
    const T* end() const noexcept { return data_ + size_; }

    // Comparison Operators
    bool operator==(const DynamicArray& other) const {
        if (size_ != other.size_) {
            return false;
        }
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] != other.data_[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const DynamicArray& other) const {
        return !(*this == other);
    }

private:
    T* data_;
    std::size_t size_;
    std::size_t capacity_;
};

} // namespace DS

#endif // DYNAMIC_ARRAY_HPP
