yaffs_load_config_file(TSK_IMG_INFO * a_img_info, std::map<std::string, std::string> & results){
    size_t config_file_name_len;
    TSK_TCHAR * config_file_name;
    FILE* config_file;
    char buf[1001];


    if(a_img_info->num_img < 1){
        return YAFFS_CONFIG_ERROR;
    }


    config_file_name_len = TSTRLEN(a_img_info->images[0]);
    config_file_name_len += TSTRLEN(YAFFS_CONFIG_FILE_SUFFIX);
    config_file_name = (TSK_TCHAR *) tsk_malloc(sizeof(TSK_TCHAR) * (config_file_name_len + 1));

    TSTRNCPY(config_file_name, a_img_info->images[0], TSTRLEN(a_img_info->images[0]) + 1);
    TSTRNCAT(config_file_name, YAFFS_CONFIG_FILE_SUFFIX, TSTRLEN(YAFFS_CONFIG_FILE_SUFFIX) + 1);

#ifdef TSK_WIN32
    HANDLE hWin;

    if ((hWin = CreateFile(config_file_name, GENERIC_READ,
            FILE_SHARE_READ, 0, OPEN_EXISTING, 0,
            0)) == INVALID_HANDLE_VALUE) {


        free(config_file_name);
        return YAFFS_CONFIG_FILE_NOT_FOUND;
    }
    config_file = _fdopen(_open_osfhandle((intptr_t) hWin, _O_RDONLY), "r");
    if (config_file == NULL) {
        tsk_error_reset();
        tsk_error_set_errno(TSK_ERR_FS);
        tsk_error_set_errstr(
                    "yaffs_load_config: Error converting Windows handle to C handle");
        free(config_file_name);
        CloseHandle(hWin);
        return YAFFS_CONFIG_ERROR;
    }
#else
    if (NULL == (config_file = fopen(config_file_name, "r"))) {
        free(config_file_name);
        return YAFFS_CONFIG_FILE_NOT_FOUND;
    }
#endif

    while(fgets(buf, 1000, config_file) != NULL){


        if((buf[0] == '#') || (buf[0] == ';')){
            continue;
        }


        if(strchr(buf, '=') == NULL){
            continue;
        }


        std::string paramName("");
        std::string paramVal("");

        const char * paramNamePtr = strtok(buf, "=");
        while(*paramNamePtr != '\0'){
            if(! isspace((char)(*paramNamePtr))){
                paramName += tolower((char)(*paramNamePtr));
            }
            paramNamePtr++;
        }

        const char * paramValPtr = strtok(NULL, "=");
        while(*paramValPtr != '\0'){
            if(! isspace(*paramValPtr)){
                paramVal += tolower((char)(*paramValPtr));
            }
            paramValPtr++;
        }


        if(results.find(paramName) != results.end()){

            tsk_error_reset();
            tsk_error_set_errno(TSK_ERR_FS);
            tsk_error_set_errstr(
                        "yaffs_load_config: Duplicate parameter name in config file (\"%s\"). %s", paramName.c_str(), YAFFS_HELP_MESSAGE);
            fclose(config_file);
            free(config_file_name);
            return YAFFS_CONFIG_ERROR;
        }


        results[paramName] = paramVal;
    }

    fclose(config_file);
    free(config_file_name);
    return YAFFS_CONFIG_OK;
}
