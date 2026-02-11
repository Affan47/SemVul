Init()
{


    jack_log("JackClient::kBufferSizeCallback buffer_size = %ld", GetEngineControl()->fBufferSize);
    if (fBufferSize) {
        fBufferSize(GetEngineControl()->fBufferSize, fBufferSizeArg);
    }


    InitAux();


    if (!jack_tls_set(JackGlobals::fRealTimeThread, this)) {
        jack_error("Failed to set thread realtime key");
    }


    if (GetEngineControl()->fRealTime) {
        set_threaded_log_function();
        SetupRealTime();
    }

    return true;
}
