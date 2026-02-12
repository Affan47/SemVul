bool ContentSettingsObserver::IsWhitelistedForContentSettings(
    const WebSecurityOrigin& origin,
    const GURL& document_url) {
  if (document_url == GURL(content::kUnreachableWebDataURL))
    return true;

  if (origin.IsUnique())
    return false;

  base::string16 protocol = origin.Protocol().Utf16();
  if (base::EqualsASCII(protocol, content::kChromeUIScheme))
    return true;

  if (base::EqualsASCII(protocol, content::kChromeDevToolsScheme))
    return true;

#if BUILDFLAG(ENABLE_EXTENSIONS)
  if (base::EqualsASCII(protocol, extensions::kExtensionScheme))
    return true;
#endif


  if (base::EqualsASCII(protocol, url::kFileScheme)) {
    return document_url.SchemeIs(url::kFileScheme) &&
           document_url.ExtractFileName().empty();
  }

  return false;
}
