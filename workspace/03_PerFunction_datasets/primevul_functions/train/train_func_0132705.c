kill_dialog_command (GSWindow *window)
{


        if (window->priv->lock_pid > 0) {
                signal_pid (window->priv->lock_pid, SIGTERM);
        }
}
