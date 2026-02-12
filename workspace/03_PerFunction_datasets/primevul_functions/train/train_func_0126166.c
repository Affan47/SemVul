AnyP::Uri::addRelativePath(const char *relUrl)
{

    if (getScheme() == AnyP::PROTO_URN)
        return;


    const auto lastSlashPos = path_.rfind('/');

    const auto relUrlLength = strlen(relUrl);
    if (lastSlashPos == SBuf::npos) {

        path_.reserveCapacity(1 + relUrlLength);
        path_.assign("/", 1);
    } else {

        path_.reserveCapacity(lastSlashPos + 1 + relUrlLength);
        path_.chop(0, lastSlashPos+1);
    }
    path_.append(relUrl, relUrlLength);
}
