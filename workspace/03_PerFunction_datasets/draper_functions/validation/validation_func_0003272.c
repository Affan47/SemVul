tile(unsigned int dest_width, unsigned int dest_height) {
    if (drawable() == 0 ||
        (dest_width == width() && dest_height == height()))
        return;

    FbPixmap new_pm(drawable(), width(), height(), depth());

    new_pm.copy(m_pm, 0, 0);

    resize(dest_width, dest_height);

    FbTk::GContext gc(*this);

    gc.setTile(new_pm);
    gc.setFillStyle(FillTiled);

    fillRectangle(gc.gc(), 0, 0, dest_width, dest_height);

}
