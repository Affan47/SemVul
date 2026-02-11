gsm_inhibitor_get_reason (GsmInhibitor *inhibitor,
                          char        **reason,
                          GError      **error)
{
        g_return_val_if_fail (GSM_IS_INHIBITOR (inhibitor), FALSE);

        if (inhibitor->priv->reason != NULL) {
                *reason = g_strdup (inhibitor->priv->reason);
        } else {
                *reason = g_strdup ("");
        }

        return TRUE;
}
