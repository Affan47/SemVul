ld10k1_tram_realloc_space(ld10k1_dsp_mgr_t *dsp_mgr, ld10k1_dsp_tram_resolve_t *res)
{
	int itram_size = res->isize;
	int etram_size = res->esize;
	int i;


	for (i = 0; i < dsp_mgr->max_tram_grp; i++)
		if (dsp_mgr->tram_grp[i].used) {
			if (dsp_mgr->tram_grp[i].pos == TRAM_POS_INTERNAL) {
				itram_size -= dsp_mgr->tram_grp[i].size;
				dsp_mgr->tram_grp[i].offset = itram_size;
			} else if (dsp_mgr->tram_grp[i].pos == TRAM_POS_EXTERNAL) {
				etram_size -= dsp_mgr->tram_grp[i].size;
				dsp_mgr->tram_grp[i].offset = etram_size;
			}
		}

	return 0;
}
