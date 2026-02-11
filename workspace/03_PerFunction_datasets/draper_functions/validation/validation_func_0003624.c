vector_print(numint_t* q, size_t size)
{
  size_t i;
  printf("vector %ld: ", (long)size);
  for (i=0; i<size; i++){
    numint_print(q[i]); printf(" ");
  }
  printf("\n");
}
