output(void *data, Query *query)
{
    query->outputBeginList();
    contact *auth_user = query->authUser();
    hostsmember *mem = getMembers(data);

    bool first = true;
    while (mem) {
        host *hst = mem->host_ptr;
        if (!auth_user || g_table_hosts->isAuthorized(auth_user, hst)) {
            if (!first)
                query->outputListSeparator();
            else
                first = false;
            if (!_show_state)
                query->outputString(hst->name);
            else {
                query->outputBeginSublist();
                query->outputString(hst->name);
                query->outputSublistSeparator();
                query->outputInteger(hst->current_state);
                query->outputSublistSeparator();
                query->outputInteger(hst->has_been_checked);
                query->outputEndSublist();
            }
        }
        mem = mem->next;
    }
    query->outputEndList();
}
