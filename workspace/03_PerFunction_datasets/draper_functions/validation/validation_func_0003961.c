CmiCompareHash(
	IN PCUNICODE_STRING KeyName,
	IN PCHAR HashString)
{
	CHAR Buffer[4];

	Buffer[0] = (KeyName->Length >= 2) ? (CHAR)KeyName->Buffer[0] : 0;
	Buffer[1] = (KeyName->Length >= 4) ? (CHAR)KeyName->Buffer[1] : 0;
	Buffer[2] = (KeyName->Length >= 6) ? (CHAR)KeyName->Buffer[2] : 0;
	Buffer[3] = (KeyName->Length >= 8) ? (CHAR)KeyName->Buffer[3] : 0;

	return (strncmp(Buffer, HashString, 4) == 0);
}
