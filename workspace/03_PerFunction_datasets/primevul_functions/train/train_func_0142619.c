QStringList Utility::LinuxHunspellDictionaryDirs()
{
    QStringList paths;

    if (!hunspell_dicts_override.isEmpty()) {

        foreach (QString s, hunspell_dicts_override.split(":")) {
            paths << s.trimmed();
        }
    }

    else if (!sigil_extra_root.isEmpty()) {
        paths.append(sigil_extra_root + "/hunspell_dictionaries/");
    }

    else if (!dicts_are_bundled) {
        paths.append("/usr/share/hunspell");


        if (!extra_dict_dirs.isEmpty()) {
            foreach (QString s, extra_dict_dirs.split(":")) {
                paths << s.trimmed();
            }
        }
    }
    else {

        paths.append(sigil_share_root + "/hunspell_dictionaries/");
    }
    return paths;
}
