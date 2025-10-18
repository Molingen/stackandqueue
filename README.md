# Контейнеры: стек, очередь и стек с min/max

- `Stack<T>` — стек (LIFO) на динамическом массиве (`std::vector` по умолчанию).
- `Queue<T>` — очередь (FIFO) на циклическом буфере.
- `MinMaxStack<T>` — стек с запросами `min()`/`max()` за O(1).

Файлы:
- `include/stack.hpp`
- `include/queue.hpp`
- `include/minmax_stack.hpp`
- `samples/main.cpp` — пример использования
- `test/*.cpp` — тесты на GoogleTest
- `CMakeLists.txt` — сборка проекта и тестов (gtest подтягивается через FetchContent)

---

## Как собрать и запустить тесты

```bash
# Генерация build-директории
cmake -S . -B build

# Компиляция
cmake --build build -j

# Прогнать тесты
ctest --test-dir build --output-on-failure

# Запустить пример
./build/sample_app
```

Требования: CMake ≥ 3.16, компилятор с поддержкой C++17 (GCC/Clang/MSVC).

---

## Реализация и интерфейсы

### 1) Стек `Stack<T, TContainer=std::vector>`

**Что бросает исключения:**
- `top()` и `pop()` на пустом стеке бросают `std::out_of_range`.

**Интерфейс:**
```cpp
void push(const T&);
void push(T&&);
void pop();
const T& top() const;
T& top();
std::size_t size() const noexcept;
bool empty() const noexcept;
void clear();
```

### 2) Очередь `Queue<T, TContainer=std::vector>`

Индексы топают по модулю `capacity`, это обеспечивает возможность прохода неким циклом. 
Когда `size_ == capacity`, делаем расширение: выделяем новый буфер в 2 раза больше предыдущего и перекладываем элементы в порядке следования, начиная с `head_`, далее обновляем `head_=0`, `tail_=size_`.

**Что бросает исключения:**
- `front()`, `back()` и `pop()` на пустой очереди бросают `std::out_of_range`.

**Интерфейс:**
```cpp
void push(const T&);
void push(T&&);
void pop();
const T& front() const;
T& front();
const T& back() const;
T& back();
std::size_t size() const noexcept;
bool empty() const noexcept;
void clear();
```

**Заметки:**
- Начальная ёмкость выбрана 8 для простоты жизни.
- `clear()` не освобождает память, чтобы не аллоцировать далее память за зря.


### 3) `MinMaxStack<T>` — стек с O(1) `min()` и `max()`

**Идея:** помимо текущего значения храним префиксные минимум и максимум на момент записи элемента.
Каждый узел выглядит так: `{ value, cur_min, cur_max }`.
- На `push(v)`: `cur_min = min(v, prev.cur_min)`, `cur_max = max(v, prev.cur_max)`.
- На `pop()`: просто снимаем верхний узел — то есть откатываем текущие min/max.
- Все запросы — O(1).

**Что бросает исключения:**
- `top/min/max/pop` на пустом стеке бросают `std::out_of_range`.

**Интерфейс:**
```cpp
void push(const T&);
void push(T&&);
void pop();
const T& top() const;
T& top();
const T& min() const;
const T& max() const;
std::size_t size() const noexcept;
bool empty() const noexcept;
void clear();
```

---