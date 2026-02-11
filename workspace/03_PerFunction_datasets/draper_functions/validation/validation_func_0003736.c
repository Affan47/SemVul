filenameBaseExt(const std::string& filename) {
    int i = filename.rfind("/");
    int j = filename.rfind("\\");

    if ((j > i) && (j >= 0)) {
        i = j;
    }

#   ifdef G3D_WIN32
        j = filename.rfind(":");
        if ((i == -1) && (j >= 0)) {
            i = j;
        }
#   endif

    if (i == -1) {
        return filename;
    } else {
        return filename.substr(i + 1, filename.length() - i);
    }
}
