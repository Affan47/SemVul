_eio_monitor_error(Eio_Monitor *monitor, int error)
{
   Eio_Monitor_Error *ev;

   ev = calloc(1, sizeof (Eio_Monitor_Error));
   if (!ev) return ;

   ev->monitor = monitor;
   EINA_REFCOUNT_REF(ev->monitor);
   ev->error = error;

   ecore_event_add(EIO_MONITOR_ERROR, ev, _eio_monitor_error_cleanup_cb, NULL);
}
