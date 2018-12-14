#pragma once 

const unsigned int _init_array_size = 5;

template <typename TData>
class CArray
{
public:
  CArray(
      unsigned int _size = _init_array_size
    );
  CArray(
      const CArray& _array
    );
  ~CArray();
 
  void push_back(
      const TData& _value
    );

  void insert(
      unsigned int _index, const TData& _value
    );

  void erase(
      unsigned int _index
    );

  void clear();

  unsigned  int size() const;

  TData& operator[] (
      unsigned int _index
    );

  void print();

protected:
  unsigned int asize;
  unsigned int count;
  TData **arr;

  void init(
      unsigned int _from
    );
  void expand();
};


template <typename TData>
CArray<TData>::CArray(
    unsigned int _size = _init_array_size
  )
{
  asize = _size;
  count = 0;
  arr = new TData*[asize];
  init(0);
}

template <typename TData>
CArray<TData>::CArray(
    const CArray& _array
  )
{
  asize = _array.asize;
  count = _array.count;
  arr = new TData*[asize];
  for (int i = 0; i < count; i++)
  {
    arr[i] = new TData(*_array.arr[i]);
  }

  init(count);
}

template <typename TData>
void CArray<TData>::init(
    unsigned int _from
)
{
  for (unsigned int i = _from; i < asize; i++)
  {
    arr[i] = nullptr;
  }
}

template <typename TData>
void CArray<TData>::expand()
{
  asize *= 2;
  TData **tempArr = new TData*[asize];
  for (unsigned int i = 0; i < count; i++)
  {
    tempArr[i] = arr[i];
  }

  delete[] arr;

  arr = tempArr;

  init(count);
}

template <typename TData>
CArray<TData>::~CArray()
{
  for (unsigned int i = 0; i < count; i++)
  {
    delete arr[i];
  }
  delete[] arr;
}

template <typename TData>
void CArray<TData>::push_back(
    const TData& _value
  )
{
  if (count >= asize)
  {
    expand();
  }

  arr[count] = new TData(_value);
    ++count;

}

template <typename TData>
void CArray<TData>::insert(
    unsigned int _index, const TData& _value
  )
{
  if ((_index != 0) && (_index >= count))
  {
    return;
  }

  if (count >= asize)
  {
    expand();
  }
  
  if (count > 0)
  {
    for (unsigned int i = count; i > _index; i--)
    {
      arr[i] = arr[i - 1];
    }
  }
  arr[_index] = new TData(_value);
  ++count;
}

template <typename TData>
void CArray<TData>::erase(
    unsigned int _index
  )
{
  if (_index < count)
  {
    delete arr[_index];

    for (unsigned int i = _index; i < count-1; i++)
    {
      arr[i] = arr[i + 1];
    }
    arr[count - 1] = nullptr;
    --count;
  }
}

template <typename TData>
void CArray<TData>::clear()
{
  for (unsigned int i = 0; i < count; i++)
  {
    delete arr[i];
  }

  delete []arr;

  asize = _init_array_size;
  arr = new TData*[asize];
  count = 0;

  init(0);
}

template <typename TData>
unsigned int CArray<TData>::size() const
{
  return count;
}

template <typename TData>
TData& CArray<TData>::operator[] (
    unsigned int _index
  )
{
  if (_index < count)
  {
    return *arr[_index];
  }
  else
  {
    throw "BAD INDEX";
  }
}

template <typename TData>
void CArray<TData>::print()
{
  if (count)
  {
    for (unsigned int i = 0; i < count; i++)
    {
      cout << *arr[i] << endl;
    }
  }
  else
  {
    cout << "Array is empty" << endl;
  }
}