setProtoDisplayAuthorization(struct protoDisplay *pdpy,
                             unsigned short authorizationNameLen,
                             const char *authorizationName)
{
    const struct AuthProtocol *a;
    Xauth *auth;

    pdpy->xdmcpAuthorization = pdpy->fileAuthorization = 0;
    if ((a = findProtocol(authorizationNameLen, authorizationName))) {
        if (a->GetXdmcpAuth) {
            (*a->GetXdmcpAuth)(pdpy, authorizationNameLen, authorizationName);
            auth = pdpy->xdmcpAuthorization;
        } else {
            auth = (*a->GetAuth)(authorizationNameLen, authorizationName);
            pdpy->fileAuthorization = auth;
            pdpy->xdmcpAuthorization = 0;
        }
        if (auth)
            debug("got %p (%d %.*s)\n", auth,
                  auth->name_length, auth->name_length, auth->name);
        else
            debug("got (null)\n");
    }
}
