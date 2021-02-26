#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <iostream>

template<typename Type>
class Vector
{
  public:

    // Стандартный конструктор
    Vector();

    // Конструктор копирования
    Vector(const Vector& other);

    // Оператор копирующего присваивания
    Vector& operator=(const Vector& other);

    // Конструктор перемещения
    Vector(Vector&& other);

    // Оператор присваивания перемещением
    Vector& operator=(Vector&& other);

    // Деструктор
    ~Vector();

    // Добавить элемент в конец вектора
    void push_back(const Type& element);

    // Удалить элемент из конца вектора
    void pop_back();

    // Добавить в вектор count элементов со значением value
    void assign(std::size_t count, const Type& value);

    // Вовзрат ссылки на последний элемент в векторе
    const Type& back() const;

    // Вовзрат ссылки на первый элемент в векторе
    const Type& front() const;

    // Вовзращает текущую вместимость вектора
    std::size_t capacity() const;

    // Возвращает текущую заполненность вектора
    std::size_t size() const;

    // Вовзращает true, если вектор пустой, иначе - false
    bool empty() const;

    // Очищает вектор
    void clear();

    // Выделяет память для хранения как минимум size элементов типа Type, не инициализируя
    void reserve(std::size_t size);

    // Делает размер вектора как минимум count и инициализирует вставленные элементы стандартным значением
    void resize(std::size_t count);

    // Если неиспользуемой памяти слишком много, то сокращает её размер до count_
    void shrink_to_fit();

    // Возвращает ссылку на элемент в позиции index
    Type& at(std::size_t index);

    // Возвращает константную ссылку на элемент в позиции index
    const Type& at(std::size_t index) const;

    // Вовзращает ссылку на элемент в позиции index
    Type& operator[](std::size_t index);

    // Возвращает константную ссылку на элемент в позиции index
    const Type& operator[](std::size_t index) const;

    // ToDo
    /*
      // Вставка в конец стразу нескольких элементов
      template <class Args>
      void emplace_back(Args && args);
    */

  private:

    // Указатель на массив с данными
    Type* data_;

    // Заполненость
    std::size_t count_;

    // Вместимость
    std::size_t capacity_;
};



//***************************************************************************//
template<typename Type>
Vector<Type>::Vector()
{
    data_ = nullptr;
    count_ = 0;
    capacity_ = 0;
}



template<typename Type>
Vector<Type>::Vector(const Vector<Type>& other)
{
    count_ = other.count_;
    capacity_ = other.capacity_;
    data_ = nullptr;

    if (capacity_ != 0) {
        data_ = new Type[capacity_];
        for (std::size_t i = 0; i < count_; i++) {
            data_[i] = other.data_[i];
        }
    }
}



template<typename Type>
Vector<Type>::Vector(Vector<Type>&& other)
{
    count_ = other.count_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.count_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
}



template<typename Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& other)
{
    if (this == &other) {
      return *this;
    }

    std::size_t newCount = other.count_;
    std::size_t newCapacity = other.capacity_;
    Type* newData = nullptr;

    if (newCapacity > 0) {
        newData = new Type[newCapacity];
        for (std::size_t i = 0; i < newCount; i++) {
            newData[i] = other.data_[i];
        }
    }

    delete[] data_;
    data_ = newData;
    count_ = newCount;
    capacity_ = newCapacity;

    return *this;
}



template<typename Type>
Vector<Type>& Vector<Type>::operator=(Vector<Type>&& other)
{
    std::size_t oldCount = count_;
    std::size_t oldCapacity = capacity_;
    Type* oldData = data_;

    count_ = other.count_;
    capacity_ = other.capacity_;
    data_ = other.data_;

    other.count_ = oldCount;
    other.capacity_ = oldCapacity;
    other.data_ = oldData;

    return *this;
}



template<typename Type>
Vector<Type>::~Vector()
{
    delete[] data_;
}



