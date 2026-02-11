label_write( Label *label, Font *_font, const char *text )
{
    Font *font = _font;
    if ( font == 0 ) font = label->def_font;
    font->align = ALIGN_X_CENTER | ALIGN_Y_CENTER;
    SDL_FillRect( label->frame->contents, 0, 0x0 );
    write_text( font, label->frame->contents, label->frame->contents->w >> 1, label->frame->contents->h >> 1, text, 255 );
    frame_apply( label->frame );
    frame_hide( label->frame, 0 );
}
