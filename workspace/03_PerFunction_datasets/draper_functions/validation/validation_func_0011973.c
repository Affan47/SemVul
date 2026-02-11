check_stopped (DisplayManager *manager)
{
    if (manager->priv->stopping &&
        !manager->priv->stopped &&
        g_list_length (manager->priv->seats) == 0)
    {
        manager->priv->stopped = TRUE;
        g_debug ("Display manager stopped");
        g_signal_emit (manager, signals[STOPPED], 0);
    }
}
