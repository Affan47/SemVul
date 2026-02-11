initialize_binary_vars()
{

    df_bin_record_count = 0;
    df_M_count = df_N_count = df_O_count = 0;


    df_no_bin_cols = 0;
    df_set_skip_before(1, 0);


    clear_binary_records(DF_CURRENT_RECORDS);
    if (df_num_bin_records_default) {
	df_bin_filetype = df_bin_filetype_default;
	df_bin_file_endianess = df_bin_file_endianess_default;
	df_add_binary_records(df_num_bin_records_default, DF_CURRENT_RECORDS);
	memcpy(df_bin_record, df_bin_record_default, df_num_bin_records*sizeof(df_binary_file_record_struct));
    } else {
	df_bin_filetype = df_bin_filetype_reset;
	df_bin_file_endianess = DF_BIN_FILE_ENDIANESS_RESET;
	df_add_binary_records(1, DF_CURRENT_RECORDS);
    }
}
