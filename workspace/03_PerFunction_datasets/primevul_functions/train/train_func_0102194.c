make_case_word(char_u *fword, char_u *cword, int flags)
{
    if (flags & WF_ALLCAP)

	allcap_copy(fword, cword);
    else if (flags & WF_ONECAP)

	onecap_copy(fword, cword, TRUE);
    else

	STRCPY(cword, fword);
}
