WlmActivityManager::~WlmActivityManager()


{

  delete[] supportedAbstractSyntaxes[0];
  delete[] supportedAbstractSyntaxes[1];
  delete[] supportedAbstractSyntaxes;

#ifdef HAVE_WINSOCK_H
  WSACleanup();
#endif
}
