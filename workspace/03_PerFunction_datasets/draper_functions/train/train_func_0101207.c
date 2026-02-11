progress_warn(progress_t * progress, char *reason, ...)
{
	gchar *s;
	va_list ap;
	g_mutex_lock(progress->mutex);
	if (reason != NULL) {
		va_start(ap, reason);
		g_vasprintf(&s, reason, ap);
		free(progress->s);
		progress->s = s;
		va_end(ap);
	}
	progress->done = 2;
	g_cond_signal(progress->cond);
	g_mutex_unlock(progress->mutex);
}
