pcap_list_datalinks(pcap_t *p, int **dlt_buffer)
{
	if (p->dlt_count == 0) {


		*dlt_buffer = (int*)malloc(sizeof(**dlt_buffer));
		if (*dlt_buffer == NULL) {
			(void)snprintf(p->errbuf, sizeof(p->errbuf),
			    "malloc: %s", pcap_strerror(errno));
			return (-1);
		}
		**dlt_buffer = p->linktype;
		return (1);
	} else {
		*dlt_buffer = (int*)calloc(sizeof(**dlt_buffer), p->dlt_count);
		if (*dlt_buffer == NULL) {
			(void)snprintf(p->errbuf, sizeof(p->errbuf),
			    "malloc: %s", pcap_strerror(errno));
			return (-1);
		}
		(void)memcpy(*dlt_buffer, p->dlt_list,
		    sizeof(**dlt_buffer) * p->dlt_count);
		return (p->dlt_count);
	}
}
