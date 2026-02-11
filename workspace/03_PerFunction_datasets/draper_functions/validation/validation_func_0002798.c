JimParseIpAddress(Jim_Interp *interp, const char *hostport, union sockaddr_any *sa, int *salen)
{


    char *sthost = NULL;
    const char *stport;
    int ret = JIM_OK;

    stport = strrchr(hostport, ':');
    if (!stport) {

        stport = hostport;
        sthost = Jim_StrDup("0.0.0.0");
    }
    else {
        sthost = Jim_StrDupLen(hostport, stport - hostport);
        stport++;
    }

    {
#ifdef HAVE_GETADDRINFO
        struct addrinfo req;
        struct addrinfo *ai;
        memset(&req, '\0', sizeof(req));
        req.ai_family = PF_INET;

        if (getaddrinfo(sthost, NULL, &req, &ai)) {
            ret = JIM_ERR;
        }
        else {
            memcpy(&sa->sin, ai->ai_addr, ai->ai_addrlen);
            *salen = ai->ai_addrlen;
            freeaddrinfo(ai);
        }
#else
        struct hostent *he;

        ret = JIM_ERR;

        if ((he = gethostbyname(sthost)) != NULL) {
            if (he->h_length == sizeof(sa->sin.sin_addr)) {
                *salen = sizeof(sa->sin);
                sa->sin.sin_family= he->h_addrtype;
                memcpy(&sa->sin.sin_addr, he->h_addr, he->h_length);
                ret = JIM_OK;
            }
        }
#endif

        sa->sin.sin_port = htons(atoi(stport));
    }
    Jim_Free(sthost);

    if (ret != JIM_OK) {
        Jim_SetResultFormatted(interp, "Not a valid address: %s", hostport);
    }

    return ret;
}
