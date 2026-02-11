var_extensible_pass_persist(struct variable *vp,
                            oid * name,
                            size_t * length,
                            int exact,
                            size_t * var_len, WriteMethod ** write_method)
{
    oid             newname[MAX_OID_LEN];
    int             i, rtest, newlen;
    char            buf[SNMP_MAXBUF];
    static char     buf2[SNMP_MAXBUF];
    struct extensible *persistpassthru;
    FILE           *file;


    init_persist_pipes();

    for (i = 1; i <= numpersistpassthrus; i++) {
        persistpassthru = get_exten_instance(persistpassthrus, i);
        rtest = snmp_oidtree_compare(name, *length,
                                     persistpassthru->miboid,
                                     persistpassthru->miblen);
        if ((exact && rtest == 0) || (!exact && rtest <= 0)) {


            if (persistpassthru->miblen >= *length || rtest < 0)
                sprint_mib_oid(buf, persistpassthru->miboid,
                               persistpassthru->miblen);
            else
                sprint_mib_oid(buf, name, *length);


            if (!open_persist_pipe(i, persistpassthru->name)) {
                return (NULL);
            }

            if (exact)
                snprintf(persistpassthru->command,
                  sizeof(persistpassthru->command), "get\n%s\n", buf);
            else
                snprintf(persistpassthru->command,
                  sizeof(persistpassthru->command), "getnext\n%s\n", buf);
            persistpassthru->command[ sizeof(persistpassthru->command)-1 ] = 0;

            DEBUGMSGTL(("ucd-snmp/pass_persist",
                        "persistpass-sending:\n%s",
                        persistpassthru->command));
            if (!write_persist_pipe(i, persistpassthru->command)) {
                *var_len = 0;


                return (NULL);
            }


            if ((file = persist_pipes[i].fIn)) {
                if (fgets(buf, sizeof(buf), file) == NULL) {
                    *var_len = 0;
                    close_persist_pipe(i);
                    return (NULL);
                }


                if (!strncmp(buf, "NONE", 4)) {
                    if (exact) {
                        *var_len = 0;
                        return (NULL);
                    }
                    continue;
                }
                newlen = parse_miboid(buf, newname);


                memcpy((char *) name, (char *) newname,
                       (int) newlen * sizeof(oid));
                *length = newlen;


                *write_method = setPassPersist;

                if (newlen == 0 || fgets(buf, sizeof(buf), file) == NULL
                    || fgets(buf2, sizeof(buf2), file) == NULL) {
                    *var_len = 0;
                    close_persist_pipe(i);
                    return (NULL);
                }
                return netsnmp_internal_pass_parse(buf, buf2, var_len, vp);
            }
            *var_len = 0;
            return (NULL);
        }
    }
    if (var_len)
        *var_len = 0;
    *write_method = NULL;
    return (NULL);
}
