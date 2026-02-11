check_file_path(book, content_type, path)
    Book *book;
    EBNet_Content_Type content_type;
    const char *path;
{
    char subbook_name[EB_MAX_FILE_NAME_LENGTH + 1];
    size_t subbook_name_length;
    EBNet_Error_Code error_code;
    char *slash;

    if (*path != '/')
	return EBNET_ERROR_BAD_PATH;

    slash = strchr(path + 1, '/');
    if (slash == NULL) {


	error_code = check_root_file_name(path + 1);
	if (error_code != EBNET_ERROR_OK)
	    return error_code;
    } else {


	subbook_name_length = slash - (path + 1);
	if (subbook_name_length == 0
	    || EB_MAX_DIRECTORY_NAME_LENGTH < subbook_name_length)
	    return EBNET_ERROR_BAD_SUBBOOK_NAME;
	memcpy(subbook_name, path + 1, subbook_name_length);
	*(subbook_name + subbook_name_length) = '\0';

	error_code = check_subbook_name(book, content_type, subbook_name);
	if (error_code != EBNET_ERROR_OK)
	    return error_code;


	error_code = check_path_parent_directory(slash);
	if (error_code != EBNET_ERROR_OK)
	    return error_code;
    }

    return EBNET_ERROR_OK;
}
