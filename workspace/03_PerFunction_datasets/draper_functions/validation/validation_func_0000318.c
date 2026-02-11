read_config() {
    char *string_result;

    int fullscreen = fs_config_get_boolean("fullscreen");
    if (fullscreen != FS_CONFIG_NONE) {
        g_fs_emu_video_fullscreen = fullscreen;
    }

    g_fs_emu_video_fullscreen_mode = fs_config_get_string("fullscreen_mode");

    string_result = fs_config_get_string("title");
    if (string_result) {
        g_fs_emu_title = string_result;
    }
    string_result = fs_config_get_string("sub_title");
    if (string_result) {
        g_fs_emu_sub_title = string_result;
    }
}
