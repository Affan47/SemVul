find_option(opal_cmd_line_t *cmd,
                                      const char *option_name)
{
    opal_list_item_t *item;
    cmd_line_option_t *option;


    for (item = opal_list_get_first(&cmd->lcl_options);
         opal_list_get_end(&cmd->lcl_options) != item;
         item = opal_list_get_next(item)) {
        option = (cmd_line_option_t *) item;
        if ((NULL != option->clo_long_name &&
             0 == strcmp(option_name, option->clo_long_name)) ||
            (NULL != option->clo_single_dash_name &&
             0 == strcmp(option_name, option->clo_single_dash_name)) ||
            (strlen(option_name) == 1 &&
             option_name[0] == option->clo_short_name)) {
            return option;
        }
    }


    return NULL;
}
