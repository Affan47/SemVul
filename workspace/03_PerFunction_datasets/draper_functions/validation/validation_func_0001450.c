stringToXml(std::string s)
{

    std::string::size_type pos = 0;
    while ((pos = s.find_first_of("<>&\"\n", pos)) != std::string::npos) {
        if (s[pos] == '<')
            s.insert(pos + 1, "&lt;");
        else if (s[pos] == '>')
            s.insert(pos + 1, "&gt;");
        else if (s[pos] == '&')
            s.insert(pos + 1, "&amp;");
        else if (s[pos] == '"')
            s.insert(pos + 1, "&quot;");
        else if (s[pos] == '\n')
            s.insert(pos + 1, "&#xa;");
        s.erase(pos, 1);
        ++pos;
    }
    return s;
}
