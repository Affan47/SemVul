gs_window_cancel_unlock_request (GSWindow  *window)
{


        g_return_if_fail (GS_IS_WINDOW (window));

        popdown_dialog (window);
}
