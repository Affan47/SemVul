fs_emu_init_2(int options) {
    fs_log("fs_emu_init_2\n");

#ifdef USE_SDL
    fs_emu_log("initializing SDL\n");
    SDL_Init(SDL_INIT_EVERYTHING);
#endif

    fs_emu_hud_init_after_config();

    fs_emu_theme_init();

#ifdef WITH_NETPLAY

    fs_emu_netplay_init();
#endif

    if (options & FS_EMU_INIT_VIDEO) {
        fs_emu_video_init();
    }

    fs_emu_init_render();


    fs_emu_set_overlay_state(FS_EMU_TOP_LEFT_OVERLAY, 1);
    fs_emu_set_overlay_state(FS_EMU_TOP_RIGHT_OVERLAY, 1);
    fs_emu_set_overlay_state(FS_EMU_BOTTOM_RIGHT_OVERLAY, 1);
    fs_emu_set_overlay_state(FS_EMU_BOTTOM_LEFT_OVERLAY, 1);

    fs_emu_log("calling fs_ml_init_2\n");
    fs_ml_init_2();
    fs_ml_set_quit_function(on_quit);

    fs_emu_log("read config\n");
    read_config();

    if (options & FS_EMU_INIT_INPUT) {
        fs_emu_input_init();
    }
    if (options & FS_EMU_INIT_AUDIO) {
        fs_emu_audio_init();
    }

    fs_ml_video_set_update_function(fs_emu_video_update_function);
    fs_ml_video_set_render_function(fs_emu_video_render_function);
    fs_ml_video_set_post_render_function(fs_emu_video_after_update);

    if (options & FS_EMU_INIT_VIDEO) {
        char *title;
        if (fs_emu_get_title()) {
            title = fs_strdup(fs_emu_get_title());
        }
        else {
            title = fs_strdup("Emulator");
        }
        if (fs_emu_get_sub_title()) {
            char *temp = title;

            title = fs_strdup_printf("%s %c%c %s", temp, 0xC2, 0xB7,
                    fs_emu_get_sub_title());
            free(temp);
        }
        fs_ml_video_create_window(title);
        free(title);
    }
}
