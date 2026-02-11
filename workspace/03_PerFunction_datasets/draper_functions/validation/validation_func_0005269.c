dump_sess_list(void)
{
    netsnmp_agent_session *a;

    DEBUGMSGTL(("snmp_agent", "DUMP agent_sess_list -> "));
    for (a = agent_session_list; a != NULL; a = a->next) {
        DEBUGMSG(("snmp_agent", "%8p[session %8p] -> ", a, a->session));
    }
    DEBUGMSG(("snmp_agent", "[NIL]\n"));
}
