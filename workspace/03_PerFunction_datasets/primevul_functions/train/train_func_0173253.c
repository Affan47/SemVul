PLT_HttpServer::Start()
{
    NPT_Result res = NPT_FAILURE;


    if (m_Running || m_Aborted) NPT_CHECK_WARNING(NPT_ERROR_INVALID_STATE);


    if (m_Port) {
        res = SetListenPort(m_Port, m_ReuseAddress);

        if (NPT_FAILED(res) && !m_AllowRandomPortOnBindFailure) {
            NPT_CHECK_SEVERE(res);
        }
    }


    if (!m_Port || NPT_FAILED(res)) {
        int retries = 100;
        do {
            int random = NPT_System::GetRandomInteger();
            int port = (unsigned short)(1024 + (random % 1024));
            if (NPT_SUCCEEDED(SetListenPort(port, m_ReuseAddress))) {
                break;
            }
        } while (--retries > 0);

        if (retries == 0) NPT_CHECK_SEVERE(NPT_FAILURE);
    }


    m_Port = m_BoundPort;


    if (m_TaskManager->GetMaxTasks() > 20) {
        m_Socket.Listen(m_TaskManager->GetMaxTasks());
    }


    PLT_HttpListenTask *task = new PLT_HttpListenTask(this, &m_Socket, false);
    NPT_CHECK_SEVERE(m_TaskManager->StartTask(task));

    NPT_SocketInfo info;
    m_Socket.GetInfo(info);
    NPT_LOG_INFO_2("HttpServer listening on %s:%d",
        (const char*)info.local_address.GetIpAddress().ToString(),
        m_Port);

    m_Running = true;
    return NPT_SUCCESS;
}
