FCEUMOV_PostLoad(void)
{
	if(movieMode == MOVIEMODE_INACTIVE || movieMode == MOVIEMODE_TASEDITOR)
		return true;
	else
		return load_successful;
}
