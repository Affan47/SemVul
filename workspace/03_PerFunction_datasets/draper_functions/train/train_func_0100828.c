panel_fit_number(buf, number, flags, maxlen)
    char *buf;
    off64_t number;
    int flags;
    int maxlen;
{
    char *str=NULL;
    int scaled=(flags & human_autoscale);
    str=panel_beautify_number(buf,number,(flags | (GroupDigits ? human_group_digits : 0)));

    if((str == NULL) || (strlen(str) > maxlen))
    {
	scaled=1;
	str=panel_beautify_number(buf, number, (flags|human_autoscale|human_SI|human_base_1024));
    }
    strncpy(buf,str,maxlen);

    buf[maxlen]='\0';
    return scaled;
}
