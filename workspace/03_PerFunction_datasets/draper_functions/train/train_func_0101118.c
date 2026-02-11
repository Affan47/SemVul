ExportIPTC_IntellectualGenre ( const SXMPMeta & xmp, IPTC_Manager * iptc )
{
	std::string    xmpValue;
	XMP_OptionBits xmpFlags;

	bool found = xmp.GetProperty ( kXMP_NS_IPTCCore, "IntellectualGenre", &xmpValue, &xmpFlags );
	if ( ! found ) {
		iptc->DeleteDataSet ( kIPTC_IntellectualGenre );
		return;
	}

	if ( ! XMP_PropIsSimple ( xmpFlags ) ) return;

	NormalizeToCR ( &xmpValue );

	int i;
	XMP_StringPtr namePtr = xmpValue.c_str();
	for ( i = 0; kIntellectualGenreMappings[i].name != 0; ++i ) {
		if ( strcmp ( namePtr, kIntellectualGenreMappings[i].name ) == 0 ) break;
	}
	if ( kIntellectualGenreMappings[i].name == 0 ) return;

	std::string iimValue = kIntellectualGenreMappings[i].refNum;
	iimValue += ':';
	iimValue += xmpValue;

	size_t iptcCount = iptc->GetDataSet ( kIPTC_IntellectualGenre, 0 );
	if ( iptcCount > 1 ) iptc->DeleteDataSet ( kIPTC_IntellectualGenre );

	iptc->SetDataSet_UTF8 ( kIPTC_IntellectualGenre, iimValue.c_str(), (XMP_Uns32)iimValue.size(), 0 );

}
