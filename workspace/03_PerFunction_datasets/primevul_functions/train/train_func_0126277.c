static int unit_log_resources(Unit *u) {
        struct iovec iovec[1 + _CGROUP_IP_ACCOUNTING_METRIC_MAX + 4];
        bool any_traffic = false, have_ip_accounting = false;
        _cleanup_free_ char *igress = NULL, *egress = NULL;
        size_t n_message_parts = 0, n_iovec = 0;
        char* message_parts[3 + 1], *t;
        nsec_t nsec = NSEC_INFINITY;
        CGroupIPAccountingMetric m;
        size_t i;
        int r;
        const char* const ip_fields[_CGROUP_IP_ACCOUNTING_METRIC_MAX] = {
                [CGROUP_IP_INGRESS_BYTES]   = "IP_METRIC_INGRESS_BYTES",
                [CGROUP_IP_INGRESS_PACKETS] = "IP_METRIC_INGRESS_PACKETS",
                [CGROUP_IP_EGRESS_BYTES]    = "IP_METRIC_EGRESS_BYTES",
                [CGROUP_IP_EGRESS_PACKETS]  = "IP_METRIC_EGRESS_PACKETS",
        };

        assert(u);


        (void) unit_get_cpu_usage(u, &nsec);
        if (nsec != NSEC_INFINITY) {
                char buf[FORMAT_TIMESPAN_MAX] = "";


                if (asprintf(&t, "CPU_USAGE_NSEC=%" PRIu64, nsec) < 0) {
                        r = log_oom();
                        goto finish;
                }
                iovec[n_iovec++] = IOVEC_MAKE_STRING(t);


                format_timespan(buf, sizeof(buf), nsec / NSEC_PER_USEC, USEC_PER_MSEC);
                t = strjoin("consumed ", buf, " CPU time");
                if (!t) {
                        r = log_oom();
                        goto finish;
                }

                message_parts[n_message_parts++] = t;
        }

        for (m = 0; m < _CGROUP_IP_ACCOUNTING_METRIC_MAX; m++) {
                char buf[FORMAT_BYTES_MAX] = "";
                uint64_t value = UINT64_MAX;

                assert(ip_fields[m]);

                (void) unit_get_ip_accounting(u, m, &value);
                if (value == UINT64_MAX)
                        continue;

                have_ip_accounting = true;
                if (value > 0)
                        any_traffic = true;


                if (asprintf(&t, "%s=%" PRIu64, ip_fields[m], value) < 0) {
                        r = log_oom();
                        goto finish;
                }
                iovec[n_iovec++] = IOVEC_MAKE_STRING(t);


                if (m == CGROUP_IP_INGRESS_BYTES) {
                        assert(!igress);
                        igress = strjoin("received ", format_bytes(buf, sizeof(buf), value), " IP traffic");
                        if (!igress) {
                                r = log_oom();
                                goto finish;
                        }
                } else if (m == CGROUP_IP_EGRESS_BYTES) {
                        assert(!egress);
                        egress = strjoin("sent ", format_bytes(buf, sizeof(buf), value), " IP traffic");
                        if (!egress) {
                                r = log_oom();
                                goto finish;
                        }
                }
        }

        if (have_ip_accounting) {
                if (any_traffic) {
                        if (igress)
                                message_parts[n_message_parts++] = TAKE_PTR(igress);
                        if (egress)
                                message_parts[n_message_parts++] = TAKE_PTR(egress);

                } else {
                        char *k;

                        k = strdup("no IP traffic");
                        if (!k) {
                                r = log_oom();
                                goto finish;
                        }

                        message_parts[n_message_parts++] = k;
                }
        }


        if (n_iovec == 0) {
                r = 0;
                goto finish;
        }

        if (n_message_parts == 0)
                t = strjoina("MESSAGE=", u->id, ": Completed.");
        else {
                _cleanup_free_ char *joined;

                message_parts[n_message_parts] = NULL;

                joined = strv_join(message_parts, ", ");
                if (!joined) {
                        r = log_oom();
                        goto finish;
                }

                joined[0] = ascii_toupper(joined[0]);
                t = strjoina("MESSAGE=", u->id, ": ", joined, ".");
        }


        iovec[n_iovec] = IOVEC_MAKE_STRING(t);
        iovec[n_iovec + 1] = IOVEC_MAKE_STRING("MESSAGE_ID=" SD_MESSAGE_UNIT_RESOURCES_STR);

        t = strjoina(u->manager->unit_log_field, u->id);
        iovec[n_iovec + 2] = IOVEC_MAKE_STRING(t);

        t = strjoina(u->manager->invocation_log_field, u->invocation_id_string);
        iovec[n_iovec + 3] = IOVEC_MAKE_STRING(t);

        log_struct_iovec(LOG_INFO, iovec, n_iovec + 4);
        r = 0;

finish:
        for (i = 0; i < n_message_parts; i++)
                free(message_parts[i]);

        for (i = 0; i < n_iovec; i++)
                free(iovec[i].iov_base);

        return r;

}
