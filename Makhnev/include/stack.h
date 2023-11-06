#ifndef __STACK_H__
#define __STACK_H__
#include <stdexcept>
const int MaxStackSize = 100;
template <typename T>
class IDataStrucure {
    void Push(const T& elem);
    T& Top();
    const T& Top() const;
    bool IsEmpty() const;
    size_t Size() const;
    void Pop();
};
#define DYNAMIC_ARRAY
#ifdef DYNAMIC_ARRAY
template <class T>
class TStack : public IDataStrucure<T>
{
    T* pMem;
    size_t size;
    size_t end;
public:

    void Push(const T& elem);
    explicit TStack(size_t _size = 2);
    TStack(const TStack<T>& stack);
    TStack(TStack<T>&& stack) noexcept;
    TStack& operator= (TStack<T>&& stack) noexcept;
    bool operator== (const TStack<T>& stack);
    bool operator!= (const TStack<T>& stack);

    ~TStack() { delete[] pMem;}
    T& Top();
    size_t Size() const;
    bool IsEmpty() const noexcept;
    const T& Top() const;
    void Pop();
};
template<class T>
inline void TStack<T>::Push(const T& elem)
{
    if (end >= size) {
        T* tmp = new T[size_t(size * 1.5)];
        size = size_t(size * 1.5);
        for (size_t i = 0; i < size; i++)
        {
            tmp[i] = pMem[i];
        }
        delete[] pMem;
        pMem = tmp;
    }
    pMem[end] = elem;
    end++;
}
template<class T>
inline TStack<T>::TStack(size_t _size)
{
    size = _size;
    end = 0;
    if ((size < 1) || (size > MaxStackSize))
        throw size;
    pMem = new T[size];
}

template<class T>
inline TStack<T>::TStack(const TStack<T>& stack)
{
    size = stack.end + 1;
    pMem = new T[size];
    end = stack.end;
    for (size_t i = 0; i < end; i++)
    {
        pMem[i] = stack.pMem[i];
    }
}

template<class T>
inline TStack<T>::TStack(TStack<T>&& stack) noexcept
{
    pMem = stack.pMem;
    stack.pMem = nullptr;
    size = stack.size;
    end = stack.end;
}

template<class T>
inline TStack<T>& TStack<T>::operator=(TStack<T>&& stack) noexcept
{
    std::swap(pMem, stack.pMem);
    size = stack.size;
    end = stack.end;
}

template<class T>
inline bool TStack<T>::operator==(const TStack<T>& stack)
{
    if (end != stack.end) return false;
    for (size_t i = 0; i < end; i++)
    {
        if (stack.pMem[i] != pMem[i]) return false;
    }
    return true;
}

template<class T>
inline bool TStack<T>::operator!=(const TStack<T>& stack)
{
    return !(*this == stack);
}

template<class T>
inline T& TStack<T>::Top()
{
    if (end == 0) throw std::out_of_range("stack is empty");
    return pMem[end - 1];
}

template<class T>
inline const T& TStack<T>::Top() const
{
    if (end == 0) throw std::out_of_range("stack is empty");
    return pMem[end - 1];
}

template<class T>
inline void TStack<T>::Pop()
{
    if (end == 0) throw std::out_of_range("stack is empty");
    end--;
}

template<class T>
inline size_t TStack<T>::Size() const
{
    return size;
}

template<class T>
inline bool TStack<T>::IsEmpty() const noexcept
{
    return end == 0;
}




#endif // DynamicArray



#endif
