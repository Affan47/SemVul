urlCheckRequest(const HttpRequest * r)
{
    int rc = 0;


    if (r->method == Http::METHOD_CONNECT)
        return 1;


    if (r->method == Http::METHOD_OPTIONS || r->method == Http::METHOD_TRACE)
        return (r->header.getInt64(Http::HdrType::MAX_FORWARDS) == 0 || r->url.path() != AnyP::Uri::Asterisk());

    if (r->method == Http::METHOD_PURGE)
        return 1;


    switch (r->url.getScheme()) {

    case AnyP::PROTO_URN:

    case AnyP::PROTO_HTTP:

    case AnyP::PROTO_CACHE_OBJECT:
        rc = 1;
        break;

    case AnyP::PROTO_FTP:

        if (r->method == Http::METHOD_PUT)
            rc = 1;

    case AnyP::PROTO_GOPHER:

    case AnyP::PROTO_WAIS:

    case AnyP::PROTO_WHOIS:
        if (r->method == Http::METHOD_GET)
            rc = 1;
        else if (r->method == Http::METHOD_HEAD)
            rc = 1;

        break;

    case AnyP::PROTO_HTTPS:
#if USE_OPENSSL
        rc = 1;
#elif USE_GNUTLS
        rc = 1;
#else


        rc = 0;
#endif
        break;

    default:
        break;
    }

    return rc;
}
