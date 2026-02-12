static long wsgi_alias_matches(const char *uri, const char *alias_fakename)
{


    const char *aliasp = alias_fakename, *urip = uri;

    while (*aliasp) {
        if (*aliasp == '/') {


            if (*urip != '/')
                return 0;

            do {
                ++aliasp;
            } while (*aliasp == '/');
            do {
                ++urip;
            } while (*urip == '/');
        }
        else {

            if (*urip++ != *aliasp++)
                return 0;
        }
    }


    if (aliasp[-1] != '/' && *urip != '\0' && *urip != '/')
        return 0;


    return urip - uri;
}
