inline void DoGetFullPathNameW(WCHAR* lpBuffer, DWORD dwSize, WCHAR* Dest)
{
    WCHAR *pPtr;


    *Dest = '\0';
    GetFullPathNameW(lpBuffer, dwSize, Dest, &pPtr);
}
