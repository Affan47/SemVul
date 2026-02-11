setLog(const char* value)
{
    doLog = boolValue(value);

    doDebug = 0;
    if (value && strncmp(value,"debug",5) == 0) {
        doDebug = 1;
    }
}
