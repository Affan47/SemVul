allocateHeader (FileInfo * nested)
{


  const TranslationTableOffset startSize = 2 * sizeof (*table);
  if (table)
    return 1;
  tableUsed = sizeof (*table) + OFFSETSIZE;
  if (!(table = malloc (startSize)))
    {
      compileError (nested, "Not enough memory");
      if (table != NULL)
	free (table);
      table = NULL;
      outOfMemory ();
    }
  memset (table, 0, startSize);
  tableSize = startSize;
  return 1;
}
