set_horizontal_scrollbar_position(AW_window *, int pos) {
    int maxpos = int(worldsize.r-rect.r)-1;
    if (pos>maxpos) pos = maxpos;
    if (pos<0) pos = 0;
    aww->set_horizontal_scrollbar_position(pos);
}
