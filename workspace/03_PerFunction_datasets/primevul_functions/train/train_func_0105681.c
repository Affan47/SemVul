static void CMSError(cmsContext , cmsUInt32Number , const char *text)
{
    error(errSyntaxWarning, -1, "{0:s}", text);
}
