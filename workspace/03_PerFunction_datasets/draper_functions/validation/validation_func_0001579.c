LOC_pad_current(char *name)
{
    if (curpad == NULL) {
	*name = '\0';
	return NO_CUR_PAD;
    }
    else {
	strcpy(name, curpad->name);
	return OK;
    }
}
