on_launch_error(GAppLaunchContext* ctx, GError* err,
                                FmPath* path, gpointer user_data)
{
    LaunchData* data = (LaunchData*)user_data;


    if(err->domain == G_IO_ERROR)
    {
        if(path && err->code == G_IO_ERROR_NOT_MOUNTED)
        {
            if(fm_mount_path(data->parent, path, TRUE))
                return FALSE;
        }
        else if(err->code == G_IO_ERROR_FAILED_HANDLED)
            return TRUE;
    }
    fm_show_error(data->parent, NULL, err->message);
    return TRUE;
}
