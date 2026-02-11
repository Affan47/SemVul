normalizeDirName(OFFilename &result,
                                         const OFFilename &dirName,
                                         const OFBool allowEmptyDirName)
{


#if defined(WIDE_CHAR_FILE_IO_FUNCTIONS) && defined(_WIN32)

    if (dirName.usesWideChars())
    {
        const wchar_t *strValue = dirName.getWideCharPointer();
        size_t strLength = (strValue == NULL) ? 0 : wcslen(strValue);
        while ((strLength > 1) && (strValue[strLength - 1] == L'\\' ))
            --strLength;

        if (allowEmptyDirName && ((strLength == 0) || ((strLength == 1) && (strValue[0] == L'.'))))
            result.clear();

        else if (!allowEmptyDirName && (strLength == 0))
            result.set(L".", OFTrue );

        else {
            wchar_t *tmpString = new wchar_t[strLength + 1];
            wcsncpy(tmpString, strValue, strLength);
            tmpString[strLength] = L'\0';
            result.set(tmpString, OFTrue );
            delete[] tmpString;
        }
    } else
#endif

    {
        const char *strValue = dirName.getCharPointer();
        size_t strLength = (strValue == NULL) ? 0 : strlen(strValue);
        while ((strLength > 1) && (strValue[strLength - 1] == PATH_SEPARATOR))
            --strLength;

        if (allowEmptyDirName && ((strLength == 0) || ((strLength == 1) && (strValue[0] == '.'))))
            result.clear();

        else if (!allowEmptyDirName && (strLength == 0))
            result.set(".");

        else
            result.set(OFString(strValue, strLength));
    }
    return result;
}
