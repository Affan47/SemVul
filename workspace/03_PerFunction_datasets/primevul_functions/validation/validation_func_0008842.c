static int hdrchkTagType(rpm_tag_t tag, rpm_tagtype_t type)
{
    rpmTagType t = rpmTagGetTagType(tag);
    if (t == type)
	return 0;


    if (t == RPM_NULL_TYPE)
	return 0;


    if (rpmTagGetClass(tag) == RPM_STRING_CLASS &&
	    (rpmTagTypeGetClass(type) == RPM_STRING_CLASS))
	return 0;


    return 1;
}
