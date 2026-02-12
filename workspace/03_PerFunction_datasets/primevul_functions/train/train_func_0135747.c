static UINT drive_process_irp_query_volume_information(DRIVE_DEVICE* drive, IRP* irp)
{
	UINT32 FsInformationClass;
	wStream* output = NULL;
	char* volumeLabel = { "FREERDP" };
	char* diskType = { "FAT32" };
	WCHAR* outStr = NULL;
	int length;
	DWORD lpSectorsPerCluster;
	DWORD lpBytesPerSector;
	DWORD lpNumberOfFreeClusters;
	DWORD lpTotalNumberOfClusters;
	WIN32_FILE_ATTRIBUTE_DATA wfad;

	if (!drive || !irp)
		return ERROR_INVALID_PARAMETER;

	output = irp->output;

	if (Stream_GetRemainingLength(irp->input) < 4)
		return ERROR_INVALID_DATA;

	Stream_Read_UINT32(irp->input, FsInformationClass);
	GetDiskFreeSpaceW(drive->path, &lpSectorsPerCluster, &lpBytesPerSector, &lpNumberOfFreeClusters,
	                  &lpTotalNumberOfClusters);

	switch (FsInformationClass)
	{
		case FileFsVolumeInformation:


			if ((length = ConvertToUnicode(sys_code_page, 0, volumeLabel, -1, &outStr, 0) * 2) <= 0)
			{
				WLog_ERR(TAG, "ConvertToUnicode failed!");
				return CHANNEL_RC_NO_MEMORY;
			}

			Stream_Write_UINT32(output, 17 + length);

			if (!Stream_EnsureRemainingCapacity(output, 17 + length))
			{
				WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
				free(outStr);
				return CHANNEL_RC_NO_MEMORY;
			}

			GetFileAttributesExW(drive->path, GetFileExInfoStandard, &wfad);
			Stream_Write_UINT32(output, wfad.ftCreationTime.dwLowDateTime);
			Stream_Write_UINT32(output,
			                    wfad.ftCreationTime.dwHighDateTime);
			Stream_Write_UINT32(output, lpNumberOfFreeClusters & 0xffff);
			Stream_Write_UINT32(output, length);
			Stream_Write_UINT8(output, 0);

			Stream_Write(output, outStr, length);
			free(outStr);
			break;

		case FileFsSizeInformation:

			Stream_Write_UINT32(output, 24);

			if (!Stream_EnsureRemainingCapacity(output, 24))
			{
				WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
				return CHANNEL_RC_NO_MEMORY;
			}

			Stream_Write_UINT64(output, lpTotalNumberOfClusters);
			Stream_Write_UINT64(output, lpNumberOfFreeClusters);
			Stream_Write_UINT32(output, lpSectorsPerCluster);
			Stream_Write_UINT32(output, lpBytesPerSector);
			break;

		case FileFsAttributeInformation:


			if ((length = ConvertToUnicode(sys_code_page, 0, diskType, -1, &outStr, 0) * 2) <= 0)
			{
				WLog_ERR(TAG, "ConvertToUnicode failed!");
				return CHANNEL_RC_NO_MEMORY;
			}

			Stream_Write_UINT32(output, 12 + length);

			if (!Stream_EnsureRemainingCapacity(output, 12 + length))
			{
				free(outStr);
				WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
				return CHANNEL_RC_NO_MEMORY;
			}

			Stream_Write_UINT32(output, FILE_CASE_SENSITIVE_SEARCH | FILE_CASE_PRESERVED_NAMES |
			                                FILE_UNICODE_ON_DISK);
			Stream_Write_UINT32(output, MAX_PATH);
			Stream_Write_UINT32(output, length);
			Stream_Write(output, outStr, length);
			free(outStr);
			break;

		case FileFsFullSizeInformation:

			Stream_Write_UINT32(output, 32);

			if (!Stream_EnsureRemainingCapacity(output, 32))
			{
				WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
				return CHANNEL_RC_NO_MEMORY;
			}

			Stream_Write_UINT64(output, lpTotalNumberOfClusters);
			Stream_Write_UINT64(output,
			                    lpNumberOfFreeClusters);
			Stream_Write_UINT64(output, lpNumberOfFreeClusters);
			Stream_Write_UINT32(output, lpSectorsPerCluster);
			Stream_Write_UINT32(output, lpBytesPerSector);
			break;

		case FileFsDeviceInformation:

			Stream_Write_UINT32(output, 8);

			if (!Stream_EnsureRemainingCapacity(output, 8))
			{
				WLog_ERR(TAG, "Stream_EnsureRemainingCapacity failed!");
				return CHANNEL_RC_NO_MEMORY;
			}

			Stream_Write_UINT32(output, FILE_DEVICE_DISK);
			Stream_Write_UINT32(output, 0);
			break;

		default:
			irp->IoStatus = STATUS_UNSUCCESSFUL;
			Stream_Write_UINT32(output, 0);
			break;
	}

	return irp->Complete(irp);
}
