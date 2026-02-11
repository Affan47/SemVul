status_done_locked (void)
{
    if (status_source)
    {
        g_source_remove (status_source);
        status_source = 0;
    }

    if (headless)
        printf ("\n");
    else if (status_window)
        gtk_widget_destroy (status_window);
}
