_pi_handler(void *user, const xmlChar *target, const xmlChar *data)
{
	XML_Parser parser = (XML_Parser) user;

	if (parser->h_pi == NULL) {
		if (parser->h_default) {
			char    *full_pi;
			spprintf(&full_pi, 0, "<?%s %s?>", (char *)target, (char *)data);
			parser->h_default(parser->user, (const XML_Char *) full_pi, strlen(full_pi));
			efree(full_pi);
		}
		return;
	}

	parser->h_pi(parser->user, (const XML_Char *) target, (const XML_Char *) data);
}
