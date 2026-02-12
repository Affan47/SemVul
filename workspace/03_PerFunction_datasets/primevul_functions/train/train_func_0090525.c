bool unit_instance_is_valid(const char *i) {


        if (isempty(i))
                return false;


        return in_charset(i, "@" VALID_CHARS);
}
