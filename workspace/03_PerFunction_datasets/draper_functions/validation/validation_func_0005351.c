createIndexEntryBinary (PR *pr, size_t *recLen)
{
  const DatabaseInfo database = pr->database;
  const IndexDesc indexDesc = getIndexDesc (database);
  FieldList f;
  char *res;

  *recLen = 2;
  res = xmalloc (2);
  appendBinaryFieldContents (&res, field_value (pr, NUMBER (pr->database)),
			     recLen);
  appendBinaryFieldContents (&res, field_value (pr, CATEGORY (pr->database)),
			     recLen);
  for (f = indexDesc->fields; f != NULL; f = f->next)
    {
      FieldIndex i = simpleFieldIndexValue (f->ent);
      size_t fieldLenOffset = *recLen;
      int valLen;


      *recLen += 2;
      valLen = format_field (i, field_value (pr, i), "", &res, recLen);
      res[fieldLenOffset + 0] = valLen / 256;
      res[fieldLenOffset + 1] = valLen & 255;


      (*recLen)++;
    }
  res[0] = *recLen / 256;
  res[1] = *recLen % 256;
  return res;
}