template<typename Type>
void Vector<Type>::push_back(const Type& element)
{
    if (count_ == capacity_) {
        std::size_t newCapacity = capacity_ * 2;
        if (newCapacity == 0) {
            newCapacity = 1;
        }
        Type* newData = new Type[newCapacity];
        for (std::size_t i = 0; i < count_; i++) {
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    data_[count_] = element;
    ++count_;
}



template<typename Type>
void Vector<Type>::pop_back()
{
   count_ -= 1;
}



template<typename Type>
void Vector<Type>::assign(std::size_t count, const Type& value)
{
    if (count > capacity_) {
        std::size_t newCapacity = capacity_ * 2;
        if (newCapacity == 0) {
            newCapacity = 1;
        }
        while (count > newCapacity) {
            newCapacity *= 2;
        }
        Type* newData = new Type[newCapacity];

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    for (std::size_t i = 0; i < count; i++) {
        data_[i] = value;
    }

    if (count > count_) {
        count_ = count;
    }
}



template<typename Type>
const Type& Vector<Type>::back() const
{
    return data_[count_ - 1];
}



template<typename Type>
const Type& Vector<Type>::front() const
{
    return data_[0];
}



template<typename Type>
std::size_t Vector<Type>::capacity() const
{
    return capacity_;
}



template<typename Type>
std::size_t Vector<Type>::size() const
{
    return count_;
}



template<typename Type>
bool Vector<Type>::empty() const
{
    return count_ == 0;
}



template<typename Type>
void Vector<Type>::clear()
{
    delete[] data_;
    data_ = nullptr;
    count_ = 0;
    capacity_ = 0;
}



template<typename Type>
void Vector<Type>::reserve(std::size_t size)
{
    if (size <= capacity_) {
        return;
    }

    std::size_t newCapacity = capacity_ * 2;
    if (newCapacity == 0) {
        newCapacity = 1;
    }
    while (size > newCapacity) {
        newCapacity *= 2;
    }
    Type* newData = new Type[newCapacity];
    for (std::size_t i = 0; i < count_; i++) {
        newData[i] = data_[i];
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
}


template<typename Type>
void Vector<Type>::resize(std::size_t count)
{
    if (count <= count_) {
        count_ = count;
        return;
    }

    if (count < capacity_) {
        for (std::size_t i = count_; i < count; ++i) {
            data_[i] = Type();
        }
        count_ = count;
        return;
    }

    std::size_t newCapacity = capacity_ * 2;
    if (newCapacity == 0) {
        newCapacity = 1;
    }
    while (count > newCapacity) {
        newCapacity *= 2;
    }
    Type* newData = new Type[newCapacity];
    for(std::size_t i = 0; i < count_; ++i) {
        newData[i] = data_[i];
    }
    for (std::size_t i = count_; i < count; ++i) {
        newData[i] = Type();
    }

    delete[] data_;
    data_ = newData;
    capacity_ = newCapacity;
    count_ = count;
}



template<typename Type>
void Vector<Type>::shrink_to_fit()
{
    if (count_ == 0) {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        return;
    }

    if (count_ <= (capacity_ / 2)) {
        std::size_t newCapacity = capacity_ / 2;
        while (count_ <= (newCapacity / 2)) {
            newCapacity /= 2;
        }
        Type* newData = new Type[newCapacity];
        for(std::size_t i = 0; i < count_; ++i) {
            newData[i] = data_[i];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }
}



template<typename Type>
Type& Vector<Type>::at(std::size_t index)
{
    return data_[index];
}



template<typename Type>
const Type& Vector<Type>::at(std::size_t index) const
{
    return data_[index];
}



template<typename Type>
Type& Vector<Type>::operator[](std::size_t index)
{
    return data_[index];
}



template<typename Type>
const Type& Vector<Type>::operator[](std::size_t index) const
{
    return data_[index];
}
//***************************************************************************//



template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T> &v)
{
    if (v.empty()) {
        out << "";
    }

    for (std::size_t i = 0; i < v.size(); i++) {
        out << v[i] << " ";
    }

    return out;
}

#endif // VECTOR_HPP
