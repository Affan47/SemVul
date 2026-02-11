getword(void)
{
    size_t x;
    int disabled = 0;
    int quote = 0;
    int rem = 0;

    if (pa_nospace)
    {
        while (C && issplit(C))
            pa_the_ptr++;
        x = pa_the_ptr;
        while (C && !issplit(C) && (C != pa_breakchar || !pa_breakchar || disabled))
        {
            if (pa_breakchar && C == pa_disable)
                disabled = 1;
            if (pa_breakchar && C == pa_enable)
                disabled = 0;
            if (pa_quote && C == '"')
                quote = 1;
            pa_the_ptr++;
            while (quote && C && C != '"')
            {
                pa_the_ptr++;
            }
            if (pa_quote && C == '"')
            {
                pa_the_ptr++;
            }
            quote = 0;
        }
    } else
    {
        if (C == pa_breakchar && pa_breakchar)
        {
            x = pa_the_ptr++;
            rem = 1;
        } else
        {
            while (C && (C == ' ' || C == 9 || C == 13 || C == 10 || issplit(C)))
                pa_the_ptr++;
            x = pa_the_ptr;
            while (C && C != ' ' && C != 9 && C != 13 && C != 10 && !issplit(C) &&
                (C != pa_breakchar || !pa_breakchar || disabled))
            {
                if (pa_breakchar && C == pa_disable)
                    disabled = 1;
                if (pa_breakchar && C == pa_enable)
                    disabled = 0;
                if (pa_quote && C == '"')
                {
                    quote = 1;
                    pa_the_ptr++;
                    while (quote && C && C != '"')
                    {
                        pa_the_ptr++;
                    }
                    if (pa_quote && C == '"')
                    {
                        pa_the_ptr++;
                    }
                }
                else
                    pa_the_ptr++;
                quote = 0;
            }
            pa_the_ptr++;
            rem = 1;
        }
        if (x == pa_the_ptr && C == pa_breakchar && pa_breakchar)
            pa_the_ptr++;
    }


    if (x < pa_the_str.size())
    {
        pa_ord = pa_the_str.substr(x,pa_the_ptr - x - rem);
    }
    else
    {
        pa_ord = "";
    }
    return pa_ord;
}
