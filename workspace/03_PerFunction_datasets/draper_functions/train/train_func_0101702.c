ERR_error_string(unsigned long errNumber, char* buffer)
{
    static const char* msg = "Please supply a buffer for error string";

    CYASSL_ENTER("ERR_error_string");
    if (buffer) {
        SetErrorString(errNumber, buffer);
        return buffer;
    }

    return (char*)msg;
}
