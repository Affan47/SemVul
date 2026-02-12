bool unit_prefix_is_valid(const char *p) {


        if (isempty(p))
                return false;

        return in_charset(p, VALID_CHARS);
}
