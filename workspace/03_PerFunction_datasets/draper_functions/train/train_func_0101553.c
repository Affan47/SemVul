mca_base_component_to_string(const mca_base_component_t *a) {
    char * str = NULL;
    if(0 > asprintf(&str, "%s.%s.%d.%d", a->mca_type_name,
                    a->mca_component_name, a->mca_component_major_version,
                    a->mca_component_minor_version)) {
        return NULL;
    }
    return str;
}
