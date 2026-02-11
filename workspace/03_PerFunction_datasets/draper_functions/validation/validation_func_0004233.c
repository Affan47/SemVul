ahc_free(struct ahc_softc *ahc)
{
	int i;

	switch (ahc->init_level) {
	default:
	case 5:
		ahc_shutdown(ahc);

	case 4:
		ahc_dmamap_unload(ahc, ahc->shared_data_dmat,
				  ahc->shared_data_dmamap);

	case 3:
		ahc_dmamem_free(ahc, ahc->shared_data_dmat, ahc->qoutfifo,
				ahc->shared_data_dmamap);
		ahc_dmamap_destroy(ahc, ahc->shared_data_dmat,
				   ahc->shared_data_dmamap);

	case 2:
		ahc_dma_tag_destroy(ahc, ahc->shared_data_dmat);
	case 1:
#ifndef __linux__
		ahc_dma_tag_destroy(ahc, ahc->buffer_dmat);
#endif
		break;
	case 0:
		break;
	}

#ifndef __linux__
	ahc_dma_tag_destroy(ahc, ahc->parent_dmat);
#endif
	ahc_platform_free(ahc);
	ahc_fini_scbdata(ahc);
	for (i = 0; i < AHC_NUM_TARGETS; i++) {
		struct ahc_tmode_tstate *tstate;

		tstate = ahc->enabled_targets[i];
		if (tstate != NULL) {
#ifdef AHC_TARGET_MODE
			int j;

			for (j = 0; j < AHC_NUM_LUNS; j++) {
				struct ahc_tmode_lstate *lstate;

				lstate = tstate->enabled_luns[j];
				if (lstate != NULL) {
					xpt_free_path(lstate->path);
					kfree(lstate);
				}
			}
#endif
			kfree(tstate);
		}
	}
#ifdef AHC_TARGET_MODE
	if (ahc->black_hole != NULL) {
		xpt_free_path(ahc->black_hole->path);
		kfree(ahc->black_hole);
	}
#endif
	if (ahc->name != NULL)
		kfree(ahc->name);
	if (ahc->seep_config != NULL)
		kfree(ahc->seep_config);
#ifndef __FreeBSD__
	kfree(ahc);
#endif
	return;
}
