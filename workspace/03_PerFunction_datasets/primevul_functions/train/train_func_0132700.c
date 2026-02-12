gs_window_dialog_finish (GSWindow *window)
{
        g_return_if_fail (GS_IS_WINDOW (window));

        gs_debug ("Dialog finished");


        keyboard_command_finish (window);


        kill_dialog_command (window);

        if (window->priv->lock_pid > 0) {
                wait_on_child (window->priv->lock_pid);

                g_spawn_close_pid (window->priv->lock_pid);
                window->priv->lock_pid = 0;
        }


        remove_key_events (window);
}
