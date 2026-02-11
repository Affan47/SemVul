snmp_collator_create_semaphore()
{

    if ((stats_sem = sem_open(stats_sem_name, O_CREAT | O_EXCL, SLAPD_DEFAULT_FILE_MODE, 1)) == SEM_FAILED) {
        if (errno == EEXIST) {


            if (sem_unlink(stats_sem_name) != 0) {
                LDAPDebug( LDAP_DEBUG_ANY, "Failed to delete old semaphore for stats file (%s). "
                          "Error %d (%s).\n", szStatsFile, errno, slapd_system_strerror(errno) );
                exit(1);
            }

            if ((stats_sem = sem_open(stats_sem_name, O_CREAT | O_EXCL, SLAPD_DEFAULT_FILE_MODE, 1)) == SEM_FAILED) {

                LDAPDebug( LDAP_DEBUG_ANY, "Failed to create semaphore for stats file (%s). Error %d (%s).\n",
                         szStatsFile, errno, slapd_system_strerror(errno) );
                exit(1);
            }
        } else {

            LDAPDebug( LDAP_DEBUG_ANY, "Failed to create semaphore for stats file (%s). Error %d.(%s)\n",
                     szStatsFile, errno, slapd_system_strerror(errno) );
            exit(1);
        }
    }


    return;
}
