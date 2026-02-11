vtkScalarsToColorsLuminanceToLuminance(
  const unsigned char *inPtr, unsigned char *outPtr, vtkIdType count,
  int numComponents)
{
  do
    {
    *outPtr++ = *inPtr;
    inPtr += numComponents;
    }
  while (--count);
}
