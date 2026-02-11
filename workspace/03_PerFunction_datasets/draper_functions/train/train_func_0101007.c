free_fiber(fiberlampstruct *fl)
{
	if (fl->fiber) {
		int f;

		for (f = 0; f < fl->nfibers; f++) {
			fiberstruct *fs = fl->fiber + f;

			if (fs->node)
				free(fs->node);
			if (fs->draw)
				free(fs->draw);
		}
		free(fl->fiber);
		fl->fiber = NULL;
	}
}
