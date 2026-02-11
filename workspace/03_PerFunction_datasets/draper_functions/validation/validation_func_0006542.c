set_width(unsigned short width)
{
    unsigned short height = TERM_WINDOW_GET_REPORTED_ROWS();

    if (width != TERM_WINDOW_GET_REPORTED_COLS()) {
        width = szHint.base_width + width * TermWin.fwidth;
        height = szHint.base_height + height * TermWin.fheight;

        resize_parent(width, height);
        handle_resize(width, height);
    }
}
