grab(std::string font_file, int size, int dpi) {

    if(font_dir.size()>0 && font_file[0] != '/') {
        font_file = font_dir + font_file;
    }


    fontSizeMap* sizemap = fonts[font_file];

    if(!sizemap) {
        sizemap = fonts[font_file] = new fontSizeMap;
    }

    fontSizeMap::iterator ft_it = sizemap->find(size);

    FXGlyphSet* glyphset;

    if(ft_it == sizemap->end()) {
        glyphset = new FXGlyphSet(library, font_file.c_str(), size, dpi);
        sizemap->insert(std::pair<int,FXGlyphSet*>(size,glyphset));
    } else {
        glyphset = ft_it->second;
    }

    return FXFont(glyphset);
}
