shots_show()
{
	ListEntry  *entry = game->shots->head->next;
	Shot       *shot;
	int        x, y;
	stk_surface_clip( stk_display, 0, 0,
			stk_display->w - BRICK_WIDTH, stk_display->h );
	while ( entry != game->shots->tail ) {
		shot = entry->item;
		entry = entry->next;
		x = (int)shot->x; y = (int)shot->y;
		stk_surface_alpha_blit( shot_shadow,
				0, 0, shot_w, shot_h,
				stk_display, x + shadow_size, y + shadow_size,
				SHADOW_ALPHA );
		stk_surface_alpha_blit( shot_pic, (int)shot->cur_fr * shot_w, 0,
				shot_w, shot_h, stk_display, x, y, shot_alpha );

		shot->update_rect.x = x;
		shot->update_rect.y = y;
		shot->update_rect.w = shot_w + shadow_size;
		shot->update_rect.h = shot_h + shadow_size;
		stk_display_store_rect( &shot->update_rect );
	}
	stk_surface_clip( stk_display, 0, 0, 0, 0 );
}
