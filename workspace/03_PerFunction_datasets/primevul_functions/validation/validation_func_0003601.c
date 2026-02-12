static int advance_multivolume(struct archive_read* a) {
	int lret;
	struct rar5* rar = get_context(a);


	while(1) {
		if(rar->main.endarc == 1) {
			int looping = 1;

			rar->main.endarc = 0;

			while(looping) {
				lret = skip_base_block(a);
				switch(lret) {
					case ARCHIVE_RETRY:

						break;
					case ARCHIVE_OK:

						looping = 0;
						break;
					default:


						return lret;
				}
			}

			break;
		} else {


			lret = skip_base_block(a);
			if(lret == ARCHIVE_FATAL || lret == ARCHIVE_FAILED)
				return lret;


			if(lret != ARCHIVE_RETRY) {


				if(rar->main.endarc == 0) {
					return lret;
				} else {
					continue;
				}
			}
		}
	}

	return ARCHIVE_OK;
}
