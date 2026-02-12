static gboolean on_server_conn_close(GIOChannel* ch, GIOCondition cond, gpointer user_data)
{


    terminate(SIGTERM);
    return TRUE;
}
