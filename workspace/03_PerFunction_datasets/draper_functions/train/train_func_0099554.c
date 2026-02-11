filter_reload_parameters(xmlNode * param_set, const char *restart_string)
{
    int len = 0;
    char *name = NULL;
    char *match = NULL;

    if (param_set == NULL) {
        return;
    }

    if (param_set) {
        xmlAttrPtr xIter = param_set->properties;

        while (xIter) {
            const char *prop_name = (const char *)xIter->name;

            xIter = xIter->next;
            name = NULL;
            len = strlen(prop_name) + 3;

            name = malloc(len);
            if(name) {
                sprintf(name, " %s ", prop_name);
                name[len - 1] = 0;
                match = strstr(restart_string, name);
            }

            if (match == NULL) {
                crm_trace("%s not found in %s", prop_name, restart_string);
                xml_remove_prop(param_set, prop_name);
            }
            free(name);
        }
    }
}
