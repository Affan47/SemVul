_fm_path_init()
{
    const char* sep, *name;
    FmPath* tmp, *parent;


    root_path = _fm_path_new_internal(NULL, "/", 1, FM_PATH_IS_LOCAL|FM_PATH_IS_NATIVE);
    home_dir = fm_get_home_dir();
    home_len = strlen(home_dir);
    while(home_dir[home_len - 1] == '/')
        --home_len;


    name = home_dir + 1;
    parent = fm_path_ref(root_path);
    while((sep = strchr(name, '/')))
    {
        int len = (sep - name);
        if(len > 0)
        {
            tmp = _fm_path_new_internal(parent, name, len, FM_PATH_IS_LOCAL|FM_PATH_IS_NATIVE);
            fm_path_unref(parent);
            parent = tmp;
        }
        name = sep + 1;
    }
    home_path = _fm_path_new_internal(parent, name, strlen(name), FM_PATH_IS_LOCAL|FM_PATH_IS_NATIVE);
    fm_path_unref(parent);

    desktop_dir = g_get_user_special_dir(G_USER_DIRECTORY_DESKTOP);
    desktop_len = strlen(desktop_dir);
    while(desktop_dir[desktop_len - 1] == '/')
        --desktop_len;


    if(G_UNLIKELY(strncmp(desktop_dir, home_dir, home_len)))
    {

        name = &desktop_dir[1];
        parent = fm_path_ref(root_path);
    }
    else
    {
        name = desktop_dir + home_len + 1;
        while (*name == '/') name++;
        if (*name == '\0')
            name = "Desktop";
        parent = fm_path_ref(home_path);
    }
    while((sep = strchr(name, '/')))
    {
        int len = (sep - name);
        if(len > 0)
        {
            tmp = _fm_path_new_internal(parent, name, len, FM_PATH_IS_LOCAL|FM_PATH_IS_NATIVE);
            fm_path_unref(parent);
            parent = tmp;
        }
        name = sep + 1;
    }
    desktop_path = _fm_path_new_internal(parent, name, strlen(name), FM_PATH_IS_LOCAL|FM_PATH_IS_NATIVE);
    fm_path_unref(parent);


    trash_root_path = _fm_path_new_internal(NULL, "trash:///", 9, FM_PATH_IS_TRASH|FM_PATH_IS_VIRTUAL|FM_PATH_IS_LOCAL);
    _fm_path_set_display_name(trash_root_path, _("Trash Can"));
    apps_root_path = _fm_path_new_internal(NULL, "menu://applications/", 20, FM_PATH_IS_VIRTUAL|FM_PATH_IS_XDG_MENU);
}
