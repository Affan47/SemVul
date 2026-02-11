_ecore_main_fdh_poll_add(Ecore_Fd_Handler *fdh)
{
   int r = 0;

   if ((!fdh->file) && HAVE_EPOLL && epoll_fd >= 0)
     {
        r = _ecore_epoll_add(_ecore_get_epoll_fd(), fdh->fd,
                             _ecore_poll_events_from_fdh(fdh), fdh);
     }
   else
     {
#ifdef USE_G_MAIN_LOOP
        fdh->gfd.fd = fdh->fd;
        fdh->gfd.events = _gfd_events_from_fdh(fdh);
        fdh->gfd.revents = 0;
        INF("adding gpoll on %d %08x", fdh->fd, fdh->gfd.events);
        g_source_add_poll(ecore_glib_source, &fdh->gfd);
#endif
     }
   return r;
}
