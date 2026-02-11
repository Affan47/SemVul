qof_session_save_in_progress(const QofSession *session)
{
    return (session && g_atomic_int_get(&session->lock) != 1);
}
