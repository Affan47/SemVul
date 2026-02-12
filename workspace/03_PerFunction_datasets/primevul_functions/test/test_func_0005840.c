static int remove_connection_headers (orderedmap hashofheaders)
{
        static const char *headers[] = {
                "connection",
                "proxy-connection"
        };

        char *data;
        char *ptr;
        ssize_t len;
        int i;

        for (i = 0; i != (sizeof (headers) / sizeof (char *)); ++i) {

                data = orderedmap_find(hashofheaders, headers[i]);

                if (!data)
                        return 0;

                len = strlen(data);


                ptr = data;
                while ((ptr = strpbrk (ptr, "()<>@,;:\\\"/[]?={} \t")))
                        *ptr++ = '\0';


                ptr = data;
                while (ptr < data + len) {
                        orderedmap_remove (hashofheaders, ptr);


                        ptr += strlen (ptr) + 1;
                        while (ptr < data + len && *ptr == '\0')
                                ptr++;
                }


                orderedmap_remove (hashofheaders, headers[i]);
        }

        return 0;
}
