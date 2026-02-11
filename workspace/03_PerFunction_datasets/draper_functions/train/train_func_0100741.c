hdspm_pref_sync_ref(struct hdspm * hdspm)
{
	switch (hdspm->io_type) {
	case AES32:
		switch (hdspm->control_register & HDSPM_SyncRefMask) {
		case 0: return 0;
		case HDSPM_SyncRef0: return 1;
		case HDSPM_SyncRef1: return 2;
		case HDSPM_SyncRef1+HDSPM_SyncRef0: return 3;
		case HDSPM_SyncRef2: return 4;
		case HDSPM_SyncRef2+HDSPM_SyncRef0: return 5;
		case HDSPM_SyncRef2+HDSPM_SyncRef1: return 6;
		case HDSPM_SyncRef2+HDSPM_SyncRef1+HDSPM_SyncRef0:
						    return 7;
		case HDSPM_SyncRef3: return 8;
		case HDSPM_SyncRef3+HDSPM_SyncRef0: return 9;
		}
		break;

	case MADI:
	case MADIface:
		if (hdspm->tco) {
			switch (hdspm->control_register & HDSPM_SyncRefMask) {
			case 0: return 0;
			case HDSPM_SyncRef0: return 1;
			case HDSPM_SyncRef1: return 2;
			case HDSPM_SyncRef1+HDSPM_SyncRef0:
					     return 3;
			}
		} else {
			switch (hdspm->control_register & HDSPM_SyncRefMask) {
			case 0: return 0;
			case HDSPM_SyncRef0: return 1;
			case HDSPM_SyncRef1+HDSPM_SyncRef0:
					     return 2;
			}
		}
		break;

	case RayDAT:
		if (hdspm->tco) {
			switch ((hdspm->settings_register &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) {
			case 0: return 0;
			case 3: return 1;
			case 4: return 2;
			case 5: return 3;
			case 6: return 4;
			case 1: return 5;
			case 2: return 6;
			case 9: return 7;
			case 10: return 8;
			}
		} else {
			switch ((hdspm->settings_register &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) {
			case 0: return 0;
			case 3: return 1;
			case 4: return 2;
			case 5: return 3;
			case 6: return 4;
			case 1: return 5;
			case 2: return 6;
			case 10: return 7;
			}
		}

		break;

	case AIO:
		if (hdspm->tco) {
			switch ((hdspm->settings_register &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) {
			case 0: return 0;
			case 3: return 1;
			case 1: return 2;
			case 2: return 3;
			case 9: return 4;
			case 10: return 5;
			}
		} else {
			switch ((hdspm->settings_register &
				HDSPM_c0_SyncRefMask) / HDSPM_c0_SyncRef0) {
			case 0: return 0;
			case 3: return 1;
			case 1: return 2;
			case 2: return 3;
			case 10: return 4;
			}
		}

		break;
	}

	return -1;
}
