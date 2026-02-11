find_char(char const* text, char c)
    {
        for(;*text; ++text)
            if (c == *text) return true;
        return false;
    }
