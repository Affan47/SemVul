openProperties() {
    for (int mode = 0; mode <= 2; ++mode) {
        const char *name  = ED4_propertyName(mode);
        AW_default  found = ED4_ROOT->aw_root->open_default(name, mode == 2);

        if (found) {
            ED4_ROOT->db      = found;
            ED4_ROOT->db_name = strdup(name);
            break;
        }
    }

    GB_informationf("Using properties from '%s'", ED4_ROOT->db_name);
    ED4_ROOT->aw_root->init_variables( ED4_ROOT->db);
}
