gsf_opendoc_metadata_subtree_internal (GsfXMLIn *xin, G_GNUC_UNUSED xmlChar const **attrs)
{
	if (NULL == doc_subtree)
		doc_subtree = gsf_xml_in_doc_new (gsf_opendoc_meta_st_dtd, gsf_ooo_ns);

	gsf_xml_in_push_state (xin, doc_subtree, NULL, NULL, NULL);
}
