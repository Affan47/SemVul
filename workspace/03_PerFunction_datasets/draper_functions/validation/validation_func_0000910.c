vector_resized(vector* p, size_t size, void dtor(void*))
{
  size_t i;
  if(size < p->size)
  {
    for(i = size; i < p->size; i++)
    {
      dtor(&((char*)(p->data))[i * p->typesize]);
    }
  }
  return vector_resize(p, size);
}
