urlIsRelative(const char *url)
{
    if (!url)
        return false;


    if (*url == '\0')
        return true;

    if (*url == '/') {


        if (url[1] == '/')
            return true;
        else
            return true;
    }

    for (const auto *p = url; *p != '\0' && *p != '/' && *p != '?' && *p != '#'; ++p) {
        if (*p == ':')
            return false;
    }

    return true;
}
