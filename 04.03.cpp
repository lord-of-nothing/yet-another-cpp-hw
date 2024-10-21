#include <algorithm>
#include <cstring>
#include <iostream>
#include <utility>

template <typename T>
class Container {
 public:
  Container() : data_(nullptr), size_(0), capacity_(0) {}

  Container(std::size_t size) : size_(size), capacity_(size) {
    data_ = new T[capacity_]{};
  }

  Container(const Container& other)
      : size_(other.size_), capacity_(other.capacity_) {
    data_ = new T[capacity_]{};
    std::ranges::copy(other.data_, other.data_ + size_, data_);
  }

  Container(Container&& other) : Container() { swap(other); }

  Container& operator=(Container other) {
    swap(other);
    return *this;
  }

  ~Container() { delete[] data_; }

  void swap(Container& other) {
    using std::swap;

    swap(data_, other.data_);
    swap(size_, other.size_);
    swap(capacity_, other.capacity_);
  }

  void push_back(const T& value) {
    if (size_ == capacity_) {
      double_capacity();
    }
    data_[size_] = value;
    ++size_;
  }

  std::size_t size() { return size_; }

  std::size_t capacity() { return capacity_; }

  const T& operator[](size_t idx) const { return data_[idx]; }

  T& operator[](size_t idx) { return data_[idx]; }

  const T& front() const { return data_[0]; }

  T& front() { return data_[0]; }

  const T& back() const { return data_[size_ - 1]; }

  T& back() { return data_[size_ - 1]; }

  bool empty() { return size_ == 0; }

  void clear() { size_ = 0; }

 private:
  T* data_;
  std::size_t size_;
  std::size_t capacity_;

  void double_capacity() {
    std::size_t new_capacity = std::max((std::size_t)2, capacity_ * 2);
    T* new_data = new T[new_capacity];
    std::ranges::copy(data_, data_ + size_, new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_capacity;
  }
};

//  ================================================================================================

template <typename T>
inline void swap(Container<T>& x, Container<T>& y) { x.swap(y); }

//  ================================================================================================

int main() {
  // из заготовки
  const std::size_t size = 5;
  Container<int> container_1;
  Container<int> container_2(size);
  Container container_3(container_2);
  Container container_4(std::move(container_3));
  container_1 = container_2;
  container_3 = std::move(container_4);
  swap(container_1, container_3);

  // добавление в конец и изменение по индексу
  Container<std::string> a;
  std::string cur_string = "A";
  for (int i = 0; i < 10; ++i) {
    a.push_back(cur_string);
    cur_string += "A";
  }
  a[6] = "BBB";
  // front и back
  std::cout << "Front: " << a.front() << "\nBack: " << a.back() << std::endl;
  a.front() = "Z";
  a.back() = "hhh";
  std::cout << "Resulting containter: ";
  for (int i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }

  // геттеры
  std::cout << "\nSize: " << a.size() << "\nCapacity: " << a.capacity()
            << std::endl;

  // очистка
  std::cout << "Is empty: " << a.empty() << std::endl;
  a.clear();
  std::cout << "Cleared!" << std::endl;
  std::cout << "Is empty: " << a.empty();
}