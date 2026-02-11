replica_task_done(Replica *replica)
{
    int rc = LDAP_OPERATIONS_ERROR;
    char *replica_dn = NULL;
    Slapi_DN *replica_sdn = NULL;
    Slapi_PBlock *pb = NULL;
    LDAPMod *mods [2];
    LDAPMod mod;
    if (NULL == replica) {
        return rc;
    }

    replica_dn = slapi_ch_smprintf("%s,cn=\"%s\",%s",
                                   REPLICA_RDN,
                                   slapi_sdn_get_dn(replica_get_root(replica)),
                                   CONFIG_BASE);
    if (NULL == replica_dn) {
        return rc;
    }
	replica_sdn = slapi_sdn_new_dn_passin(replica_dn);
    pb = slapi_pblock_new();
    mods[0] = &mod;
    mods[1] = NULL;
    mod.mod_op = LDAP_MOD_DELETE | LDAP_MOD_BVALUES;
    mod.mod_type = (char *)TASK_ATTR;
    mod.mod_bvalues = NULL;

    slapi_modify_internal_set_pb_ext(pb, replica_sdn, mods, NULL,
                      NULL,
                      repl_get_plugin_identity (PLUGIN_MULTIMASTER_REPLICATION),
                      0);
    slapi_modify_internal_pb (pb);

    slapi_pblock_get(pb, SLAPI_PLUGIN_INTOP_RESULT, &rc);
    if ((rc != LDAP_SUCCESS) && (rc != LDAP_NO_SUCH_ATTRIBUTE)) {
        slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
                        "replica_task_done: "
                        "failed to remove (%s) attribute from (%s) entry; "
                        "LDAP error - %d\n",
                        TASK_ATTR, replica_dn, rc);
    }

    slapi_pblock_destroy (pb);
    slapi_sdn_free(&replica_sdn);

    return rc;
}
