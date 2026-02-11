monitor_remove_watch (CkTtyIdleMonitor *monitor)
{
        if (monitor->priv->file_monitor != NULL &&
            monitor->priv->file_notify_id > 0) {
                g_debug ("Removing notify");
                ck_file_monitor_remove_notify (monitor->priv->file_monitor,
                                               monitor->priv->file_notify_id);
        }

        return FALSE;
}
