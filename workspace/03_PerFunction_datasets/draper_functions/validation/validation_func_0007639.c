load(gpsimObject *file, gpsimObject *pProcessorType)
{
  cout << endl;

  char s1[256];
  file->toString(s1, sizeof(s1));

  if (pProcessorType) {
    char s2[256];
    pProcessorType->toString(s2, sizeof(s2));
    return load1(s1, s2);
  }
  return load1(s1,0);
}
