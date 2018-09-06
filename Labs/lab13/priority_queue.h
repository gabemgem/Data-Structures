#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    for(unsigned int i=0; i<values.size(); ++i)
      push(values[i]);
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    unsigned int i = m_heap.size()-1;
    while(i!=0) {
      if(m_heap[i]<m_heap[(i-1)/2]) {
        T temp = m_heap[(i-1)/2];
        m_heap[(i-1)/2]=m_heap[i];
        m_heap[i]=temp;
        i=(i-1)/2;
      }
      else
        break;
    }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    m_heap[0]=m_heap[m_heap.size()-1];
    typename std::vector<T>::iterator i=m_heap.end();
    --i;
    m_heap.erase(i);

    unsigned int p=0;
    while(2*p+1<m_heap.size()) {
      unsigned int child = 2*p+2;
      if(child<m_heap.size() && m_heap[child]<m_heap[child-1]) {
        
      }
      else
        child--;
      if(m_heap[child]<m_heap[p]) {
        T temp = m_heap[child];
        m_heap[child]=m_heap[p];
        m_heap[p]=temp;
        p=child;
      }
      else
        break;
    }
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    if(heap.size()>1) {
      for(unsigned int i=0; i<heap.size(); ++i) {
        if(i==0) {
          if(heap[i+1]<heap[i] || heap[i+2]<heap[i])
            return false;
        }
        else if(heap[i]<heap[(i-1)/2])
          return false;
      }
      return true;
    }
    return true;
  }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
  if(v.size()<=1)
    return;

  for(unsigned int j=1; j<=v.size(); ++j) {
    unsigned int i = j-1;
    std::cout<<i<<"------"<<j<<std::endl;
    while(i>0) {
      
      if(v[i]<v[(i-1)/2]) {
        T temp = v[(i-1)/2];
        v[(i-1)/2]=v[i];
        v[i]=temp;
        i=(i-1)/2;
      }
      else
        break;
    }
  }


  unsigned int size=v.size();
  while(size>0) {
    T temp = v[0];
    v[0]=v[size-1];
    v[size-1]=temp;
    size--;
    unsigned int p=0;
    while(2*p+1<size) {
      unsigned int child = 2*p+2;
      if(child<size && v[child]<v[child-1]) {
        
      }
      else
        child--;
      if(v[child]<v[p]) {
        T temp = v[child];
        v[child]=v[p];
        v[p]=temp;
        p=child;
      }
      else
        break;
    }
  }

}

#endif
