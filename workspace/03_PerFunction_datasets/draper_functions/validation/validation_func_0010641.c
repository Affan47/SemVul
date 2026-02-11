x_server_disconnect_session (DisplayServer *display_server, Session *session)
{
    gint vt;

    vt = display_server_get_vt (display_server);
    if (vt > 0)
    {
        session_set_tty (session, NULL);
        session_unset_env (session, "XDG_VTNR");
    }
    session_unset_env (session, "DISPLAY");
    session_set_xdisplay (session, NULL);
    session_set_remote_host_name (session, NULL);
    session_set_x_authority (session, NULL, FALSE);
}
