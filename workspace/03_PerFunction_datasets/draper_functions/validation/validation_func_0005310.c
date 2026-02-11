createResponder(const Request& request, const std::string& realm, const std::string& authContent)
{
    return new NotAuthenticatedResponder(*this, realm, authContent);
}
