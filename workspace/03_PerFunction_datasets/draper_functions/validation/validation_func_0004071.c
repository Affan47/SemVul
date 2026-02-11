bind(const KResolverEntry& address)
{
  resetError();

  if (m_sockfd == -1 && !create(address))
    return false;


  if (KSocks::self()->bind(m_sockfd, address.address(), address.length()) == -1)
    {
      if (errno == EADDRINUSE)
	setError(AddressInUse);
      else if (errno == EINVAL)
	setError(AlreadyBound);
      else

	setError(NotSupported);
      return false;
    }

  return true;
}
