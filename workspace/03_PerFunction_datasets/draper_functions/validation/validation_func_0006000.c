max_flushed_epoch()
{
    kvepoch_t mfe = 0, ge = global_log_epoch;
    for (int i = 0; i < nlogger; ++i) {
        loginfo& log = logs->log(i);
        kvepoch_t fe = log.quiescent() ? ge : log.flushed_epoch();
        if (!mfe || fe < mfe)
            mfe = fe;
    }
    return mfe;
}
