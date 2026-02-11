inExceptionFileSiteList(String url)
{
	if (inSiteList(url, exception_file_site_list) != NULL)
		return true;
	else
		return inURLList(url, exception_file_url_list) != NULL;
}
