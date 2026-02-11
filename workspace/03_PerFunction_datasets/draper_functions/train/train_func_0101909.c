h5tools_print_char(h5tools_str_t *str, const h5tool_format_t *info, char ch)
{
    if (info->str_locale == ESCAPE_HTML) {
        if (ch <= ' ' || ch > '~')
            h5tools_str_append(str, "%%%02x", ch);
        else
            h5tools_str_append(str, "%c", ch);
    }
    else {
        switch (ch) {
        case '"':
            if (!info->do_escape)
                h5tools_str_append(str, "\"");
            else
                h5tools_str_append(str, "\\\"");
            break;
        case '\\':
            if (!info->do_escape)
                h5tools_str_append(str, "\\");
            else
                h5tools_str_append(str, "\\\\");
            break;
        case '\b':
            if (!info->do_escape)
                h5tools_str_append(str, "\b");
            else
                h5tools_str_append(str, "\\b");
            break;
        case '\f':
            if (!info->do_escape)
                h5tools_str_append(str, "\f");
            else
                h5tools_str_append(str, "\\f");
            break;
        case '\n':
            if (!info->do_escape) {
                h5tools_str_append(str, "\n");
                h5tools_str_append(str, "           ");
            }
            else
                h5tools_str_append(str, "\\n");
            break;
        case '\r':
            if (!info->do_escape) {
                h5tools_str_append(str, "\r");
                h5tools_str_append(str, "           ");
            }
            else
                h5tools_str_append(str, "\\r");
            break;
        case '\t':
            if (!info->do_escape)
                h5tools_str_append(str, "\t");
            else
                h5tools_str_append(str, "\\t");
            break;
        default:
            if (isprint(ch))
                h5tools_str_append(str, "%c", ch);
            else
                h5tools_str_append(str, "\\%03o", ch);

            break;
        }
    }
}
