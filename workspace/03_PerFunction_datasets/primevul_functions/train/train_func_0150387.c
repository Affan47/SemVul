int findDirContainingFile(J9StringBuffer **result, char *paths, char pathSeparator, char *fileToFind, int elementsToSkip) {
	char *startOfDir, *endOfDir, *pathsCopy;
	int   isEndOfPaths, foundIt, count=elementsToSkip;


	paths = strdup(paths);
	if (!paths) {
		return FALSE;
	}

	pathsCopy = paths;
	while(elementsToSkip--) {
		pathsCopy = strchr(pathsCopy, pathSeparator);
		if(pathsCopy) {
			pathsCopy++;
		} else {
			free(paths);
			return 0;
		}
	}


	startOfDir = endOfDir = pathsCopy;
	for (isEndOfPaths=FALSE, foundIt=FALSE; !foundIt && !isEndOfPaths; endOfDir++) {

		isEndOfPaths = endOfDir[0] == '\0';
		if (isEndOfPaths || (endOfDir[0] == pathSeparator))  {
			endOfDir[0] = '\0';
			if (strlen(startOfDir) && isFileInDir(startOfDir, fileToFind)) {
				foundIt = TRUE;
				if (NULL != *result) {
					free(*result);
					*result = NULL;
				}
				*result = jvmBufferCat(NULL, startOfDir);
			}
			startOfDir = endOfDir+1;
			count+=1;
		}
	}

	free(paths);
	if(foundIt) {
		return count;
	} else {
		return 0;
	}
}
