ClearLogInternal(int i)
{
    if (i >= 0 && i <= max_logs && slot[i].log != &g_null_log)
        slot[i].log->Clear();
}
