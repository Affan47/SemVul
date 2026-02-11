print_html_string(GString *out, char *str, bool obfuscate) {
    while (*str != '\0') {
        switch (*str) {
        case '&':
            g_string_append_printf(out, "&amp;");
            break;
        case '<':
            g_string_append_printf(out, "&lt;");
            break;
        case '>':
            g_string_append_printf(out, "&gt;");
            break;
        case '"':
            g_string_append_printf(out, "&quot;");
            break;
        default:
	  if (obfuscate && ((int) *str < 128) && ((int) *str >= 0)){
                if (rand() % 2 == 0)
                    g_string_append_printf(out, "&#%d;", (int) *str);
                else
                    g_string_append_printf(out, "&#x%x;", (unsigned int) *str);
            }
            else
                g_string_append_c(out, *str);
        }
    str++;
    }
}
