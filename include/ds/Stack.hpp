#ifndef STACK_HPP
#define STACK_HPP

#include "DynamicArray.hpp"
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace DS {

template <typename T>
class Stack {
public:
    explicit Stack(std::size_t initialCapacity = 4)
        : storage_(initialCapacity) {}

    void push(const T& value) {
        storage_.push_back(value);
    }

    void push(T&& value) {
        storage_.push_back(std::move(value));
    }

    void pop() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty, cannot pop");
        }
        storage_.pop_back();
    }

    T& top() {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty, cannot access top");
        }
        return storage_.back();
    }

    const T& top() const {
        if (isEmpty()) {
            throw std::underflow_error("Stack is empty, cannot access top");
        }
        return storage_.back();
    }

    bool isEmpty() const noexcept {
        return storage_.isEmpty();
    }

    std::size_t size() const noexcept {
        return storage_.size();
    }

    void clear() noexcept {
        storage_.clear();
    }

private:
    DynamicArray<T> storage_;
};

} // namespace DS

#endif // STACK_HPP
