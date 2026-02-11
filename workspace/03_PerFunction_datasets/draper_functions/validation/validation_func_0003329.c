write(FILE* fout) {
    unsigned int i;

    fprintf(fout,
        "<scheduler_request>\n"
        "  <authenticator>%s</authentiicator>\n"
        "  <platform_name>%s</platform_name>\n"
        "  <cross_project_id>%s</cross_project_id>\n"
        "  <hostid>%d</hostid>\n"
        "  <core_client_major_version>%d</core_client_major_version>\n"
        "  <core_client_minor_version>%d</core_client_minor_version>\n"
        "  <core_client_release>%d</core_client_release>\n"
        "  <rpc_seqno>%d</rpc_seqno>\n"
        "  <work_req_seconds>%.15f</work_req_seconds>\n"
        "  <resource_share_fraction>%.15f</resource_share_fraction>\n"
        "  <rrs_fraction>%.15f</rrs_fraction>\n"
        "  <prrs_fraction>%.15f</prrs_fraction>\n"
        "  <estimated_delay>%.15f</estimated_delay>\n"
        "  <code_sign_key>%s</code_sign_key>\n"
        "  <anonymous_platform>%s</anonymous_platform>\n",
        authenticator,
        platform.name,
        cross_project_id,
        hostid,
        core_client_major_version,
        core_client_minor_version,
        core_client_release,
        rpc_seqno,
        work_req_seconds,
        resource_share_fraction,
        rrs_fraction,
        prrs_fraction,
        cpu_estimated_delay,
        code_sign_key,
        is_anonymous(platforms.list[0])?"true":"false"
    );

    for (i=0; i<client_app_versions.size(); i++) {
        fprintf(fout,
            "  <app_version>\n"
            "    <app_name>%s</app_name>\n"
            "    <version_num>%d</version_num>\n"
            "  </app_version>\n",
            client_app_versions[i].app_name,
            client_app_versions[i].version_num
        );
    }

    fprintf(fout,
        "  <global_prefs_xml>\n"
        "    %s"
        "  </globals_prefs_xml>\n",
        global_prefs_xml
    );

    fprintf(fout,
        "  <global_prefs_source_email_hash>%s</global_prefs_source_email_hash>\n",
        global_prefs_source_email_hash
    );

    fprintf(fout,
        "  <host>\n"
        "    <id>%d</id>\n"
        "    <rpc_time>%d</rpc_time>\n"
        "    <timezone>%d</timezone>\n"
        "    <d_total>%.15f</d_total>\n"
        "    <d_free>%.15f</d_free>\n"
        "    <d_boinc_used_total>%.15f</d_boinc_used_total>\n"
        "    <d_boinc_used_project>%.15f</d_boinc_used_project>\n"
        "    <d_boinc_max>%.15f</d_boinc_max>\n",
        host.id,
        host.rpc_time,
        host.timezone,
        host.d_total,
        host.d_free,
        host.d_boinc_used_total,
        host.d_boinc_used_project,
        host.d_boinc_max
    );

    for (i=0; i<results.size(); i++) {
        fprintf(fout,
            "  <result>\n"
            "    <name>%s</name>\n"
            "    <client_state>%d</client_state>\n"
            "    <cpu_time>%.15f</cpu_time>\n"
            "    <exit_status>%d</exit_status>\n"
            "    <app_version_num>%d</app_version_num>\n"
            "  </result>\n",
            results[i].name,
            results[i].client_state,
            results[i].cpu_time,
            results[i].exit_status,
            results[i].app_version_num
        );
    }

    for (i=0; i<msgs_from_host.size(); i++) {
        fprintf(fout,
            "  <msg_from_host>\n"
            "    <variety>%s</variety>\n"
            "    <msg_text>%s</msg_text>\n"
            "  </msg_from_host>\n",
            msgs_from_host[i].variety,
            msgs_from_host[i].msg_text.c_str()
        );
    }

    for (i=0; i<file_infos.size(); i++) {
        fprintf(fout,
            "  <file_info>\n"
            "    <name>%s</name>\n"
            "  </file_info>\n",
            file_infos[i].name
        );
        fprintf(fout, "</scheduler_request>\n");
    }
    return 0;
}
