drawChars(const ustring &s, int x, int y) {
    if (fFont != null && s != null) {
        cstring cs(s);
        fFont->drawGlyphs(*this, x, y, cs.c_str(), cs.c_str_len());
    }
}
