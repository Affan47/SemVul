string_input_for_buffer (const char *string)
{
    char *pos_slash, *pos_space, *next_char;


    if (strncmp (string, "/*", 2) == 0)
        return string;


    if (string[0] == '/')
    {
        pos_slash = strchr (string + 1, '/');
        pos_space = strchr (string + 1, ' ');


        if (!pos_slash || (pos_space && pos_slash > pos_space))
            return NULL;

        return (string[1] == '/') ? string + 1 : string;
    }


    if (!string_is_command_char (string))
        return string;


    next_char = utf8_next_char (string);
    if (!next_char || !next_char[0])
        return string;
    if (utf8_charcmp (string, next_char) == 0)
        return next_char;


    return NULL;
}
