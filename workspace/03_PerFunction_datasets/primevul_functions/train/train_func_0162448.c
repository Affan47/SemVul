static void drawpage(fz_context *ctx, fz_document *doc, int pagenum)
{
	fz_page *page;
	fz_display_list *list = NULL;
	fz_device *list_dev = NULL;
	int start;
	fz_cookie cookie = { 0 };
#if GREY_FALLBACK != 0
	fz_device *test_dev = NULL;
	int is_color = 0;
#else
	int is_color = 2;
#endif
	render_details render;
	int status;

	fz_var(list);
	fz_var(list_dev);
	fz_var(test_dev);

	do
	{
		start = (showtime ? gettime() : 0);

		page = fz_load_page(ctx, doc, pagenum - 1);


		get_page_render_details(ctx, page, &render);


		fz_try(ctx)
		{
			list = fz_new_display_list(ctx, render.bounds);
			list_dev = fz_new_list_device(ctx, list);
#if GREY_FALLBACK != 0
			test_dev = fz_new_test_device(ctx, &is_color, 0.01f, 0, list_dev);
			fz_run_page(ctx, page, test_dev, fz_identity, &cookie);
			fz_close_device(ctx, test_dev);
#else
			fz_run_page(ctx, page, list_dev, fz_identity, &cookie);
#endif
			fz_close_device(ctx, list_dev);
		}
		fz_always(ctx)
		{
#if GREY_FALLBACK != 0
			fz_drop_device(ctx, test_dev);
#endif
			fz_drop_device(ctx, list_dev);
		}
		fz_catch(ctx)
		{
			fz_drop_display_list(ctx, list);
			list = NULL;


			render.num_workers = 1;
		}
		render.list = list;

#if GREY_FALLBACK != 0
		if (list == NULL)
		{


			fz_try(ctx)
			{
				test_dev = fz_new_test_device(ctx, &is_color, 0.01f, 0, NULL);
				fz_run_page(ctx, page, test_dev, fz_identity, &cookie);
				fz_close_device(ctx, test_dev);
			}
			fz_always(ctx)
			{
				fz_drop_device(ctx, test_dev);
			}
			fz_catch(ctx)
			{

				fz_drop_page(ctx, page);
				fz_rethrow(ctx);
			}
		}
#endif

#if GREY_FALLBACK == 2

		if (is_color == 1)
		{


			is_color = 0;
			fz_try(ctx)
			{
				test_dev = fz_new_test_device(ctx, &is_color, 0.01f, FZ_TEST_OPT_IMAGES | FZ_TEST_OPT_SHADINGS, NULL);
				if (list)
					fz_run_display_list(ctx, list, test_dev, &fz_identity, &fz_infinite_rect, &cookie);
				else
					fz_run_page(ctx, page, test_dev, &fz_identity, &cookie);
				fz_close_device(ctx, test_dev);
			}
			fz_always(ctx)
			{
				fz_drop_device(ctx, test_dev);
			}
			fz_catch(ctx)
			{
				fz_drop_display_list(ctx, list);
				fz_drop_page(ctx, page);
				fz_rethrow(ctx);
			}
		}
#endif


		initialise_banding(ctx, &render, is_color);

		if (bgprint.active && showtime)
		{
			int end = gettime();
			start = end - start;
		}


		if (!bgprint.active)
			break;


		status = wait_for_bgprint_to_finish();
		if (status == RENDER_OK)
		{


			break;
		}


		fz_drop_display_list(ctx, list);
		fz_drop_page(ctx, page);

		if (status == RENDER_FATAL)
		{

			fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
		}
		bgprint.started = 1;
		bgprint.solo = 1;
		mu_trigger_semaphore(&bgprint.start);
		status = wait_for_bgprint_to_finish();
		if (status != 0)
		{

			fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
		}

	}
	while (1);

	if (showtime)
	{
		fprintf(stderr, "page %s %d", filename, pagenum);
	}
	if (bgprint.active)
	{
		bgprint.started = 1;
		bgprint.solo = 0;
		bgprint.render = render;
		bgprint.filename = filename;
		bgprint.pagenum = pagenum;
		bgprint.interptime = start;
		mu_trigger_semaphore(&bgprint.start);
	}
	else
	{
		if (try_render_page(ctx, pagenum, &cookie, start, 0, filename, 0, 0, &render))
		{

			fz_throw(ctx, FZ_ERROR_GENERIC, "Failed to render page");
		}
	}
}
