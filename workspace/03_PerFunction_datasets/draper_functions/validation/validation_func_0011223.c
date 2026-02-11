ExportExporterList( nffile_t *nffile ) {
int i;


	i = 1;
	while ( i < MAX_EXPORTERS  && exporter_list[i] != NULL ) {
		exporter_info_record_t *exporter;
       	generic_sampler_t *sampler;

		exporter = &exporter_list[i]->info;
		AppendToBuffer(nffile, (void *)exporter, exporter->header.size);

		sampler  = exporter_list[i]->sampler;
        while ( sampler ) {
            AppendToBuffer(nffile, (void *)&(sampler->info), sampler->info.header.size);
            sampler = sampler->next;
        }

		i++;
	}


}
