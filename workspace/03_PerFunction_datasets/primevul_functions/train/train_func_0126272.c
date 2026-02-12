int unit_deserialize_skip(FILE *f) {
        int r;
        assert(f);


        for (;;) {
                _cleanup_free_ char *line = NULL;
                char *l;

                r = read_line(f, LONG_LINE_MAX, &line);
                if (r < 0)
                        return log_error_errno(r, "Failed to read serialization line: %m");
                if (r == 0)
                        return 0;

                l = strstrip(line);


                if (isempty(l))
                        return 1;
        }
}
