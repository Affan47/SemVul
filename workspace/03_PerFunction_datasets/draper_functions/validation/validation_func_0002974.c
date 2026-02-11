ssh_pcap_file_open(ssh_pcap_file pcap, const char *filename){
	ssh_buffer header;
	int err;
	if(pcap == NULL)
		return SSH_ERROR;
	if(pcap->output){
		fclose(pcap->output);
		pcap->output=NULL;
	}
	pcap->output=fopen(filename,"wb");
	if(pcap->output==NULL)
		return SSH_ERROR;
	header=ssh_buffer_new();
	if(header==NULL)
		return SSH_ERROR;
    err = buffer_add_u32(header,htonl(PCAP_MAGIC));
    if (err < 0) {
        goto error;
    }
    err = buffer_add_u16(header,htons(PCAP_VERSION_MAJOR));
    if (err < 0) {
        goto error;
    }
    err = buffer_add_u16(header,htons(PCAP_VERSION_MINOR));
    if (err < 0) {
        goto error;
    }

    err = buffer_add_u32(header,htonl(0));
    if (err < 0) {
        goto error;
    }

    err = buffer_add_u32(header,htonl(0));
    if (err < 0) {
        goto error;
    }

    err = buffer_add_u32(header,htonl(MAX_PACKET_LEN));
    if (err < 0) {
        goto error;
    }

    err = buffer_add_u32(header,htonl(DLT_RAW));
    if (err < 0) {
        goto error;
    }
	err=ssh_pcap_file_write(pcap,header);
error:
	ssh_buffer_free(header);
	return err;
}
