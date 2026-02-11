startAvahi(const char *pHWStr, const char *pServerName, int pPort)
{
  int tMaxServerName = 25;
  int tPid = fork();
  if(tPid == 0)
  {
    char tName[100 + HWID_SIZE + 3];
    if(strlen(pServerName) > tMaxServerName)
    {
      slog(LOG_INFO,"Hey dog, we see you like long server names, "
              "so we put a strncat in our command so we don't buffer overflow, while you listen to your flow.\n"
              "We just used the first %d characters.  Pick something shorter if you want\n", tMaxServerName);
    }

    tName[0] = '\0';
    char tPort[SERVLEN];
    sprintf(tPort, "%d", pPort);
    strcat(tName, pHWStr);
    strcat(tName, "@");
    strncat(tName, pServerName, tMaxServerName);
    slog(AVAHI_LOG_LEVEL, "Avahi/DNS-SD Name: %s\n", tName);

    execlp("avahi-publish-service", "avahi-publish-service", tName,
         "_raop._tcp", tPort, "tp=UDP","sm=false","sv=false","ek=1","et=0,1",
         "cn=0,1","ch=2","ss=16","sr=44100","pw=false","vn=3","txtvers=1", NULL);
    execlp("dns-sd", "dns-sd", "-R", tName,
         "_raop._tcp", ".", tPort, "tp=UDP","sm=false","sv=false","ek=1","et=0,1",
         "cn=0,1","ch=2","ss=16","sr=44100","pw=false","vn=3","txtvers=1", NULL);
    execlp("mDNSPublish", "mDNSPublish", tName,
         "_raop._tcp", tPort, "tp=UDP","sm=false","sv=false","ek=1","et=0,1",
         "cn=0,1","ch=2","ss=16","sr=44100","pw=false","vn=3","txtvers=1", NULL);
    if(errno == -1) {
            perror("error");
    }

    slog(LOG_INFO, "Bad error... couldn't find or failed to run: avahi-publish-service OR dns-sd OR mDNSPublish\n");
    exit(1);
  }
  else
  {
    slog(LOG_DEBUG_VV, "Avahi/DNS-SD started on PID: %d\n", tPid);
  }
  return tPid;
}
