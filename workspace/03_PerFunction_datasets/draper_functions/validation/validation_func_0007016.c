amber_getInvWavelength (const char * filename,
		CalibratorParam *calibrator)
{
	int            ext_oi_wavelength=0;
	cpl_table    * table=NULL;


	ext_oi_wavelength=cpl_fits_find_extension(filename,"OI_WAVELENGTH");
	table = cpl_table_load(filename, ext_oi_wavelength, 0);
	if (table == NULL) {
		return cpl_error_set_message(cpl_func, cpl_error_get_code(),
				"Could not load the table");
	}


	if (cpl_table_has_column(table,"EFF_WAVE")){
		const int dimen_table=cpl_table_get_nrow(table);
		int       i;

		calibrator->calibInvWavelength=cpl_vector_new(dimen_table);


		for(i=0;i<dimen_table;i++){
			cpl_vector_set(calibrator->calibInvWavelength,i,
					1./cpl_table_get_float(table,"EFF_WAVE",i,NULL));
		}
	}
	cpl_table_delete(table);


	return cpl_error_set(cpl_func, cpl_error_get_code());
}
