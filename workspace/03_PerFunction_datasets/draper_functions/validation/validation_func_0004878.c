dumpStack(Stack theStack)
{
  int i;

  if (theStack == NULL)
    syserr("NULL stack not supported anymore");

  printf("[");
  for (i = 0; i < theStack->stackp; i++)
    printf("%ld ", (unsigned long) theStack->stack[i]);
  printf("]");
}
