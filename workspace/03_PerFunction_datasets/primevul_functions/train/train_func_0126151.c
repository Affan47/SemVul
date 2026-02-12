AnyP::Uri::authority(bool requirePort) const
{
    if (authorityHttp_.isEmpty()) {


        authorityWithPort_.append(host());
        authorityHttp_ = authorityWithPort_;


        authorityWithPort_.appendf(":%u",port());
        if (port() != getScheme().defaultPort())
            authorityHttp_ = authorityWithPort_;
    }

    return requirePort ? authorityWithPort_ : authorityHttp_;
}
