getPixelSize() const
{
    Size sz(0, 0);

    if (d_window)
    {
        sz = d_window->getPixelSize();
        sz.d_width += (d_padding.d_left + d_padding.d_right);
        sz.d_height += (d_padding.d_top + d_padding.d_bottom);
    }

    return sz;
}
