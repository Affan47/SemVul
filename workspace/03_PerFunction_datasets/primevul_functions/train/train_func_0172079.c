nextline(struct pam_fh *pam_fh, pam_handle_t *pamh, int *err)
{
	char	*ll;
	int	find_a_line = 0;
	char	*data = pam_fh->data;
	char	*bufferp = pam_fh->bufferp;
	char	*bufferendp = &data[pam_fh->bufsize];
	size_t	input_len;


	while (!find_a_line) {

		if (bufferp == bufferendp)
			return (NULL);


		while (*bufferp == '\n') {


			if (++bufferp == bufferendp) {
				return (NULL);
			}

		}


		while (*bufferp == '#') {
			if ((ll = pam_conf_strnchr(bufferp, '\n',
			    bufferendp - bufferp)) != NULL) {
				bufferp = ll;
			} else {


				return (NULL);
			}


			if (bufferp == bufferendp) {
				return (NULL);
			}
		}

		if ((*bufferp != '\n') && (*bufferp != '#')) {
			find_a_line = 1;
		}
	}

	*err = PAM_SUCCESS;

	if ((ll = pam_conf_strnchr(bufferp, '\n', bufferendp - bufferp))
	    != NULL) {
		if ((input_len = ll - bufferp) >= sizeof (pam_fh->line)) {
			__pam_log(LOG_AUTH | LOG_ERR,
			    "nextline[%d:%s]: pam.conf line too long %.256s",
			    pamh->include_depth, pam_trace_cname(pamh),
			    bufferp);
			input_len = sizeof (pam_fh->line) - 1;
			*err = PAM_SERVICE_ERR;
		}
		(void) strncpy(pam_fh->line, bufferp, input_len);
		pam_fh->line[input_len] = '\0';
		pam_fh->bufferp = ll++;
	} else {
		ll = bufferendp;
		if ((input_len = ll - bufferp) >= sizeof (pam_fh->line)) {
			__pam_log(LOG_AUTH | LOG_ERR,
			    "nextline[%d:%s]: pam.conf line too long %.256s",
			    pamh->include_depth, pam_trace_cname(pamh),
			    bufferp);
			input_len = sizeof (pam_fh->line) - 1;
			*err = PAM_SERVICE_ERR;
		}
		(void) strncpy(pam_fh->line, bufferp, input_len);
		pam_fh->line[input_len] = '\0';
		pam_fh->bufferp = ll;
	}

	return (pam_fh->line);
}
