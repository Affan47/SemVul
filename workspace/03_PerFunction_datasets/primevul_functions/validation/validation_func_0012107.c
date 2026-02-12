static void sm501_update_display(void *opaque)
{
    SM501State *s = (SM501State *)opaque;
    DisplaySurface *surface = qemu_console_surface(s->con);
    DirtyBitmapSnapshot *snap;
    int y, c_x = 0, c_y = 0;
    int crt = (s->dc_crt_control & SM501_DC_CRT_CONTROL_SEL) ? 1 : 0;
    int width = get_width(s, crt);
    int height = get_height(s, crt);
    int src_bpp = get_bpp(s, crt);
    int dst_bpp = surface_bytes_per_pixel(surface);
    int dst_depth_index = get_depth_index(surface);
    draw_line_func *draw_line = NULL;
    draw_hwc_line_func *draw_hwc_line = NULL;
    int full_update = 0;
    int y_start = -1;
    ram_addr_t offset;
    uint32_t *palette;
    uint8_t hwc_palette[3 * 3];
    uint8_t *hwc_src = NULL;

    if (!((crt ? s->dc_crt_control : s->dc_panel_control)
          & SM501_DC_CRT_CONTROL_ENABLE)) {
        return;
    }

    palette = (uint32_t *)(crt ? &s->dc_palette[SM501_DC_CRT_PALETTE -
                                                SM501_DC_PANEL_PALETTE]
                               : &s->dc_palette[0]);


    switch (src_bpp) {
    case 1:
        draw_line = draw_line8_funcs[dst_depth_index];
        break;
    case 2:
        draw_line = draw_line16_funcs[dst_depth_index];
        break;
    case 4:
        draw_line = draw_line32_funcs[dst_depth_index];
        break;
    default:
        qemu_log_mask(LOG_GUEST_ERROR, "sm501: update display"
                      "invalid control register value.\n");
        return;
    }


    if (is_hwc_enabled(s, crt)) {

        draw_hwc_line = draw_hwc_line_funcs[dst_depth_index];
        hwc_src = get_hwc_address(s, crt);
        c_x = get_hwc_x(s, crt);
        c_y = get_hwc_y(s, crt);
        get_hwc_palette(s, crt, hwc_palette);
    }


    if (s->last_width != width || s->last_height != height) {
        qemu_console_resize(s->con, width, height);
        surface = qemu_console_surface(s->con);
        s->last_width = width;
        s->last_height = height;
        full_update = 1;
    }


    if (s->do_full_update) {
        s->do_full_update = false;
        full_update = 1;
    }


    offset = get_fb_addr(s, crt);
    snap = memory_region_snapshot_and_clear_dirty(&s->local_mem_region,
              offset, width * height * src_bpp, DIRTY_MEMORY_VGA);
    for (y = 0; y < height; y++, offset += width * src_bpp) {
        int update, update_hwc;


        update_hwc = draw_hwc_line && c_y <= y && y < c_y + SM501_HWC_HEIGHT;
        update = full_update || update_hwc;

        update |= memory_region_snapshot_get_dirty(&s->local_mem_region, snap,
                                                   offset, width * src_bpp);


        if (update) {
            uint8_t *d = surface_data(surface);
            d +=  y * width * dst_bpp;


            draw_line(d, s->local_mem + offset, width, palette);


            if (update_hwc) {
                draw_hwc_line(d, hwc_src, width, hwc_palette, c_x, y - c_y);
            }

            if (y_start < 0) {
                y_start = y;
            }
        } else {
            if (y_start >= 0) {

                dpy_gfx_update(s->con, 0, y_start, width, y - y_start);
                y_start = -1;
            }
        }
    }
    g_free(snap);


    if (y_start >= 0) {
        dpy_gfx_update(s->con, 0, y_start, width, y - y_start);
    }
}
