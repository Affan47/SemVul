readFile(ConvData *data, const char* converterName,
         UErrorCode *pErrorCode) {
    char line[200];
    char *end;
    FileStream *convFile;

    UCMStates *baseStates;
    UBool dataIsBase;

    if(U_FAILURE(*pErrorCode)) {
        return FALSE;
    }

    data->ucm=ucm_open();

    convFile=T_FileStream_open(converterName, "r");
    if(convFile==NULL) {
        *pErrorCode=U_FILE_ACCESS_ERROR;
        return FALSE;
    }

    readHeader(data, convFile, converterName, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return FALSE;
    }

    if(data->ucm->baseName[0]==0) {
        dataIsBase=TRUE;
        baseStates=&data->ucm->states;
        ucm_processStates(baseStates);
    } else {
        dataIsBase=FALSE;
        baseStates=NULL;
    }


    ucm_readTable(data->ucm, convFile, dataIsBase, baseStates, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return FALSE;
    }


    while(T_FileStream_readLine(convFile, line, sizeof(line))) {
        end=uprv_strchr(line, 0);
        while(line<end &&
              (*(end-1)=='\n' || *(end-1)=='\r' || *(end-1)==' ' || *(end-1)=='\t')) {
            --end;
        }
        *end=0;

        if(line[0]=='#' || u_skipWhitespace(line)==end) {
            continue;
        }

        if(0==uprv_strcmp(line, "CHARMAP")) {

            ucm_readTable(data->ucm, convFile, FALSE, baseStates, pErrorCode);
        } else {
            fprintf(stderr, "unexpected text after the base mapping table\n");
        }
        break;
    }

    T_FileStream_close(convFile);

    if(data->ucm->base->flagsType==UCM_FLAGS_MIXED || data->ucm->ext->flagsType==UCM_FLAGS_MIXED) {
        fprintf(stderr, "error: some entries have the mapping precision (with '|'), some do not\n");
        *pErrorCode=U_INVALID_TABLE_FORMAT;
    }

    return dataIsBase;
}
