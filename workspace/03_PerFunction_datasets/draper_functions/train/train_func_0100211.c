editor_draw_selrect(void)
{
  if (!editor) {
    return;
  }

  if (editor->selrect_active && editor->selrect_width > 0
      && editor->selrect_height > 0) {
    draw_selection_rectangle(editor->selrect_x,
                             editor->selrect_y,
                             editor->selrect_width,
                             editor->selrect_height);
  }
}
