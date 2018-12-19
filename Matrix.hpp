/////////////////////////////////////////////////////////////////////////////////////
/*                                                                                 */
/*   Matrix.hpp                                                                    */
/*   -----------------------                                                       */
/*   Author : Guit0x                                                               */
/*                                                                                 */
/*   Type            : Template class                                              */
/*   OS Dependencies : none                                                        */
/*   Library Used    : STL                                                         */
/*                                                                                 */
/*   A simple class that hold a linear vector and behave like a two dimensional    */
/*   container.                                                                    */
/*                                                                                 */
/////////////////////////////////////////////////////////////////////////////////////

#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>
#include <cassert>

/////////////////////////////////////////////////////////////////////
template<typename T>
class Matrix
{
    using iterator               = typename std::vector<T>::iterator;
    using const_iterator         = typename std::vector<T>::const_iterator;
    using reverse_iterator       = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

public:
    Matrix() = delete;
    Matrix(std::size_t rows, std::size_t cols, const T& val = T{});
    Matrix(const std::initializer_list<std::initializer_list<T>>&);
    Matrix<T>& operator=(const std::initializer_list<std::initializer_list<T>>&);

public:
    bool empty()       const { return m_cells.empty(); }
    std::size_t size() const { return m_cells.size();  }
    std::size_t rows() const { return m_rows;          }
    std::size_t cols() const { return m_cols;          }

public:
    void init(std::size_t rows, std::size_t cols, const T& val = T{});

public:
    iterator begin()                 noexcept       { return m_cells.begin();   }
    const_iterator begin()           const noexcept { return m_cells.begin();   }
    iterator end()                   noexcept       { return m_cells.end();     }
    const_iterator end()             const noexcept { return m_cells.end();     }
    reverse_iterator rbegin()        noexcept       { return m_cells.rbegin();  }
    const_reverse_iterator rbegin()  const noexcept { return m_cells.rbegin();  }
    reverse_iterator rend()          noexcept       { return m_cells.rend();    }
    const_reverse_iterator rend()    const noexcept { return m_cells.rend();    }
    const_iterator cbegin()          const noexcept { return m_cells.cbegin();  }
    const_iterator cend()            const noexcept {  return m_cells.cend();   }
    const_reverse_iterator crbegin() const noexcept { return m_cells.crbegin(); }
    const_reverse_iterator crend()   const noexcept { return m_cells.crend();   }

public:
    T& operator[](std::size_t n);
    const T& operator[](std::size_t n) const;
    T& operator()(std::size_t row, std::size_t col);
    const T& operator()(std::size_t row, std::size_t col) const;

private:
    void checkAccess(std::size_t n) const;

private:
    std::size_t m_rows{};
    std::size_t m_cols{};
    std::vector<T> m_cells{};
};

/////////////////////////////////////////////////////////////////////
template<typename T>
inline Matrix<T>::Matrix(std::size_t rows, std::size_t cols, const T& val) :
    m_rows{rows},
    m_cols{cols},
    m_cells(rows*cols, val)
{

}

template<typename T>
inline Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& il) :
    Matrix(il.size(), il.begin()->size() != 0 ? il.begin()->size() : 0, T{})
{
    const std::size_t cols = il.begin()->size();
    auto it = std::find_if(il.begin(), il.end(),
                           [cols](const std::initializer_list<T>& il){
                               return il.size() != cols;
                           });
    assert(it == il.end() && "Column number must be the same in each rows");
    std::size_t i{0};
    for(const auto& row : il){
        std::size_t j{0};
        for(const auto& cell : row){
            m_cells[(i*cols)+j] = cell;
            ++j;
        }
        ++i;
    }
}

template<typename T>
inline Matrix<T>& Matrix<T>::operator=(const std::initializer_list<std::initializer_list<T>>& il)
{
    *this = Matrix{il};
    return *this;
}

template<typename T>
void Matrix<T>::init(std::size_t rows, std::size_t cols, const T& val)
{
	*this = Matrix{rows, cols, val};
}

template<typename T>
inline void Matrix<T>::checkAccess(std::size_t n) const
{
    if(m_cells.empty())
        throw(std::runtime_error{"Access on empty container"});
    if(n >= m_cells.size())
        throw(std::runtime_error{"Access out of range"});
}

template<typename T>
inline T& Matrix<T>::operator[](std::size_t n)
{
    checkAccess(n);
    return m_cells[n];
}

template<typename T>
inline const T& Matrix<T>::operator[](std::size_t n) const
{
    checkAccess(n);
    return m_cells[n];
}

template<typename T>
inline T& Matrix<T>::operator()(std::size_t row, std::size_t col)
{
    const std::size_t index = (row*m_cols) + col;
    checkAccess(index);
    return m_cells[index];
}

template<typename T>
inline const T& Matrix<T>::operator()(std::size_t row, std::size_t col) const
{
    const std::size_t index = (row*m_cols) + col;
    checkAccess(index);
    return m_cells[index];
}

#endif // !MATRIX_HPP_INCLUDED
