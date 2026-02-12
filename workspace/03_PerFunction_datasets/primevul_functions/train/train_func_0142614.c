QString Utility::DefinePrefsDir()
{


    if (!SIGIL_PREFS_DIR.isEmpty()) {
        return SIGIL_PREFS_DIR;
    } else {
        return QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    }
}
