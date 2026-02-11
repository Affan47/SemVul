index_search(SgrepData *sgrep,struct IndexWriterStruct *writer,
		  FileList *files) {
    struct ScanBuffer *sb;
    int previous_file=-1;
    SGMLScanner *sgmls;

    sb=new_scan_buffer(sgrep,files);
    sgmls=new_sgml_index_scanner(sgrep,files,writer);
    while(next_scan_buffer(sb)>0) {
	if (previous_file!=-1 && sb->file_num!=previous_file) {
	    sgml_flush(sgmls);
	}
	previous_file=sb->file_num;
	sgrep_progress(sgrep,"Indexing file %d/%d '%s' %d/%dK (%d%%)\n",
		      sb->file_num+1,flist_files(files),
		       flist_name(files,sb->file_num),
		      sb->region_start/1024,flist_total(files)/1024,
		      sb->region_start/(flist_total(files)/100+1));
	if (sgrep->progress_callback) {
	    sgrep->progress_callback(sgrep->progress_data,
				     sb->file_num,flist_files(files),
				     sb->region_start,flist_total(files));
	}
	if (sgml_scan(sgmls,sb->map,sb->len,sb->region_start,sb->file_num)
	    ==SGREP_ERROR) {
	    delete_scan_buffer(sb);
	    delete_sgml_scanner(sgmls);
	    return SGREP_ERROR;
	}
    }
    sgml_flush(sgmls);
    delete_scan_buffer(sb);
    delete_sgml_scanner(sgmls);
    return SGREP_OK;
}
