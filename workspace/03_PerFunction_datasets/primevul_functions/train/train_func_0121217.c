void print_report_hdr(unsigned int flags, struct tm *rectime,
		      struct file_header *file_hdr)
{


	get_file_timestamp_struct(flags, rectime, file_hdr);


	print_gal_header(rectime, file_hdr->sa_sysname, file_hdr->sa_release,
			 file_hdr->sa_nodename, file_hdr->sa_machine,
			 file_hdr->sa_cpu_nr > 1 ? file_hdr->sa_cpu_nr - 1 : 1,
			 PLAIN_OUTPUT);
}
