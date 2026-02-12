usm_check_and_update_timeliness(u_char * secEngineID,
                                size_t secEngineIDLen,
                                u_int boots_uint,
                                u_int time_uint, int *error)
{
    u_char          myID[USM_MAX_ID_LENGTH];
    u_long          myIDLength =
        snmpv3_get_engineID(myID, USM_MAX_ID_LENGTH);
    u_int           myBoots;
    u_int           myTime;


    if ((myIDLength > USM_MAX_ID_LENGTH) || (myIDLength == 0)) {


        DEBUGMSGTL(("usm", "Buffer overflow.\n"));
        *error = SNMPERR_USM_GENERICERROR;
        return -1;
    }

    myBoots = snmpv3_local_snmpEngineBoots();
    myTime = snmpv3_local_snmpEngineTime();


    if (secEngineIDLen == myIDLength
        && memcmp(secEngineID, myID, myIDLength) == 0) {
        u_int           time_difference = myTime > time_uint ?
            myTime - time_uint : time_uint - myTime;

        if (boots_uint == ENGINEBOOT_MAX
            || boots_uint != myBoots
            || time_difference > USM_TIME_WINDOW) {
            snmp_increment_statistic(STAT_USMSTATSNOTINTIMEWINDOWS);

            DEBUGMSGTL(("usm",
                        "boot_uint %u myBoots %u time_diff %u => not in time window\n",
                        boots_uint, myBoots, time_difference));
            *error = SNMPERR_USM_NOTINTIMEWINDOW;
            return -1;
        }

        *error = SNMPERR_SUCCESS;
        return 0;
    }


    else {
        u_int           theirBoots, theirTime, theirLastTime;
        u_int           time_difference;

        if (get_enginetime_ex(secEngineID, secEngineIDLen,
                              &theirBoots, &theirTime,
                              &theirLastTime, TRUE)
            != SNMPERR_SUCCESS) {
            DEBUGMSGTL(("usm", "%s\n",
                        "Failed to get remote engine's times."));

            *error = SNMPERR_USM_GENERICERROR;
            return -1;
        }

        time_difference = theirTime > time_uint ?
            theirTime - time_uint : time_uint - theirTime;


        if (theirBoots == ENGINEBOOT_MAX || theirBoots > boots_uint) {
            DEBUGMSGTL(("usm", "%s\n", "Remote boot count invalid."));

            *error = SNMPERR_USM_NOTINTIMEWINDOW;
            return -1;
        }


        if (theirBoots == boots_uint && time_uint < theirLastTime) {
            if (time_difference > USM_TIME_WINDOW) {
                DEBUGMSGTL(("usm", "%s\n", "Message too old."));
                *error = SNMPERR_USM_NOTINTIMEWINDOW;
                return -1;
            }

            else {

                *error = SNMPERR_SUCCESS;
                return 0;
            }
        }


        if (set_enginetime(secEngineID, secEngineIDLen,
                           boots_uint, time_uint, TRUE)
            != SNMPERR_SUCCESS) {
            DEBUGMSGTL(("usm", "%s\n",
                        "Failed updating remote boot/time."));
            *error = SNMPERR_USM_GENERICERROR;
            return -1;
        }

        *error = SNMPERR_SUCCESS;
        return 0;

    }


}
