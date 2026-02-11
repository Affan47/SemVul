_trace_connstr (
  SQLCHAR		* str,
  SQLSMALLINT		  len,
  SQLSMALLINT		* lenptr,
  int 			  output)
{
  SQLCHAR *dup;
  ssize_t length;

  if (!str)
    {
      trace_emit ("\t\t%-15.15s * 0x0\n", "SQLCHAR");
      return;
    }

  trace_emit ("\t\t%-15.15s * %p\n", "SQLCHAR", str);

  if (!output)
    return;


  if (lenptr )
    length = *lenptr;
  else
    length = len;

  if (length == SQL_NTS)
    length = STRLEN (str);


  if ((dup = (SQLCHAR *) malloc (length + 1)) == NULL)
    return;
  memcpy (dup, str, length);
  dup[length] = '\0';


  _trace_connstr_hidepwd (dup);
  trace_emit_string (dup, length, 0);
  free (dup);
}
