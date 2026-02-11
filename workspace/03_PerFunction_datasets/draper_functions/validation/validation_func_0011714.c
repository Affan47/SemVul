read_geom_in_nwchem_input(gchar *NameFile)
{
	FilePosTypeGeom j;
 	j=  get_geometry_type_from_nwchem_input_file(NameFile);
 	if( j.geomtyp == GEOM_IS_XYZ)
		read_XYZ_from_nwchem_input_file(NameFile);
      	else
 	if( j.geomtyp == GEOM_IS_ZMAT)
		read_Zmat_from_nwchem_input_file(NameFile);
        else
    		Message(_("Sorry\nI can not read gemetry in NWChem input file\n"),_("Warning"),TRUE);
}
