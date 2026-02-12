static bool map_info2_flags_to_sbuf(const SMB_STRUCT_STAT *psbuf,
				const uint32_t smb_fflags,
				const uint32_t smb_fmask,
				int *stat_fflags)
{
	uint32_t max_fmask = 0;
	int i;

	*stat_fflags = psbuf->st_ex_flags;


	for (i = 0; i < ARRAY_SIZE(info2_flags_map); ++i) {
	    max_fmask |= info2_flags_map[i].smb_fflag;
	    if (smb_fmask & info2_flags_map[i].smb_fflag) {
		    if (smb_fflags & info2_flags_map[i].smb_fflag) {
			    *stat_fflags |= info2_flags_map[i].stat_fflag;
		    } else {
			    *stat_fflags &= ~info2_flags_map[i].stat_fflag;
		    }
	    }
	}


	if ((smb_fmask & max_fmask) != smb_fmask) {
		return False;
	}

	return True;
}
