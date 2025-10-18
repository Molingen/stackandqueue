#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace ds {

template <typename T>
class MinMaxStack {
public:
    MinMaxStack() = default;

    void push(const T& v) {
        if (data_.empty()) {
            data_.push_back(Node{v, v, v});
        } else {
            const T mn = std::min(v, data_.back().cur_min);
            const T mx = std::max(v, data_.back().cur_max);
            data_.push_back(Node{v, mn, mx});
        }
    }

    void push(T&& v) {
        if (data_.empty()) {
            data_.push_back(Node{v, v, v});
        } else {
            T vv = std::move(v);
            const T mn = std::min(vv, data_.back().cur_min);
            const T mx = std::max(vv, data_.back().cur_max);
            data_.push_back(Node{std::move(vv), mn, mx});
        }
    }

    void pop() {
        if (data_.empty()) throw std::out_of_range("MinMaxStack::pop on empty stack");
        data_.pop_back();
    }

    const T& top() const {
        if (data_.empty()) throw std::out_of_range("MinMaxStack::top on empty stack");
        return data_.back().value;
    }

    T& top() {
        if (data_.empty()) throw std::out_of_range("MinMaxStack::top on empty stack");
        return data_.back().value;
    }

    const T& min() const {
        if (data_.empty()) throw std::out_of_range("MinMaxStack::min on empty stack");
        return data_.back().cur_min;
    }

    const T& max() const {
        if (data_.empty()) throw std::out_of_range("MinMaxStack::max on empty stack");
        return data_.back().cur_max;
    }

    size_t size() const noexcept { return data_.size(); }
    bool empty() const noexcept { return data_.empty(); }
    void clear() { data_.clear(); }

private:

    struct Node {
        T value;
        T cur_min;
        T cur_max;
    };

    std::vector<Node> data_;

};

} // namespace ds
