add_header_to_connection (orderedmap hashofheaders, char *header, size_t len)
{
        char *sep;


        len -= chomp (header, len);

        sep = strchr (header, ':');
        if (!sep)
                return 0;


        while (*sep == ':' || *sep == ' ' || *sep == '\t')
                *sep++ = '\0';


        len -= sep - header - 1;

        return orderedmap_append (hashofheaders, header, sep);
}
