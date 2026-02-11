getQuoted(int p0, DOMString &result)
{

    int p = p0;

    if (peek(p)!='"' && peek(p)!='\'')
        return p0;

    int b = get(p++);

    DOMString buf;

    while (p<len )
        {
        b = get(p++);
        if (b=='"' || b=='\'')
            break;
        else if (b=='&')
            {
            p = parseEntity(p, result);
            if (p < 0)
                return p0;
            }
        else
            {
            buf.push_back((XMLCh)b);
            }
        }


    result.append(buf);

    return p;
}
