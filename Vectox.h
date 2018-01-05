/**
 *  Date of creation : 05/01/2018
 *  Info             : Personnal template class that act like vector.
 *  Currently State  : Under contruction...
 *  Author           : GuiM0x
 *
 */

#ifndef VECTOX_H
#define VECTOX_H
 
template<typename T>
class Vectox
{
public:
    typedef typename std::vector<T>::size_type _size_type;
    typedef typename std::vector<T>::iterator _iterator;
    typedef typename std::vector<T>::const_iterator _const_iterator;
    typedef typename std::vector<T>::reverse_iterator _reverse_iterator;
    typedef typename std::vector<T>::const_reverse_iterator _const_reverse_iterator;

    // Default
    Vectox();

    // Fill
    explicit Vectox(_size_type size);
    Vectox(_size_type size, const T& val);
    Vectox(std::initializer_list<T> il);

    // Copy-Move
    Vectox(const Vectox<T>&);
    Vectox(Vectox<T>&&);

    // Range
    template<typename InputIterator>
    Vectox(InputIterator first, InputIterator last);

    // Operator=
    Vectox<T>& operator=(const Vectox<T>&);
    Vectox<T>& operator=(Vectox<T>&&);
    Vectox<T>& operator=(std::initializer_list<T>);

    // Capacity
    _size_type size() const noexcept { return m_data->size(); }
    _size_type max_size() const noexcept { return m_data->max_size(); }
    void resize(_size_type n) { m_data->resize(n); }
    void resize(_size_type n, const T& val) { m_data->resize(n, val); }
    _size_type capacity() const noexcept { return m_data->capacity(); }
    bool empty() const noexcept { return m_data->empty(); }
    void reserve(_size_type n) { m_data->reserve(n); }
    void shrink_to_fit() { m_data->shrink_to_fit(); }

    // Modifiers
    void assign(_iterator first, _iterator last);
    void assign(_size_type n, const T& val) { m_data->assign(n, val); }
    void assign(std::initializer_list<T> il) { m_data->assign(il); }
    void push_back(const T& val) { m_data->push_back(val); }
    void push_back(T&& val) { m_data->push_back(std::move(val)); }
    void pop_back();
    _iterator erase(_const_iterator position) { return (m_data->erase(position)); }
    _iterator erase(_const_iterator first, _const_iterator last) { return (m_data->erase(first, last)); }
    void swap(Vectox<T>& x) { m_data->swap(*(x.data())); }
    void clear() noexcept { m_data->clear(); }

    // Element access
    T& operator[](_size_type);
    T& front();
    T& back();
    std::shared_ptr<std::vector<T>> data() { return m_data; }

    // Iterators
    _iterator begin() noexcept { return m_data->begin(); }
    _iterator end() noexcept { return m_data->end(); }
    _const_iterator cbegin() const noexcept { return m_data->cbegin(); }
    _const_iterator cend() const noexcept { return m_data->cend(); }
    _reverse_iterator rbegin() noexcept { return m_data->rbegin(); }
    _reverse_iterator rend() noexcept { return m_data->rend(); }
    _const_reverse_iterator crbegin() const noexcept { return m_data->crbegin(); }
    _const_reverse_iterator crend() const noexcept { return m_data->crend(); }


private:
    std::shared_ptr<std::vector<T>> m_data;

    // Error check
    void check(_size_type i, const std::string& message) const;
};

////// CTR(s)
template<typename T>
Vectox<T>::Vectox() :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>()))
{

}

template<typename T>
Vectox<T>::Vectox(_size_type size) :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>(size)))
{

}

template<typename T>
Vectox<T>::Vectox(_size_type size, const T& val) :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>(size, val)))
{

}

template<typename T>
Vectox<T>::Vectox(std::initializer_list<T> il) :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>(il)))
{

}

template<typename T>
template<typename InputIterator>
Vectox<T>::Vectox(InputIterator first, InputIterator last) :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>()))
{
    while(first != last) {
        this->push_back(*first);
        ++first;
    }
}

template<typename T>
Vectox<T>::Vectox(const Vectox<T>& cpy) :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>(*cpy.m_data)))
{

}

template<typename T>
Vectox<T>::Vectox(Vectox<T>&& other) :
    m_data(std::make_shared<std::vector<T>>(std::vector<T>(std::move(*other.m_data))))
{

}

// OPERATOR=
template<typename T>
Vectox<T>& Vectox<T>::operator=(const Vectox<T>& cpy)
{
    this->m_data = cpy;
}

template<typename T>
Vectox<T>& Vectox<T>::operator=(Vectox<T>&& other)
{
    this->m_data = std::move(other);
}

template<typename T>
Vectox<T>& Vectox<T>::operator=(std::initializer_list<T> il)
{
    this->m_data = il;
}

////// MEMBERS
template<typename T>
void Vectox<T>::check(_size_type i, const std::string& message) const
{
    if(i >= m_data->size())
        throw std::out_of_range(message);
}

template<typename T>
T& Vectox<T>::operator[](_size_type i)
{
    check(i, "Out of range on Vectox !");
    return (*m_data)[i];
}

template<typename T>
T& Vectox<T>::front()
{
    check(0, "Front on empty Vectox !");
    return m_data->front();
}

template<typename T>
T& Vectox<T>::back()
{
    check(0, "Back on empty Vectox !");
    return m_data->back();
}

template<typename T>
void Vectox<T>::assign(_iterator first, _iterator last)
{
    while(first != last) {
        m_data->push_back(*first);
        ++first;
    }
}

template<typename T>
void Vectox<T>::pop_back()
{
    check(0, "Pop back on empty Vectox !");
    m_data->pop_back();
}

#endif // VECTOX_H
