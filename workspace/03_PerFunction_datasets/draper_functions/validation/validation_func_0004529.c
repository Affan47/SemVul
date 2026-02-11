AddFileListItemInfo(FileListInfoPtr fileListInfoPtr, char* name,
					unsigned int size, unsigned int data)
{
	FileListItemInfoPtr fileListItemInfoPtr = (FileListItemInfoPtr)
												calloc((fileListInfoPtr->numEntries + 1),
														sizeof(FileListItemInfo));
	if(fileListItemInfoPtr == NULL) {
	    rfbLog("File [%s]: Method [%s]: fileListItemInfoPtr is NULL\n",
	    		__FILE__, __FUNCTION__);
		return FAILURE;
	}

	if(fileListInfoPtr->numEntries != 0) {
	    memcpy(fileListItemInfoPtr, fileListInfoPtr->pEntries,
	    		fileListInfoPtr->numEntries * sizeof(FileListItemInfo));
	}

	strcpy(fileListItemInfoPtr[fileListInfoPtr->numEntries].name, name);
	fileListItemInfoPtr[fileListInfoPtr->numEntries].size = size;
	fileListItemInfoPtr[fileListInfoPtr->numEntries].data = data;

	if(fileListInfoPtr->pEntries != NULL) {
	    free(fileListInfoPtr->pEntries);
	    fileListInfoPtr->pEntries = NULL;
	}

	fileListInfoPtr->pEntries = fileListItemInfoPtr;
	fileListItemInfoPtr = NULL;
	fileListInfoPtr->numEntries++;

	return SUCCESS;
}
