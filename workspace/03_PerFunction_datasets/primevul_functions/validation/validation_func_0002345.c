void lua_text_pattern::pre_pattern(string &pat, string &fn) const
{

    pat.erase(pat.find_last_not_of(" \t\n\r") + 1);

    fn += " pmatch([[";
    fn += pat;
    fn += "]], text, false) ";

    pat.clear();
}
