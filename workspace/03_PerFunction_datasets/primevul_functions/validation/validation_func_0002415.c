pattern_match lua_text_pattern::match_location(const string &s) const
{


    return matches(s)
        ? pattern_match::succeeded(s)
        : pattern_match::failed(s);
}
