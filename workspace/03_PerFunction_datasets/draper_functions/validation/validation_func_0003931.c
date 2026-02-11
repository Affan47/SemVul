isSSL(const char* URL)
{
	return URL ? !strncmp(https,URL,https_len) : 0;
}
