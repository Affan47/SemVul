update_abs_pos(SpriteFrame *spriteFrame)
{
	if( !spriteFrame )
		spriteFrame = cur_sprite_frame();

	abs_x1 = cur_x + spriteFrame->offset_x;
	abs_y1 = cur_y + spriteFrame->offset_y;

	abs_x2 = abs_x1 + spriteFrame->width  - 1;
	abs_y2 = abs_y1 + spriteFrame->height - 1;
}
