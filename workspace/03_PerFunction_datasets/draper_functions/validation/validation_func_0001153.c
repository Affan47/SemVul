SendTrackerRequest(const char *event)
{
   if(!t_session)
      return;

   xstring request(GetURL());
   request.appendf("info_hash=%s",url::encode(GetInfoHash(),URL_PATH_UNSAFE).get());
   request.appendf("&peer_id=%s",url::encode(GetMyPeerId(),URL_PATH_UNSAFE).get());
   request.appendf("&port=%d",GetPort());
   request.appendf("&uploaded=%llu",GetTotalSent());
   request.appendf("&downloaded=%llu",GetTotalRecv());
   if(HasMetadata())
      request.appendf("&left=%llu",GetTotalLeft());
   request.append("&compact=1&no_peer_id=1");
   if(event)
      request.appendf("&event=%s",event);
   const char *ip=ResMgr::Query("torrent:ip",0);
   if(ip && ip[0])
      request.appendf("&ip=%s",ip);

#if INET6
   int port=Torrent::GetPortIPv4();
   int port_ipv6=Torrent::GetPortIPv6();
   const char *ipv6=ResMgr::Query("torrent:ipv6",0);
   if(port && ip && ip[0])
      request.appendf("&ipv4=%s:%d",ip,port);
   if(port_ipv6)
      request.appendf("&ipv6=[%s]:%d",ipv6&&ipv6[0]?ipv6:Torrent::GetAddressIPv6(),port_ipv6);
#endif

   int numwant=GetWantedPeersCount();
   if(numwant>=0)
      request.appendf("&numwant=%d",numwant);
   const xstring& my_key=GetMyKey();
   if(my_key)
      request.appendf("&key=%s",my_key.get());
   const char *tracker_id=GetTrackerId();
   if(tracker_id)
      request.appendf("&trackerid=%s",url::encode(tracker_id,URL_PATH_UNSAFE).get());
   LogSend(4,request);
   t_session->Open(url::path_ptr(request),FA::RETRIEVE);
   t_session->SetFileURL(request);
   tracker_reply=new IOBufferFileAccess(t_session);
}
