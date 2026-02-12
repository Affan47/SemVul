DcmSCP::~DcmSCP()
{

  if (m_assoc)
  {
    dropAndDestroyAssociation();
  }

#ifdef HAVE_WINSOCK_H
  WSACleanup();
#endif
}
