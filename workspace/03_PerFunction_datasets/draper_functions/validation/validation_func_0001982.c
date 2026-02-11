flickcurl_auth_checkToken(flickcurl* fc, const char* token)
{
  char *perms = NULL;
  xmlDocPtr doc = NULL;
  xmlXPathContextPtr xpathCtx = NULL;

  flickcurl_init_params(fc, 0);

  if(!token)
    return NULL;

  flickcurl_add_param(fc, "auth_token", (char*)token);

  flickcurl_end_params(fc);

  flickcurl_set_sign(fc);

  if(flickcurl_prepare(fc, "flickr.auth.checkToken"))
    goto tidy;

  doc = flickcurl_invoke(fc);
  if(!doc)
    goto tidy;

  xpathCtx = xmlXPathNewContext(doc);
  if(xpathCtx) {
    perms = flickcurl_xpath_eval(fc, xpathCtx,
                                    (const xmlChar*)"/rsp/auth/perms");
    xmlXPathFreeContext(xpathCtx);
  }

  tidy:

  return perms;
}
