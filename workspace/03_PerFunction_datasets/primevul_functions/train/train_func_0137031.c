inline void DoGetFullPathNameA(char* lpBuffer, DWORD dwSize, char* Dest)
{
    char *pPtr;


    *Dest = '\0';
    GetFullPathNameA(lpBuffer, dwSize, Dest, &pPtr);
}
