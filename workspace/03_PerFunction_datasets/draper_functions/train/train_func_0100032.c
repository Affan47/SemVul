Terminate()
{
    CALLSTACK_INFO();

    try
    {
        throw;
    }
    catch (const std::exception &e)
    {
        LOG_ERROR << "Fatal error: " << e.what() << std::endl;
    }
    catch (...)
    {
        LOG_ERROR << "Unknown fatal error." << std::endl;
    }
    LOG_ERROR << std::endl;

    Abort();
}
