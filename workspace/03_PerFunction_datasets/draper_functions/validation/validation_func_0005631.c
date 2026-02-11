AddItem(unsigned long id, unsigned long fid, unsigned long flags)
{
  struct icon_info *new, *tmp;
  tmp = Head;

  if (id == main_win || (flags & TRANSIENT))
    return False;

  while (tmp != NULL){
    if (tmp->id == id ||
	(tmp->wmhints && (tmp->wmhints->flags & IconWindowHint) &&
	 tmp->wmhints->icon_window == id))
      return False;
    tmp = tmp->next;
  }

  new = (struct icon_info *)safemalloc(sizeof(struct icon_info));
  new->name = NULL;
  new->window_name = NULL;
  new->res_class = NULL;
  new->res_name = NULL;
  new->action = NULL;
  new->icon_file = NULL;
  new->icon_w = 0;
  new->icon_h = 0;
  new->IconWin = None;
  new->iconPixmap = None;
  new->icon_maskPixmap = None;
  new->icon_pixmap_w = None;
  new->icon_depth = 0;
  new->id = id;
  new->fid = fid;
  new->defaulticon = 1;
  new->flags = flags | ICON_OURS;
  new->wmhints = NULL;
  new->prev = NULL;

  new->next = Head;
  if (Head != NULL)
    Head->prev = new;
  else
    Tail = new;
  Head = new;

  num_icons++;

  return True;
}
