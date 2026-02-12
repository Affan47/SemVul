DWORD VDir::CalculateEnvironmentSpace(void)
{
    int index;
    DWORD dwSize = 0;
    for (index = 0; index < driveCount; ++index) {
	if (dirTableA[index] != NULL) {
	    dwSize += strlen(dirTableA[index]) + 5;
	}
    }
    return dwSize;
}
