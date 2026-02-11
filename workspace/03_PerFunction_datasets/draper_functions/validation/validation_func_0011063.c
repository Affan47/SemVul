gtk_sheet_move_child(GtkSheet *sheet, GtkWidget *widget, gint x, gint y)
{
  GtkSheetChild *child;
  GList *children;

  g_return_if_fail(sheet != NULL);
  g_return_if_fail(GTK_IS_SHEET(sheet));

  children = sheet->children;
  while(children)
    {
       child = children->data;

       if(child->widget == widget){
         child->x = x;
         child->y = y;
         child->row = ROW_FROM_YPIXEL(sheet, y);
	 child->col = COLUMN_FROM_XPIXEL(sheet, x);
         gtk_sheet_position_child(sheet, child);
         return;
       }

       children = g_list_next(children);
    }

  g_warning("Widget must be a GtkSheet child");

}
