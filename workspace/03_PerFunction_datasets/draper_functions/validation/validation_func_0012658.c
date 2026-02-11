start_timeout_func (Camera *camera, unsigned int timeout,
		    CameraTimeoutFunc func, void __unused__ *data)
{
	pthread_t tid;
	ThreadData *td;

	td = malloc (sizeof (ThreadData));
	if (!td)
		return 0;
	memset (td, 0, sizeof (ThreadData));
	td->camera = camera;
	td->timeout = timeout;
	td->func = func;

	pthread_create (&tid, NULL, thread_func, td);

	return (tid);
}
