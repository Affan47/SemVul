vmCplParlistExport(const cpl_parameterlist *list)
{

    if (list != NULL
        || cpl_parameterlist_get_size((cpl_parameterlist *)list) == 0) {

        cpl_parameter *parameter =
                       cpl_parameterlist_get_first((cpl_parameterlist *)list);


        while (parameter) {

            const char *name;
            const char *group;

            char *context = (char *)cpl_parameter_get_context(parameter);

            int status;

            cx_string *value;


            if (strstr(context, "vimos.") != context) {
                return -1;
            }
            else {
                group = context + strlen("vimos.");
            }


            name = cpl_parameter_get_alias(parameter, CPL_PARAMETER_MODE_CLI);

            if (name == NULL) {
                return -2;
            }
            else {
                char *s = strrchr(name, (int)'.');

                if (s != NULL) {
                    name = s + 1;
                }
            }


            value = cx_string_new();

            switch (cpl_parameter_get_type(parameter)) {
                case CPL_TYPE_BOOL:
                    if (cpl_parameter_get_bool(parameter) != 0) {
                        cx_string_set(value, "true");
                    }
                    else {
                        cx_string_set(value, "false");
                    }
                    break;

                case CPL_TYPE_INT:
                {
                    int i = cpl_parameter_get_int(parameter);

                    cx_string_sprintf(value, "%i", i);
                    break;
                }

                case CPL_TYPE_DOUBLE:
                {
                    double d = cpl_parameter_get_double(parameter);

                    cx_string_sprintf(value, "%g", d);
                    break;
                }

                case CPL_TYPE_STRING:
                    cx_string_set(value, cpl_parameter_get_string(parameter));
                    break;

                default:
                    return -3;
                    break;
            }


            status = pilDfsDbCreateEntry(group, name, cx_string_get(value),
                                         READ_WRITE);

            if (status != EXIT_SUCCESS) {
                cx_string_delete(value);
                return 1;
            }

            cx_string_delete(value);
            parameter = cpl_parameterlist_get_next((cpl_parameterlist *)list);

        }

    }

    return 0;

}
