#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace DS {

template <typename T>
class Queue {
public:
    explicit Queue(std::size_t initialCapacity = 4)
        : data_(nullptr), front_(0), rear_(0), size_(0),
          capacity_(initialCapacity < 2 ? 2 : initialCapacity) {
        data_ = new T[capacity_];
    }

    ~Queue() {
        delete[] data_;
        data_ = nullptr;
        front_ = 0;
        rear_ = 0;
        size_ = 0;
        capacity_ = 0;
    }

    Queue(const Queue& other)
        : data_(nullptr), front_(0), rear_(other.size_), size_(other.size_),
          capacity_(other.capacity_) {
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[(other.front_ + i) % other.capacity_];
        }
    }

    Queue& operator=(const Queue& other) {
        if (this != &other) {
            T* newData = new T[other.capacity_];
            for (std::size_t i = 0; i < other.size_; ++i) {
                newData[i] = other.data_[(other.front_ + i) % other.capacity_];
            }
            delete[] data_;
            data_ = newData;
            front_ = 0;
            rear_ = other.size_;
            size_ = other.size_;
            capacity_ = other.capacity_;
        }
        return *this;
    }

    Queue(Queue&& other) noexcept
        : data_(other.data_), front_(other.front_), rear_(other.rear_),
          size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.front_ = 0;
        other.rear_ = 0;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    Queue& operator=(Queue&& other) noexcept {
        if (this != &other) {
            delete[] data_;
            data_ = other.data_;
            front_ = other.front_;
            rear_ = other.rear_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.data_ = nullptr;
            other.front_ = 0;
            other.rear_ = 0;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    bool isEmpty() const noexcept {
        return size_ == 0;
    }

    std::size_t size() const noexcept {
        return size_;
    }

    std::size_t capacity() const noexcept {
        return capacity_;
    }

    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_) {
            return;
        }
        T* newData = new T[newCapacity];
        for (std::size_t i = 0; i < size_; ++i) {
            newData[i] = std::move(data_[(front_ + i) % capacity_]);
        }
        delete[] data_;
        data_ = newData;
        front_ = 0;
        rear_ = size_;
        capacity_ = newCapacity;
    }

    void enqueue(const T& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        data_[rear_] = value;
        rear_ = (rear_ + 1) % capacity_;
        ++size_;
    }

    void enqueue(T&& value) {
        if (size_ >= capacity_) {
            reserve(capacity_ * 2);
        }
        data_[rear_] = std::move(value);
        rear_ = (rear_ + 1) % capacity_;
        ++size_;
    }

    void dequeue() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty, cannot dequeue");
        }
        front_ = (front_ + 1) % capacity_;
        --size_;
    }

    T& front() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty, cannot access front");
        }
        return data_[front_];
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty, cannot access front");
        }
        return data_[front_];
    }

    T& back() {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty, cannot access back");
        }
        std::size_t backIndex = (rear_ == 0 ? capacity_ - 1 : rear_ - 1);
        return data_[backIndex];
    }

    const T& back() const {
        if (isEmpty()) {
            throw std::underflow_error("Queue is empty, cannot access back");
        }
        std::size_t backIndex = (rear_ == 0 ? capacity_ - 1 : rear_ - 1);
        return data_[backIndex];
    }

    void clear() noexcept {
        front_ = 0;
        rear_ = 0;
        size_ = 0;
    }

private:
    T* data_;
    std::size_t front_;
    std::size_t rear_;
    std::size_t size_;
    std::size_t capacity_;
};

} // namespace DS

#endif // QUEUE_HPP
