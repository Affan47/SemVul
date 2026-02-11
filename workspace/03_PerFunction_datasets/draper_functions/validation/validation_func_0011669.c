set_window_color(int idx, const char *color)
{
    XColor xcol;
    int i;

    D_X11(("idx == %d, color == \"%s\"\n", idx, NONULL(color)));

    if (!color || *color == '\0')
        return;


    if (isdigit(*color)) {
        i = atoi(color);
        if (i >= 8 && i <= 15) {
            i -= 8;
            PixColors[idx] = PixColors[minBright + i];
        } else if (i >= 0 && i <= 7) {
            PixColors[idx] = PixColors[minColor + i];
        } else {
            libast_print_warning("Color index %d is invalid.\n", i);
            return;
        }
    } else if (XParseColor(Xdisplay, cmap, color, &xcol)) {
        if (!XAllocColor(Xdisplay, cmap, &xcol)) {
            libast_print_warning("Unable to allocate \"%s\" in the color map.\n", color);
            return;
        }
        if ((idx > maxBright) && (idx < 256) && (PixColors[idx])) {
            XFreeColors(Xdisplay, cmap, (unsigned long *) &(PixColors[idx]), 1, 0);
        }
        PixColors[idx] = xcol.pixel;
    } else {
        libast_print_warning("Unable to resolve \"%s\" as a color name.\n", color);
        return;
    }
    set_colorfgbg();
    scr_touch();
    scr_refresh(DEFAULT_REFRESH);
    redraw_image(image_bg);
}
