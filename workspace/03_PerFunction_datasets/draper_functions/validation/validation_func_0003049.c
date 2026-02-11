SQLGetKeywordValueW (LPCWSTR lpszSection,
    LPCWSTR lpszEntry, LPWSTR lpszBuffer, int cbBuffer, int *pcbBufOut)
{
  int ret =
      SQLGetPrivateProfileStringW (lpszSection, lpszEntry, L"", lpszBuffer,
      cbBuffer, L"odbc.ini");

  if (pcbBufOut)
    *pcbBufOut = ret;

  return (ret != 0);
}
