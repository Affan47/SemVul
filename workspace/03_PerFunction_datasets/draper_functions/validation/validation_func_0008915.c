user_action(client_t *c, int x, int y, int button)
{
    if (x >= c->geom.w - frame_height(c) && y <= frame_height(c)) {
        switch (button) {
            case Button1: iconify_client(c); break;
            case Button2: resize_client(c); break;
            case Button3: send_wm_delete(c); break;
            case Button4: zoom_client(c); break;
            case Button5: unzoom_client(c); break;
        }
    } else {
        switch (button) {
            case Button1: XRaiseWindow(dpy, c->frame); break;
            case Button2: move_client(c); break;
            case Button3: XLowerWindow(dpy, c->frame); break;
            case Button4: shade_client(c); break;
            case Button5: unshade_client(c); break;
        }
    }
}
