SQLReadFileDSN (LPCSTR lpszFileName, LPCSTR lpszAppName, LPCSTR lpszKeyName,
    LPSTR lpszString, WORD cbString, WORD * pcbString)
{
  BOOL retcode = FALSE;
  WORD len = 0, i;
  char filename[1024];


  CLEAR_ERROR ();

  if (!lpszString || !cbString)
    {
      PUSH_ERROR (ODBC_ERROR_INVALID_BUFF_LEN);
      goto quit;
    }

  if (!lpszAppName && lpszKeyName)
    {
      PUSH_ERROR (ODBC_ERROR_INVALID_REQUEST_TYPE);
      goto quit;
    }


  if (lpszFileName)
    {
      _iodbcdm_getdsnfile (lpszFileName, filename, sizeof (filename));
      len =
	  GetPrivateProfileString (lpszAppName, lpszKeyName, "", lpszString,
	  cbString, filename);
      if (numerrors == -1)
	retcode = TRUE;
      goto quit;
    }

  PUSH_ERROR (ODBC_ERROR_INVALID_PATH);
  goto quit;

quit:
  for (i = 0; i < len; i++)
    if (!lpszString[i])
      lpszString[i] = ';';

  if (pcbString)
    *pcbString = len;

  if (len == cbString - 1)
    {
      PUSH_ERROR (ODBC_ERROR_OUTPUT_STRING_TRUNCATED);
      retcode = FALSE;
    }

  return retcode;
}
