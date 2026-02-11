ItemName_Draw (menuitem_s *a, FNT_font_t font, const float *color)
{
	int text_x, text_y;
	unsigned int align, cmode;

	if (a->generic.namedraw != NULL)
	{
		a->generic.namedraw (a, font);
		return;
	}

	if (a->generic.name == NULL)
		return;

	text_x = Item_GetX (*a);
	text_y = Item_GetY (*a) + MenuText_UpperMargin (a, font->size);

	if ((a->generic.flags & QMF_BUTTON))
	{
		int border_x, width;

		width = CHASELINK(a->generic.lsize).x+CHASELINK(a->generic.rsize).x;

		if (!a->generic.parent->horizontal)
		{
			align = FNT_ALIGN_CENTER;
			text_x = a->generic.parent->x + width/2;
			border_x = a->generic.parent->x;
		}
		else
		{
			align = FNT_ALIGN_RIGHT;
			border_x = text_x - width + RCOLUMN_OFFSET/2;
		}


		if (color == dark_color)
			Menu_DrawHorizBar ("menu/button_border", border_x, Item_GetY(*a)+2, width, font->height*2-4, a->generic.highlight_alpha*a->generic.highlight_alpha);
	}
	else if ( a->generic.flags & QMF_RIGHT_COLUMN )
	{
		align = FNT_ALIGN_LEFT;
	}
	else
	{
		if (a->generic.parent->horizontal)
		{
			align = FNT_ALIGN_RIGHT;
			text_x += LCOLUMN_OFFSET;
		}
		else
		{
			align = FNT_ALIGN_LEFT;
			text_x = a->generic.parent->x;
		}
	}

	if ( a->generic.flags & QMF_STRIP_COLOR || color == highlight_color )
		cmode = FNT_CMODE_TWO;
	else
		cmode = FNT_CMODE_QUAKE_SRS;

	Menu_DrawString (
		text_x, text_y,
		a->generic.name, cmode, align, color
	);
}
