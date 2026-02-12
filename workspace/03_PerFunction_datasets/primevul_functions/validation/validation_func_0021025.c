static char* object_string(ASN1_TYPE* object)
{
	char* result;
	unsigned char* utf8String;
	int length;

	length = ASN1_STRING_to_UTF8(&utf8String, object->value.asn1_string);

	if (length < 0)
	{
		return 0;
	}

	result = (char*)_strdup((char*)utf8String);
	OPENSSL_free(utf8String);
	return result;
}
