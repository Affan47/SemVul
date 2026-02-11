fputs(const string &str)
{

    if (_stream) {
        if (::fputs(str.c_str(), _stream) != EOF) {
            return true;
        }
    }
    return false;
}
