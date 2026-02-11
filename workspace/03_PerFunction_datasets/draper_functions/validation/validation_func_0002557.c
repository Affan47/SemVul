simplifyString(const std::string &source)
{
    std::string str = source;
    bool escaped = false;
    for (std::string::size_type i = 0; i + 2 < str.size(); i++)
    {
        if (!escaped)
        {
            if (str[i] == '\\')
                escaped = true;

            continue;
        }

        if (str[i] == 'x')
        {

            if (str[i+1] == '0' && str[i+2] == '0')
                str.replace(i, 3, "0");
            else if (i > 0)
            {


                unsigned int n = 1;
                while (n < 2 && std::isxdigit(str[i+1+n]))
                    ++n;
                --i;
                n += 2;
                str.replace(i, n, "a");
            }
        }
        else if (MathLib::isOctalDigit(str[i]))
        {
            if (MathLib::isOctalDigit(str[i+1]) &&
                MathLib::isOctalDigit(str[i+2]))
            {
                if (str[i+1] == '0' && str[i+2] == '0')
                    str.replace(i, 3, "0");
                else
                {


                    --i;
                    str.replace(i, 4, "a");
                }
            }
        }

        escaped = false;
    }

    return str;
}
