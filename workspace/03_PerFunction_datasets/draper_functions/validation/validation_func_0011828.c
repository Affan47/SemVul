setScriptLibraryErrorFile(char const* fname, char const* libName)
{
    m_scriptLibName = libName;

    if (scriptErrLogFile)
        fclose(scriptErrLogFile);

    if (!fname)
    {
        scriptErrLogFile = NULL;
        return;
    }

    std::string fileName = m_logsDir;
    fileName.append(fname);
    scriptErrLogFile = fopen(fileName.c_str(), "a");
}
