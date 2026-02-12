void PackLinuxElf32x86::addStubEntrySections(Filter const *ft)
{
    int const n_mru = ft->n_mru;


    addLoader("LEXEC000", nullptr);

    if (ft->id) {
        {
            addLoader("LXUNF000", nullptr);
            addLoader("LXUNF002", nullptr);
                if (0x80==(ft->id & 0xF0)) {
                    if (256==n_mru) {
                        addLoader("MRUBYTE0", nullptr);
                    }
                    else if (n_mru) {
                        addLoader("LXMRU005", nullptr);
                    }
                    if (n_mru) {
                        addLoader("LXMRU006", nullptr);
                    }
                    else {
                        addLoader("LXMRU007", nullptr);
                    }
            }
            else if (0x40==(ft->id & 0xF0)) {
                addLoader("LXUNF008", nullptr);
            }
            addLoader("LXUNF010", nullptr);
        }
        if (n_mru) {
            addLoader("LEXEC009", nullptr);
        }
    }
    addLoader("LEXEC010", nullptr);
    addLoader(getDecompressorSections(), nullptr);
    addLoader("LEXEC015", nullptr);
    if (ft->id) {
        {
            if (0x80!=(ft->id & 0xF0)) {
                addLoader("LXUNF042", nullptr);
            }
        }
        addFilter32(ft->id);
        {
            if (0x80==(ft->id & 0xF0)) {
                if (0==n_mru) {
                    addLoader("LXMRU058", nullptr);
                }
            }
            addLoader("LXUNF035", nullptr);
        }
    }
    else {
        addLoader("LEXEC017", nullptr);
    }

    addLoader("IDENTSTR", nullptr);
    addLoader("LEXEC020", nullptr);
    addLoader("FOLDEXEC", nullptr);
}
