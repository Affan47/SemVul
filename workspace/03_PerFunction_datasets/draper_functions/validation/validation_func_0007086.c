CanReadFile(const char *filename)
{
  int result;
  FILE *fp = fopen(filename, "r");
  if (fp == NULL) return 0;

  int numParts, numPts, numPolys, numEdges;
  result = fscanf(fp, "%d %d %d %d", &numParts, &numPts, &numPolys, &numEdges);
  if ((result < 4) || (numParts < 1) || (numPts < 1) || (numPolys < 1))
    {
    fclose(fp);
    return 0;
    }

  for (int part = 0; part < numParts; part++)
    {
    int partStart, partEnd;
    result = fscanf(fp, "%d %d", &partStart, &partEnd);
    if (   (result < 2)
        || (partStart < 1) || (partStart > numPolys)
        || (partEnd < 1) || (partEnd > numPolys)
        || (partStart >= partEnd) )
      {
      fclose(fp);
      return 0;
      }
    }

  fclose(fp);
  return 1;
}
