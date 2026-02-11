soap_serialize_std__vectorTemplateOfPointerToa__address(struct soap *soap, const std::vector<a__address * >*a)
{
#ifndef WITH_NOIDREF
	for (std::vector<a__address * >::const_iterator i = a->begin(); i != a->end(); ++i)
		soap_serialize_PointerToa__address(soap, &(*i));
#endif
}
