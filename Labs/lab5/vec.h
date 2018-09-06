#ifndef Vec_h_
#define Vec_h_
#include <cstddef>
#include <iostream>
// Simple implementation of the vector class, revised from Koenig and Moo.  This 
// class is implemented using a dynamically allocated array (of templated type T).  
// We ensure that that m_size is always <= m_alloc and when a push_back or resize 
// call would violate this condition, the data is copied to a larger array.

template <class T> class Vec {

public:   
  // TYPEDEFS
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef unsigned int size_type;

  // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
  Vec() { this->create(); }
  Vec(size_type n, const T& t = T()) { this->create(n, t); }
  Vec(const Vec& v) { copy(v); }
  Vec& operator=(const Vec& v); 
  ~Vec() { delete [] m_data; }

  // MEMBER FUNCTIONS AND OTHER OPERATORS
  T& operator[] (size_type i) { return m_data[i]; }
  const T& operator[] (size_type i) const { return m_data[i]; }
  void push_back(const T& t);
  iterator erase(iterator p);
  void resize(size_type n, const T& fill_in_value = T());
  void shrink(size_type n);
  void clear() { delete [] m_data;  create(); }
  bool empty() const { return m_size == 0; }
  size_type size() const { return m_size; }
  size_type allocated() const { return m_alloc; }
  void reallocate(size_type n) { m_alloc=n; }
  void print() const;

  // ITERATOR OPERATIONS
  iterator begin() { return m_data; }
  const_iterator begin() const { return m_data; }
  iterator end() { return m_data + m_size; }
  const_iterator end() const { return m_data + m_size; }

private:  
  // PRIVATE MEMBER FUNCTIONS
  void create();
  void create(size_type n, const T& val);
  void copy(const Vec<T>& v); 

  // REPRESENTATION
  T* m_data;         // Pointer to first location in the allocated array
  size_type m_size;  // Number of elements stored in the vector
  size_type m_alloc; // Number of array locations allocated,  m_size <= m_alloc
};

template <class T> void Vec<T>::print() const {
	std::cout<<"m_alloc: "<<m_alloc<<"\nm_size: "<<m_size<<std::endl;
	for(iterator q=m_data; q<m_data+m_size; q++)
		std::cout<<" "<<*q;
	std::cout<<std::endl<<std::endl;
}


// Create an empty vector (null pointers everywhere).
template <class T>  void Vec<T>::create() {
  m_data = NULL;
  m_size = m_alloc = 0;  // No memory allocated yet
}

// Create a vector with size n, each location having the given value
template <class T> void Vec<T>::create(size_type n, const T& val) {
  m_data = new T[n];
  m_size = m_alloc = n;
  for (T* p = m_data; p != m_data + m_size; ++p)
    *p = val;
}

// Assign one vector to another, avoiding duplicate copying.
template <class T> Vec<T>& Vec<T>::operator=(const Vec<T>& v) {
  if (this != &v) {
    delete [] m_data;
    this -> copy(v);
  }
  return *this;
}

// Create the vector as a copy of the given vector. 
template <class T> void Vec<T>::copy(const Vec<T>& v) {
  this->m_alloc = v.m_alloc;
  this->m_size = v.m_size;
  this->m_data = new T[this->m_alloc];
  
  // Copy the data
  for (size_type i = 0; i < this->m_size; ++i)
    this -> m_data[ i ] = v.m_data[ i ];
}

// Add an element to the end, resize if necesssary. 
template <class T> void Vec<T>::push_back(const T& val) {
  if (m_size == m_alloc) { 
    // Allocate a larger array, and copy the old values

    // Calculate the new allocation.  Make sure it is at least one.
    m_alloc *= 2;
    if (m_alloc < 1) m_alloc = 1;
    
    // Allocate and copy the old array
    T* new_data = new T[ m_alloc ];
    for (size_type i=0; i<m_size; ++i)
      new_data[i] = m_data[i];
    
    // Delete the old array and reset the pointers
    delete [] m_data;
    m_data = new_data;
  }

  // Add the value at the last location and increment the bound
  m_data[m_size] = val;
  ++ m_size;
}

// Shift each entry of the array after the iterator. Return the iterator, 
// which will have the same value, but point to a different element.
template <class T> typename Vec<T>::iterator Vec<T>::erase(iterator p) {
  // remember iterator and T* are equivalent
  for (iterator q = p; q < m_data+m_size-1; ++q)
    *q = *(q+1);
  m_size --;
  return p;
}

template <class T> typename Vec<T>::size_type remove_matching_elements(Vec<T>& v, const T& el) {
	typename Vec<T>::size_type x=0;
	
	for(typename Vec<T>::iterator q = v.begin(); q<v.begin()+v.size(); q++) {
		if(q>v.end()) {
			std::cout<<"over\n";
			break;
		}
		if(*q==el) {
			x++;
			v.erase(q);
			q--;
		}
	}
	
	if(v.size()<(double(v.allocated())+.5)/2) {
		v.shrink(v.size());
	}
		
	
	return x;
}

template <class T> void Vec<T>::shrink(size_type n) {
	if (n < m_alloc) {
      m_alloc = n;
      T* new_data = new T[m_alloc];
      for (size_type i=0; i<m_size; ++i)
		new_data[i] = m_data[i];
      delete [] m_data;
      m_data = new_data;
	}
}

// If n is less than or equal to the current size, just change the size.  If n is 
// greater than the current size, the new slots must be filled in with the given value. 
// Re-allocation should occur only if necessary.  push_back should not be used.
template <class T> void Vec<T>::resize(size_type n, const T& fill_in_value) {
  if (n <= m_size)
    m_size = n;
  else {
    // If necessary, allocate new space and copy the old values
    if (n > m_alloc) {
      m_alloc = n;
      T* new_data = new T[m_alloc];
      for (size_type i=0; i<m_size; ++i)
	new_data[i] = m_data[i];
      delete [] m_data;
      m_data = new_data;
    }
    
    // Now fill in the remaining values and assign the final size.
    for (size_type i = m_size; i<n; ++i)
      m_data[i] = fill_in_value;
    m_size = n;
  }
}
#endif
