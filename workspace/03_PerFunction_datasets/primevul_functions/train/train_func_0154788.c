e_util_gthread_id (GThread *thread)
{
#if GLIB_SIZEOF_VOID_P == 8

	return (guint64) thread;
#else
	return (gint) thread;
#endif
}
