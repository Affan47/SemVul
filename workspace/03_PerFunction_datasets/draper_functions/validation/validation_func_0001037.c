playlist_zoom_out(void)
{

    if(pl3_window_is_fullscreen())
		return;
    if ((pl3_zoom + 1) >= PLAYLIST_ZOOM_LEVELS)
        return;
    pl3_old_zoom = pl3_zoom;
    pl3_zoom++;
    playlist_zoom_level_changed();
}
