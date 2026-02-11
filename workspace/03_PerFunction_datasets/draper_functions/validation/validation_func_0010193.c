st_callback(stonith_t * st, stonith_event_t * e)
{
    if (st->state == stonith_disconnected) {
        crm_exit(ENOTCONN);
    }

    crm_notice("Operation %s requested by %s %s for peer %s.  %s reported: %s (ref=%s)",
               e->operation, e->origin, e->result == pcmk_ok ? "completed" : "failed",
               e->target, e->executioner ? e->executioner : "<none>",
               pcmk_strerror(e->result), e->id);

    if (expected_notifications) {
        expected_notifications--;
    }
}
