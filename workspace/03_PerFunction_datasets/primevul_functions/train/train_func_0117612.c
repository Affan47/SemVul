rrinternal_get_delims(sldns_rdf_type rdftype, size_t r_cnt, size_t r_max)
{
	switch(rdftype) {
	case LDNS_RDF_TYPE_B64        :
	case LDNS_RDF_TYPE_HEX        :
	case LDNS_RDF_TYPE_LOC        :
	case LDNS_RDF_TYPE_WKS        :
	case LDNS_RDF_TYPE_IPSECKEY   :
	case LDNS_RDF_TYPE_NSEC       :	if (r_cnt == r_max - 1) {
						return "\n";
					}
					break;
	default                       :	break;
	}
	return "\n\t ";
}
