state_hfieldbody0(char ch)
    {
        if (ch == '\r')
        {
            state = &HeaderParser::state_hfieldbody_cr;
            return;
        }
        else if (ch == '\n')
        {
            state = &HeaderParser::state_hfieldbody_crlf;
            return;
        }
        else if (std::isspace(ch))
        {
            return;
        }
        else if (!std::isspace(ch))
        {
            token.reserve(32);
            token = ch;
            state = &HeaderParser::state_hfieldbody;
            return;
        }
    }
