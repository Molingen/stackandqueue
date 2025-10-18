#include <iostream>
#include <stack.hpp>
#include <queue.hpp>
#include <minmax_stack.hpp>

int main() {
    ds::Stack<int> st;
    st.push(10), st.push(20);
    std::cout << "Stack top=" << st.top() << " size=" << st.size() << '\n';
    st.pop();
    std::cout << "Stack top after pop=" << st.top() << " size=" << st.size() << '\n';

    ds::Queue<int> q;
    for (int i = 1; i <= 5; ++i) q.push(i);
    std::cout << "Queue front=" << q.front() << " back=" << q.back() << " size=" << q.size() << '\n';
    q.pop();
    std::cout << "Queue front after pop=" << q.front() << " size=" << q.size() << '\n';

    ds::MinMaxStack<int> mm;
    for (int v : {3,1,2,1,5}) {
        mm.push(v);
        std::cout << "push " << v << " -> min=" << mm.min() << " max=" << mm.max() << '\n';
    }
    while (!mm.empty()) {
        std::cout << "top=" << mm.top() << " min=" << mm.min() << " max=" << mm.max() << '\n';
        mm.pop();
    }
    return 0;
}
