test_ipc(const char *service)
{
    heim_isemaphore s;
    heim_idata req, rep;
    heim_ipc ipc;
    int ret;

    ret = heim_ipc_init_context(service, &ipc);
    if (ret)
	errx(1, "heim_ipc_init_context: %d", ret);

    req.length = 0;
    req.data = NULL;

    ret = heim_ipc_call(ipc, &req, &rep, NULL);
    if (ret)
	errx(1, "heim_ipc_call: %d", ret);

    s = heim_ipc_semaphore_create(0);
    if (s == NULL)
	errx(1, "heim_ipc_semaphore_create");

    ret = heim_ipc_async(ipc, &req, s, reply);
    if (ret)
	errx(1, "heim_ipc_async: %d", ret);

    heim_ipc_semaphore_wait(s, HEIM_IPC_WAIT_FOREVER);

    heim_ipc_free_context(ipc);
}
