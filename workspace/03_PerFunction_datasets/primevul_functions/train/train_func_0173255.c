PLT_HttpServer::Stop()
{

    if (m_Aborted || !m_Running) NPT_CHECK_WARNING(NPT_ERROR_INVALID_STATE);


    m_TaskManager->Abort();

    m_Running = false;
    m_Aborted = true;

    return NPT_SUCCESS;
}
