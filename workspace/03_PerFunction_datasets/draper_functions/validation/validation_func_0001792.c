lpr(fz_context *ctx, pdf_obj *node, int depth, int page)
{
	pdf_obj *kids;
	pdf_obj *o = NULL;
	int i, n;

	if (pdf_dict_mark(node))
		return page;

	fz_var(o);

	fz_try(ctx)
	{
		if (!strcmp("Page", pdf_to_name(pdf_dict_gets(node, "Type"))))
		{
			pdf_obj *r;


			o = pdf_keep_obj(pdf_dict_gets(node, "Resources"));
			if (!o)
			{
				o = pdf_keep_obj(pdf_new_dict(ctx, 2));
				pdf_dict_puts(node, "Resources", o);
			}
			lpr_inherit_res(ctx, node, depth, o);
			r = lpr_inherit(ctx, node, "MediaBox", depth);
			if (r)
				pdf_dict_puts(node, "MediaBox", r);
			r = lpr_inherit(ctx, node, "CropBox", depth);
			if (r)
				pdf_dict_puts(node, "CropBox", r);
			r = lpr_inherit(ctx, node, "BleedBox", depth);
			if (r)
				pdf_dict_puts(node, "BleedBox", r);
			r = lpr_inherit(ctx, node, "TrimBox", depth);
			if (r)
				pdf_dict_puts(node, "TrimBox", r);
			r = lpr_inherit(ctx, node, "ArtBox", depth);
			if (r)
				pdf_dict_puts(node, "ArtBox", r);
			r = lpr_inherit(ctx, node, "Rotate", depth);
			if (r)
				pdf_dict_puts(node, "Rotate", r);
			page++;
		}
		else
		{
			kids = pdf_dict_gets(node, "Kids");
			n = pdf_array_len(kids);
			for(i = 0; i < n; i++)
			{
				page = lpr(ctx, pdf_array_get(kids, i), depth+1, page);
			}
			pdf_dict_dels(node, "Resources");
			pdf_dict_dels(node, "MediaBox");
			pdf_dict_dels(node, "CropBox");
			pdf_dict_dels(node, "BleedBox");
			pdf_dict_dels(node, "TrimBox");
			pdf_dict_dels(node, "ArtBox");
			pdf_dict_dels(node, "Rotate");
		}
	}
	fz_always(ctx)
	{
		pdf_drop_obj(o);
	}
	fz_catch(ctx)
	{
		fz_rethrow(ctx);
	}

	pdf_dict_unmark(node);

	return page;
}
