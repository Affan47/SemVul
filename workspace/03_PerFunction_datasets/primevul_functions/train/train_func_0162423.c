compileTranslationTable (const char *tableList)
{
  char **tableFiles;
  char **subTable;
  errorCount = warningCount = fileCount = 0;
  table = NULL;
  characterClasses = NULL;
  ruleNames = NULL;
  if (tableList == NULL)
    return NULL;
  if (!opcodeLengths[0])
    {
      TranslationTableOpcode opcode;
      for (opcode = 0; opcode < CTO_None; opcode++)
	opcodeLengths[opcode] = strlen (opcodeNames[opcode]);
    }
  allocateHeader (NULL);


  compileString ("space \\s 0");
  compileString ("noback sign \\x0000 0");
  compileString ("space \\x00a0 a unbreakable space");
  compileString ("space \\x001b 1b escape");
  compileString ("space \\xffff 123456789abcdef ENDSEGMENT");


  if (!(tableFiles = resolveTable (tableList, NULL)))
    {
      errorCount++;
      goto cleanup;
    }
  for (subTable = tableFiles; *subTable; subTable++)
    if (!compileFile (*subTable))
      goto cleanup;


cleanup:
  if (characterClasses)
    deallocateCharacterClasses ();
  if (ruleNames)
    deallocateRuleNames ();
  if (warningCount)
    lou_logPrint ("%d warnings issued", warningCount);
  if (!errorCount)
    {
      setDefaults ();
      table->tableSize = tableSize;
      table->bytesUsed = tableUsed;
    }
  else
    {
      lou_logPrint ("%d errors found.", errorCount);
      if (table)
	free (table);
      table = NULL;
    }
  return (void *) table;
}
