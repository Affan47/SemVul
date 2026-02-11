Module_free(Module** m)
{
  assert(m != NULL);
  if (m == NULL) {
    return;
  }
  assert((*m) != NULL);
  if ((*m) == NULL) {
    return;
  }
  Module_releaseModule(*m);
  if ((*m)->fileName) {
    free((*m)->fileName);
    (*m)->fileName = NULL;
  }
  free((*m));
  (*m) = NULL;
}
