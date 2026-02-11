ck_seat_get_sessions (CkSeat         *seat,
                      GPtrArray     **sessions,
                      GError        **error)
{
        g_return_val_if_fail (CK_IS_SEAT (seat), FALSE);

        if (sessions == NULL) {
                return FALSE;
        }

        *sessions = g_ptr_array_new ();
        g_hash_table_foreach (seat->priv->sessions, (GHFunc)listify_session_ids, sessions);

        return TRUE;
}
