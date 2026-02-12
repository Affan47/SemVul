void MemoryBuffer<T, SIZE, Allocator>::grow(std::size_t size) {
  std::size_t new_capacity = this->capacity_ + this->capacity_ / 2;
  if (size > new_capacity)
      new_capacity = size;
#if FMT_USE_ALLOCATOR_TRAITS
  T *new_ptr =
      std::allocator_traits<Allocator>::allocate(*this, new_capacity, FMT_NULL);
#else
  T *new_ptr = this->allocate(new_capacity, FMT_NULL);
#endif

  std::uninitialized_copy(this->ptr_, this->ptr_ + this->size_,
                          make_ptr(new_ptr, new_capacity));
  std::size_t old_capacity = this->capacity_;
  T *old_ptr = this->ptr_;
  this->capacity_ = new_capacity;
  this->ptr_ = new_ptr;


  if (old_ptr != data_)
    Allocator::deallocate(old_ptr, old_capacity);
}
