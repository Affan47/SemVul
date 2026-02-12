static int try_render_page(fz_context *ctx, int pagenum, fz_cookie *cookie, int start, int interptime, char *fname, int bg, int solo, render_details *render)
{
	int status;

	if (out && !(bg && solo))
	{


		fz_try(ctx)
		{
			int w = render->ibounds.x1 - render->ibounds.x0;
			int h = render->ibounds.y1 - render->ibounds.y0;
			fz_write_header(ctx, render->bander, w, h, render->n, 0, 0, 0, 0, 0, NULL);
		}
		fz_catch(ctx)
		{

			return RENDER_FATAL;
		}
	}

	while (1)
	{
		status = dodrawpage(ctx, pagenum, cookie, render);
		if (status == RENDER_OK || status == RENDER_FATAL)
			break;


		if (bg && !solo)
		{
			DEBUG_THREADS(("Render failure; trying again in solo mode\n"));
			return RENDER_RETRY;
		}


		if (render->num_workers > 1)
		{
			render->num_workers >>= 1;
			DEBUG_THREADS(("Render failure; trying again with %d render threads\n", render->num_workers));
			continue;
		}


		if (render->band_height_multiple > 2)
		{
			render->band_height_multiple >>= 1;
			DEBUG_THREADS(("Render failure; trying again with %d band height multiple\n", render->band_height_multiple));
			continue;
		}


		if (render->list)
		{
			fz_drop_display_list(ctx, render->list);
			render->list = NULL;
			DEBUG_THREADS(("Render failure; trying again with no list\n"));
			continue;
		}


		DEBUG_THREADS(("Render failure; nothing else to try\n"));
		break;
	}

	fz_close_band_writer(ctx, render->bander);

	fz_drop_page(ctx, render->page);
	fz_drop_display_list(ctx, render->list);
	fz_drop_band_writer(ctx, render->bander);

	if (showtime)
	{
		int end = gettime();
		int diff = end - start;

		if (bg)
		{
			if (diff + interptime < timing.min)
			{
				timing.min = diff + interptime;
				timing.mininterp = interptime;
				timing.minpage = pagenum;
				timing.minfilename = fname;
			}
			if (diff + interptime > timing.max)
			{
				timing.max = diff + interptime;
				timing.maxinterp = interptime;
				timing.maxpage = pagenum;
				timing.maxfilename = fname;
			}
			timing.total += diff + interptime;
			timing.count ++;

			fprintf(stderr, " %dms (interpretation) %dms (rendering) %dms (total)\n", interptime, diff, diff + interptime);
		}
		else
		{
			if (diff < timing.min)
			{
				timing.min = diff;
				timing.minpage = pagenum;
				timing.minfilename = fname;
			}
			if (diff > timing.max)
			{
				timing.max = diff;
				timing.maxpage = pagenum;
				timing.maxfilename = fname;
			}
			timing.total += diff;
			timing.count ++;

			fprintf(stderr, " %dms\n", diff);
		}
	}

	if (showmemory)
	{
		fz_dump_glyph_cache_stats(ctx, fz_stderr(ctx));
	}

	fz_flush_warnings(ctx);

	return status;
}
