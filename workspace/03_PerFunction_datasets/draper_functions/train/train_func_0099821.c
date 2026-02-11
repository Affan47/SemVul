get_fixed_heap_space (size_t s)
{
  BYTE_T *z;
  if (heap_is_fluid) {
    z = HEAP_ADDRESS (fixed_heap_pointer);
    fixed_heap_pointer += A68_ALIGN ((int) s);

    ABEND (fixed_heap_pointer >= (heap_size - MIN_MEM_SIZE), ERROR_OUT_OF_CORE, NO_TEXT);
    ABEND (((int) temp_heap_pointer - (int) fixed_heap_pointer) <= MIN_MEM_SIZE, ERROR_OUT_OF_CORE, NO_TEXT);
    return (z);
  } else {
    return (get_heap_space (s));
  }
}
