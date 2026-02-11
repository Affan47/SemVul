exportldif_load_settings( ExportLdifCtl *ctl ) {
	XmlProperty *props;
	gint rc;
	gchar buf[ XML_BUFSIZE ];

	props = xmlprops_create();
	xmlprops_set_path( props, ctl->settingsFile );
	rc = xmlprops_load_file( props );
	if( rc == 0 ) {

		*buf = '\0';
		xmlprops_get_property_s( props, EXMLPROP_DIRECTORY, buf );
		ctl->dirOutput = mgu_replace_string( ctl->dirOutput, buf );

		*buf = '\0';
		xmlprops_get_property_s( props, EXMLPROP_FILE, buf );
		ctl->fileLdif = mgu_replace_string( ctl->fileLdif, buf );

		*buf = '\0';
		xmlprops_get_property_s( props, EXMLPROP_SUFFIX, buf );
		ctl->suffix = mgu_replace_string( ctl->suffix, buf );

		ctl->rdnIndex =
			xmlprops_get_property_i( props, EXMLPROP_RDN_INDEX );
		ctl->useDN =
			xmlprops_get_property_b( props, EXMLPROP_USE_DN );
		ctl->excludeEMail =
			xmlprops_get_property_b( props, EXMLPROP_EXCL_EMAIL );
	}
	else {

		exportldif_default_values( ctl );
	}
	exportldif_build_filespec( ctl );


	xmlprops_free( props );
}
