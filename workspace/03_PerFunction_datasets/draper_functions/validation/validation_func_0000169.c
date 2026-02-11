log__delete_rotated_logs()
{
	struct logfileinfo *logp = NULL;
	char buffer[BUFSIZ];
	char tbuf[TBUFSIZE];


	logp = loginfo.log_access_logchain;
	while (logp) {
		tbuf[0] = buffer[0] = '\0';
		log_convert_time (logp->l_ctime, tbuf, 1);
		PR_snprintf (buffer, sizeof(buffer), "%s.%s", loginfo.log_access_file, tbuf);

		LDAPDebug(LDAP_DEBUG_ANY,"Deleted Rotated Log: %s\n",buffer,0,0);

		if (PR_Delete(buffer) != PR_SUCCESS) {
			logp = logp->l_next;
			continue;
		}
		loginfo.log_numof_access_logs--;
		logp = logp->l_next;
	}


	logp = loginfo.log_audit_logchain;
	while (logp) {
		tbuf[0] = buffer[0] = '\0';
		log_convert_time (logp->l_ctime, tbuf, 1);
		PR_snprintf (buffer, sizeof(buffer), "%s.%s", loginfo.log_audit_file, tbuf);
		if (PR_Delete(buffer) != PR_SUCCESS) {
			logp = logp->l_next;
			continue;
		}
		loginfo.log_numof_audit_logs--;
		logp = logp->l_next;
	}


	logp = loginfo.log_error_logchain;
	while (logp) {
		tbuf[0] = buffer[0] = '\0';
		log_convert_time (logp->l_ctime, tbuf, 1);
		PR_snprintf (buffer, sizeof(buffer), "%s.%s", loginfo.log_error_file, tbuf);
		if (PR_Delete(buffer) != PR_SUCCESS) {
			logp = logp->l_next;
			continue;
		}
		loginfo.log_numof_error_logs--;
		logp = logp->l_next;
	}
}
