#pragma once
#include <vector>
#include <stdexcept>

namespace ds {

template <typename T, template<typename...> class TContainer = std::vector>
class Queue {
public:
    Queue() = default;

    void push(const T& el) {
        grow_if_full();
        if (cont_.size() == 0) cont_.resize(8);
        cont_[tail_] = el;
        tail_ = (tail_ + 1) % cont_.size();
        ++size_;
    }

    void push(T&& el) {
        grow_if_full();
        if (cont_.size() == 0) cont_.resize(8);
        cont_[tail_] = std::move(el);
        tail_ = (tail_ + 1) % cont_.size();
        ++size_;
    }

    void pop() {
        if (empty()) throw std::out_of_range("Queue::pop on empty queue");
        head_ = (head_ + 1) % cont_.size();
        --size_;
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("Queue::front on empty queue");
        return cont_[head_];
    }
    T& front() {
        if (empty()) throw std::out_of_range("Queue::front on empty queue");
        return cont_[head_];
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("Queue::back on empty queue");
        std::size_t idx = (tail_ + cont_.size() - 1) % cont_.size();
        return cont_[idx];
    }

    T& back() {
        if (empty()) throw std::out_of_range("Queue::back on empty queue");
        std::size_t idx = (tail_ + cont_.size() - 1) % cont_.size();
        return cont_[idx];
    }

    size_t size() const noexcept { return size_; }
    bool empty() const noexcept { return size_ == 0; }
    void clear() { head_ = tail_ = size_ = 0; }

private:

    TContainer<T>  cont_;
    size_t         head_ = 0;
    size_t         tail_ = 0;
    size_t         size_ = 0;

    void grow_if_full() {
        if (size_ < cont_.size()) return;
        size_t new_cap = cont_.size() == 0 ? 8 : cont_.size() * 2;
        TContainer<T> next;
        next.resize(new_cap);
        for (size_t i = 0; i < size_; ++i) {
            next[i] = std::move(cont_[(head_ + i) % (cont_.size() == 0 ? 1 : cont_.size())]);
        }
        cont_.swap(next);
        head_ = 0;
        tail_ = size_;
    }

};

} // namespace ds
