#ifndef unordered_map_insert_iterator_h
#define unordered_map_insert_iterator_h

#include <iterator>
#include <memory>
#include <iostream>


  /**
   *  Synopsis:  Turns assignment into insertion.
   *
   *  An output iterator constructed from a container-of-T. Methods:
   * 
   *   unordered_map_insert_iterator<C>& unordered_map_insert_iterator::operator(const T&)
   *   unordered_map_insert_iterator<C>& unordered_map_insert_iterator::operator(T&&)
   * 
   *  calls C::insert_or_copy(T);
   *
   *  Tip:  Use unordered_map_inserter(C) function to create these iterators
  */
template<typename _Container> class unordered_map_insert_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void> {
    protected:
      _Container* container;

    public:
      /// A nested typedef for the type of whatever container you used.
      using container_type = _Container;

      /// The only way to create this %iterator is with a container.
      explicit
      unordered_map_insert_iterator(_Container& __x) : container(&__x)
      { 
      }

      /**
       *  @param  __value  An instance of whatever type
       *                 container_type::const_reference is; presumably a
       *                 reference-to-const T for container<T>.
       *  @return  This %iterator, for chained operations.
       *
       *  This kind of %iterator doesn't really have a @a position in the
       *  container (you can think of the position as being permanently at
       *  the end, if you like).  Assigning a value to the %iterator will
       *  always append the value to the end of the container.
      */

/*  Kurt commented out
#if __cplusplus < 201103L
      unordered_map_insert_iterator&
      operator=(typename _Container::const_reference __value)
      {
	container->insert(__value);
	return *this;
      }

#else
      unordered_map_insert_iterator&
      operator=(const typename _Container::value_type& __value)
      {
	container->insert(__value);
	return *this;
      }

      unordered_map_insert_iterator&
      operator=(typename _Container::value_type&& __value)
      {
	container->insert(std::move(__value));
	return *this;
      }
#endif
*/
      // Kurt added next two methods  
      /*
       _Container::value_type is wrong because it is 
        
          typedef std::pair<const Key, Ty> value_type;
       * 
       We want std::pair<_Container::key_type, _Container::mapped_type>
       
       */
      unordered_map_insert_iterator&
      operator=(const std::pair<typename _Container::key_type, typename _Container::mapped_type>& __value) 
      {
        // Debug
      //--  std::cout << "first = "  << __value.first << ". second = " << __value.second << std::endl; 
	container->insert_or_assign(__value.first, __value.second); 
	return *this;
      }
      
      unordered_map_insert_iterator&
      operator=(std::pair<typename _Container::key_type, typename _Container::mapped_type>&& __value)
      {
       // Debug
       //-- std::cout << "first = "  << __value.first << ". second = " << __value.second << std::endl;    
	container->insert_or_assign(std::move(__value.first), std::move(__value.second)); 
	return *this;
      }
      
      /// Simply returns *this.
      unordered_map_insert_iterator&
      operator*()
      { return *this; }

      /// Simply returns *this.  (This %iterator does not @a move.)
      unordered_map_insert_iterator&
      operator++()
      { return *this; }

      /// Simply returns *this.  (This %iterator does not @a move.)
      unordered_map_insert_iterator
      operator++(int)
      { return *this; }
    };

/**
   *  @param  __x  A container of arbitrary type.
   *  @return  An instance of back_insert_iterator working on @p __x.
   *
   *  This wrapper function helps in creating back_insert_iterator instances.
   *  Typing the name of the %iterator requires knowing the precise full
   *  type of the container, which can be tedious and impedes generic
   *  programming.  Using this function lets you take advantage of automatic
   *  template parameter deduction, making the compiler match the correct
   *  types for you.
  */
 
template< class Container >
unordered_map_insert_iterator<Container> unordered_map_inserter( Container& c )
{
    return unordered_map_insert_iterator<Container>(c);
}
#endif
