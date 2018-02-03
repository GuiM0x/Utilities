#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <vector>
#include <memory>
#include <utility>

template<typename> class Matrix;

template<typename T>
std::ostream& operator<<(std::ostream&, const Matrix<T>&);
template<typename T>
bool operator==(const Matrix<T>&, const Matrix<T>&);
template<typename T>
bool operator!=(const Matrix<T>&, const Matrix<T>&);

template<typename T>
class Matrix
{
private:
    class Coord
    {
    public:
        Coord() = delete;
        Coord(std::size_t _row, std::size_t _col) :
            row{_row}, col{_col} {}

        std::size_t row, col;
    };

public:
    typedef typename std::vector<T>::size_type size_type;

    /// CONSTRUCTORS
    Matrix();
    Matrix(size_type rows, size_type cols, const T& val = T{});
    Matrix(std::initializer_list<std::initializer_list<T>> il);
    Matrix(const Matrix<T>&);
    Matrix(Matrix<T>&&) noexcept;
    Matrix<T>& operator=(const Matrix<T>&);
    Matrix<T>& operator=(Matrix<T>&&) noexcept;
    ~Matrix() = default;

    /// CAPACITY
    size_type size() const
    { return m_data->size(); }

    bool empty() const
    { return m_data->empty(); }

    Coord dimension() const
    { return Coord(m_rows, m_cols); }

    Coord getCoordByID(size_type id) const
    { return Coord{id/m_cols, id%m_rows}; }

    size_type getIDByCoord(size_type row, size_type col) const
    { return ((row*m_cols)+col); }

    /// ELEMENTS ACCESS
    T& operator[](size_type id) const;
    T& operator()(size_type row, size_type col) const;

    /// MODIFIERS
    Matrix<T>& swap(Matrix<T>&);

    /// FRIEND OPERATORS
    friend bool operator==<T>(const Matrix<T>&, const Matrix<T>&);
    friend bool operator!=<T>(const Matrix<T>&, const Matrix<T>&);
    friend std::ostream& operator<<<T>(std::ostream&, const Matrix<T>&);

private:
    std::shared_ptr<std::vector<T>> m_data;
    size_type m_rows = 0;
    size_type m_cols = 0;

    void check(size_type i, const std::string& msg) const;
    void check(size_type row, size_type col, const std::string& msg) const;
};

//////////////////////////////////////////////////////////////////
/////// CONSTRUCTOR(S)
template<typename T>
Matrix<T>::Matrix() :
    m_data{std::make_shared<std::vector<T>>(std::vector<T>())}
{

}

template<typename T>
Matrix<T>::Matrix(size_type rows, size_type cols, const T& val) :
    m_data{std::make_shared<std::vector<T>>(std::vector<T>(rows*cols, val))},
    m_rows{rows}, m_cols{cols}
{

}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> il) :
    Matrix(il.size(), (il.size() > 0 ? il.begin()->size() : 0))
{
    // TO DO : Gérer le cas où des lignes n'aurait pas le même nombre de colonnes (throw)

    std::size_t i{0};
    for(const auto& line : il){
        std::size_t j{0};
        for(const auto& val : line){
            (*m_data)[(i*m_cols)+j] = val;
            ++j;
        }
        ++i;
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& cpy) :
    m_data{std::make_shared<std::vector<T>>(*cpy.m_data)},
    m_rows{cpy.m_rows}, m_cols{cpy.m_cols}
{

}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept :
    m_data{std::make_shared<std::vector<T>>(std::move(*other.m_data))},
    m_rows{other.m_rows}, m_cols{other.m_cols}
{

}
//////////////////////////////////////////////////////////////////
/////// FUNCTION(S)
template<typename T>
Matrix<T>& Matrix<T>::swap(Matrix<T>& other)
{
    Matrix<T> tmp{*this};
    *this = std::move(other);
    other = std::move(tmp);

    return *this;
}

template<typename T>
void Matrix<T>::check(size_type i, const std::string& msg) const
{
    if(i >= m_data->size())
        throw std::out_of_range(msg);
}

template<typename T>
void Matrix<T>::check(size_type row, size_type col, const std::string& msg) const
{
    if((row*m_cols)+col >= m_data->size())
        throw std::out_of_range(msg);
}
//////////////////////////////////////////////////////////////////
/////// ELEMENT ACCESS
template<typename T>
T& Matrix<T>::operator[](size_type id) const
{
    check(id, "Access out of range");
    return (*m_data)[id];
}

template<typename T>
T& Matrix<T>::operator()(size_type row, size_type col) const
{
    check(row, col, "Access out of range");
    return (*m_data)[(row*m_cols)+col];
}
//////////////////////////////////////////////////////////////////
/////// ASSIGN OPERATORS
template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& cpy)
{
    if(this != &cpy){
        *m_data = *cpy.m_data;
        m_rows  = cpy.m_rows;
        m_cols  = cpy.m_cols;
    }

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
    if(this != &other){
        *m_data = std::move(*other.m_data);
        m_rows  = other.m_rows;
        m_cols  = other.m_cols;
    }

    return *this;
}
//////////////////////////////////////////////////////////////////
/////// OPERATOR(S)
//(operator<< Provisoire)
template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix)
{
    if(!matrix.empty()){
        os << "Global size : " << matrix.size() << '\n'
           << "Total Rows  : " << matrix.m_rows << '\n'
           << "Total Cols  : " << matrix.m_cols << '\n'
           << '\n';
        for(std::size_t i=0; i<matrix.m_rows; ++i){
            for(std::size_t j=0; j<matrix.m_cols; ++j){
                os << const_cast<Matrix<T>&>(matrix)(i, j) << ' ';
            }
            os << '\n';
        }
        os << "--------------------------------";
    }
    else{
        os << "Matrix empty.\n";
        os << "--------------------------------";
    }

    return os;
}

template<typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return (*(lhs.m_data) == *(rhs.m_data));
}

template<typename T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs)
{
    return !(lhs == rhs);
}

#endif // MATRIX_HPP_INCLUDED
