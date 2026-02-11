Devices_H_Special(void)
{
	if (devbug)
		Log_print("HHSPEC");

	switch (MEMORY_dGetByte(Devices_ICCOMZ)) {
#ifdef DO_RENAME
	case 0x20:
		Devices_H_Rename();
		return;
#endif
#ifdef HAVE_UTIL_UNLINK
	case 0x21:
		Devices_H_Delete();
		return;
#endif
#ifdef DO_LOCK
	case 0x23:
		Devices_H_Lock();
		return;
	case 0x24:
		Devices_H_Unlock();
		return;
#endif
	case 0x26:
		Devices_H_Note();
		return;
	case 0x25:
		Devices_H_Point();
		return;
	case 0x27:
		Devices_H_FileLength();
		return;
	case 0x28:
		Devices_H_Load(FALSE);
		return;
#ifdef DO_MKDIR
	case 0x22:
	case 0x2a:
		Devices_H_MakeDirectory();
		return;
#endif
#ifdef DO_RMDIR
	case 0x2b:
		Devices_H_RemoveDirectory();
		return;
#endif
	case 0x29:
	case 0x2c:
		Devices_H_ChangeDirectory();
		return;
	case 0x2f:
		Devices_H_DiskInfo();
		return;
	case 0x30:
		Devices_H_ToAbsolutePath();
		return;
	case 0xfe:
		if (devbug)
			Log_print("FORMAT Command");
		break;
	default:
		if (devbug)
			Log_print("UNKNOWN Command %02X", MEMORY_dGetByte(Devices_ICCOMZ));
		break;
	}

	CPU_regY = 168;
	CPU_SetN;
}
