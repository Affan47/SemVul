fs_ml_show_cursor(int show, int immediate) {
    if (immediate) {
        SDL_ShowCursor(show);
    }
    else {
        post_video_event(show ? FS_ML_VIDEO_EVENT_SHOW_CURSOR :
                FS_ML_VIDEO_EVENT_HIDE_CURSOR);
    }
}
