ReadElement(string section, string entry, string filename)
{
    if (section.length() == 0)
        return string();
    if (entry.length() == 0)
        return string();
    if (filename.length() == 0)
        return string();

    IniFile MyIniFile (filename);

    return MyIniFile.GetKeyValue(section, entry);;
}
