setFromString(const char *str) {
    if (str == 0)
        setDefaultValue();
    else {
        string filename(str);

        StringUtil::removeFirstWhitespace(filename);
        StringUtil::removeTrailingWhitespace(filename);

        std::auto_ptr<PixmapWithMask> pm(Image::load(filename, m_tm.screenNum()));
        if (pm.get() == 0)
            setDefaultValue();
        else {
            (*this)->pixmap() = pm->pixmap().release();
            (*this)->mask() = pm->mask().release();
        }
    }
}
