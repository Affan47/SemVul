seat_unity_set_next_session (Seat *seat, Session *session)
{
    DisplayServer *display_server;
    const gchar *id = NULL;

    if (!session)
        return;

    display_server = session_get_display_server (session);

    if (IS_X_SERVER_LOCAL (display_server))
        id = x_server_local_get_mir_id (X_SERVER_LOCAL (display_server));
    else
        id = session_get_env (session, "MIR_SERVER_NAME");

    if (id)
    {
        l_debug (seat, "Marking Mir session %s as the next session", id);
        unity_system_compositor_set_next_session (SEAT_UNITY (seat)->priv->compositor, id);
    }
    else
    {
        l_debug (seat, "Failed to work out session ID to mark");
    }

    SEAT_CLASS (seat_unity_parent_class)->set_next_session (seat, session);
}
