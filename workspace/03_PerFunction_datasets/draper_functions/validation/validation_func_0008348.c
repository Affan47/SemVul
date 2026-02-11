RenderText(SDL_Surface *Surface, const PG_Rect *ClipRect, int BaseLineX, int BaseLineY, const PG_String& Text, PG_Font* font) {
	static bool bRecursion = false;
	int OriBaseX = BaseLineX;
	FT_UInt previous = 0;

	PG_FontFaceCacheItem* FaceCache = font->GetFaceCache();


	if (FaceCache == NULL) {
		return false;
	}

	FT_Face Face = FaceCache->Face;
	FT_Vector  delta;

	if(SDL_MUSTLOCK(Surface)) {
		SDL_LockSurface(Surface);
	}

	Uint32 c0;


	int len = Text.size();
	for(int i = 0; i < len; i++) {
		int glyph_index;
		PG_GlyphCacheItem* Glyph;
		int OldBaseLineX = BaseLineX;

      c0 = (PG_Char)(Text[i]);


		if (c0 < 32) {
			continue;
		}


		glyph_index = FT_Get_Char_Index(Face, c0);


		if ( FaceCache->Use_Kerning && previous && glyph_index ) {
			FT_Get_Kerning(Face, previous, glyph_index, ft_kerning_default, &delta );
			BaseLineX += delta.x >> 6;
		}
		previous = glyph_index;


		Glyph = GetGlyph(font, glyph_index);


		if (c0 != ' ') {
			BlitFTBitmap(Surface, &Glyph->Bitmap, BaseLineX + Glyph->Bitmap_left, BaseLineY - Glyph->Bitmap_top, font, ClipRect);
		}

		BaseLineX += Glyph->Advance_x;
		if (font->GetStyle() & PG_Font::BOLD) {
			BaseLineX += FaceCache->Bold_Offset;
		}


		if (font->GetStyle() & PG_Font::UNDERLINE) {
			SDL_Rect	und_rect;

			und_rect.x = OldBaseLineX;
			und_rect.y = BaseLineY;
			und_rect.h = FaceCache->Underline_Height;
			und_rect.w = BaseLineX - OldBaseLineX;

			SDL_FillRect(
			    Surface,
			    &und_rect,
			    font->GetColor().MapRGB(Surface->format)
			);
		}
	}


	if (font->GetStyle() & PG_Font::BOLD && !bRecursion) {
		bRecursion = true;
		RenderText(Surface, ClipRect, OriBaseX+1, BaseLineY, Text, font);
		bRecursion = false;
	}

	if(SDL_MUSTLOCK(Surface)) {
		SDL_UnlockSurface(Surface);
	}

	return true;
}
