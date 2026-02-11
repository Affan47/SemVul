rsh_launch_agent_lookup(const char *agent_list, char *path)
{
    char **tmp;

    OPAL_OUTPUT_VERBOSE((5, orte_plm_base_framework.framework_output,
                         "%s plm:rsh_lookup on agent %s path %s",
                         ORTE_NAME_PRINT(ORTE_PROC_MY_NAME),
                         (NULL == agent_list) ? mca_plm_rsh_component.agent : agent_list,
                         (NULL == path) ? "NULL" : path));
    if (NULL == (tmp = orte_plm_rsh_search(agent_list, path))) {
        return ORTE_ERR_NOT_FOUND;
    }


    opal_argv_free(tmp);
    return ORTE_SUCCESS;
}
