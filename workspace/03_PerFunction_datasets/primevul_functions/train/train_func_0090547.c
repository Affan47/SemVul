bool slice_name_is_valid(const char *name) {
        const char *p, *e;
        bool dash = false;

        if (!unit_name_is_valid(name, UNIT_NAME_PLAIN))
                return false;

        if (streq(name, SPECIAL_ROOT_SLICE))
                return true;

        e = endswith(name, ".slice");
        if (!e)
                return false;

        for (p = name; p < e; p++) {

                if (*p == '-') {


                        if (p == name)
                                return false;


                        if (dash)
                                return false;

                        dash = true;
                } else
                        dash = false;
        }


        if (dash)
                return false;

        return true;
}
