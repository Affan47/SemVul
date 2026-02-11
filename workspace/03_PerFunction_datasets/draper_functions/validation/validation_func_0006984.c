directory_list_rewind(directory_list_ty *dlp)
{
    size_t          j;

    for (j = 0; j < dlp->length; ++j)
	directory_destructor(dlp->item + j);
    dlp->length = 0;
}
