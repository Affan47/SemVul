fs_emu_video_buffer_init(int width, int height, int bpp) {

    if (g_video_buffers_initialized) {
        return 0;
    }
    if (bpp == 0) {
        bpp = g_fs_emu_video_bpp;
    }
    for (int i = 0; i < 3; i++) {
        g_video_buffers[i].width = width;
        g_video_buffers[i].height = height;
        g_video_buffers[i].bpp = bpp;
        g_video_buffers[i].size = width * height * bpp;
        g_video_buffers[i].data = fs_malloc0(g_video_buffers[i].size);

        g_video_buffers[i].aspect = 1.0;


    }
    g_video_buffers_mutex = fs_mutex_create();
    g_video_buffers_initialized = 1;
    return 1;
}
