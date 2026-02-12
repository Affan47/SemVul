AnyP::Uri::parse(const HttpRequestMethod& method, const SBuf &rawUrl)
{
    try {

        LOCAL_ARRAY(char, login, MAX_URL);
        LOCAL_ARRAY(char, foundHost, MAX_URL);
        LOCAL_ARRAY(char, urlpath, MAX_URL);
        char *t = NULL;
        char *q = NULL;
        int foundPort;
        int l;
        int i;
        const char *src;
        char *dst;
        foundHost[0] = urlpath[0] = login[0] = '\0';

        if ((l = rawUrl.length()) + Config.appendDomainLen > (MAX_URL - 1)) {
            debugs(23, DBG_IMPORTANT, MYNAME << "URL too large (" << l << " bytes)");
            return false;
        }

        if ((method == Http::METHOD_OPTIONS || method == Http::METHOD_TRACE) &&
                Asterisk().cmp(rawUrl) == 0) {

            setScheme(AnyP::PROTO_HTTP, nullptr);
            port(getScheme().defaultPort());
            path(Asterisk());
            return true;
        }

        Parser::Tokenizer tok(rawUrl);
        AnyP::UriScheme scheme;

        if (method == Http::METHOD_CONNECT) {


            foundPort = 443;


            auto B = tok.buf();
            const char *url = B.c_str();

            if (sscanf(url, "[%[^]]]:%d", foundHost, &foundPort) < 1)
                if (sscanf(url, "%[^:]:%d", foundHost, &foundPort) < 1)
                    return false;

        } else {

            scheme = uriParseScheme(tok);

            if (scheme == AnyP::PROTO_NONE)
                return false;

            if (scheme == AnyP::PROTO_URN) {
                parseUrn(tok);
                return true;
            }


            static const SBuf doubleSlash("//");
            if (!tok.skip(doubleSlash))
                return false;

            auto B = tok.remaining();
            const char *url = B.c_str();


            src = url;
            i = 0;


            for (dst = foundHost; i < l && *src != '/' && *src != '?' && *src != '#' && *src != '\0' && !xisspace(*src); ++i, ++src, ++dst) {
                *dst = *src;
            }


            if (i > l)
                return false;
            *dst = '\0';


            if (*src != '/') {

                urlpath[0] = '/';
                dst = &urlpath[1];
            } else {
                dst = urlpath;
            }

            for (; i < l && *src != '\r' && *src != '\n' && *src != '\0'; ++i, ++src, ++dst) {
                *dst = *src;
            }


            if (i > l)
                return false;
            *dst = '\0';

            foundPort = scheme.defaultPort();


            t = strrchr(foundHost, '@');
            if (t != NULL) {
                strncpy((char *) login, (char *) foundHost, sizeof(login)-1);
                login[sizeof(login)-1] = '\0';
                t = strrchr(login, '@');
                *t = 0;
                strncpy((char *) foundHost, t + 1, sizeof(foundHost)-1);
                foundHost[sizeof(foundHost)-1] = '\0';

                rfc1738_unescape(login);
            }


            if (*foundHost == '[') {

                dst = foundHost;

                src = foundHost;
                ++src;
                l = strlen(foundHost);
                i = 1;
                for (; i < l && *src != ']' && *src != '\0'; ++i, ++src, ++dst) {
                    *dst = *src;
                }


                *dst = '\0';
                ++dst;


                while (*dst != '\0' && *dst != ':')
                    ++dst;
                t = dst;
            } else {
                t = strrchr(foundHost, ':');

                if (t != strchr(foundHost,':') ) {


                    t = NULL;
                }
            }


            if (scheme != AnyP::PROTO_NONE && foundHost[0] == '\0') {
                debugs(23, DBG_IMPORTANT, "SECURITY ALERT: Missing hostname in URL '" << url << "'. see access.log for details.");
                return false;
            }

            if (t && *t == ':') {
                *t = '\0';
                ++t;
                foundPort = atoi(t);
            }
        }

        for (t = foundHost; *t; ++t)
            *t = xtolower(*t);

        if (stringHasWhitespace(foundHost)) {
            if (URI_WHITESPACE_STRIP == Config.uri_whitespace) {
                t = q = foundHost;
                while (*t) {
                    if (!xisspace(*t)) {
                        *q = *t;
                        ++q;
                    }
                    ++t;
                }
                *q = '\0';
            }
        }

        debugs(23, 3, "Split URL '" << rawUrl << "' into proto='" << scheme.image() << "', host='" << foundHost << "', port='" << foundPort << "', path='" << urlpath << "'");

        if (Config.onoff.check_hostnames &&
                strspn(foundHost, Config.onoff.allow_underscore ? valid_hostname_chars_u : valid_hostname_chars) != strlen(foundHost)) {
            debugs(23, DBG_IMPORTANT, MYNAME << "Illegal character in hostname '" << foundHost << "'");
            return false;
        }

        if (!urlAppendDomain(foundHost))
            return false;


        while ((l = strlen(foundHost)) > 0 && foundHost[--l] == '.')
            foundHost[l] = '\0';


        if (strstr(foundHost, "..") || *foundHost == '.') {
            debugs(23, DBG_IMPORTANT, MYNAME << "Illegal hostname '" << foundHost << "'");
            return false;
        }

        if (foundPort < 1 || foundPort > 65535) {
            debugs(23, 3, "Invalid port '" << foundPort << "'");
            return false;
        }

#if HARDCODE_DENY_PORTS


        if (foundPort == 7 || foundPort == 9 || foundPort == 19) {
            debugs(23, DBG_CRITICAL, MYNAME << "Deny access to port " << foundPort);
            return false;
        }
#endif

        if (stringHasWhitespace(urlpath)) {
            debugs(23, 2, "URI has whitespace: {" << rawUrl << "}");

            switch (Config.uri_whitespace) {

            case URI_WHITESPACE_DENY:
                return false;

            case URI_WHITESPACE_ALLOW:
                break;

            case URI_WHITESPACE_ENCODE:
                t = rfc1738_escape_unescaped(urlpath);
                xstrncpy(urlpath, t, MAX_URL);
                break;

            case URI_WHITESPACE_CHOP:
                *(urlpath + strcspn(urlpath, w_space)) = '\0';
                break;

            case URI_WHITESPACE_STRIP:
            default:
                t = q = urlpath;
                while (*t) {
                    if (!xisspace(*t)) {
                        *q = *t;
                        ++q;
                    }
                    ++t;
                }
                *q = '\0';
            }
        }

        setScheme(scheme);
        path(urlpath);
        host(foundHost);
        userInfo(SBuf(login));
        port(foundPort);
        return true;

    } catch (...) {
        debugs(23, 2, "error: " << CurrentException << " " << Raw("rawUrl", rawUrl.rawContent(), rawUrl.length()));
        return false;
    }
}
