ExecuteKey(XEvent event)
{
  struct icon_info *item;
  struct keyfunc *tmp;

  if ((item = Hilite) == NULL)
     if ((item = Head) == NULL)
       return;

  tmp = KeyActions;
  event.xkey.keycode =
    XKeysymToKeycode(dpy,fvwm_KeycodeToKeysym(dpy,event.xkey.keycode,0,0));
  while (tmp != NULL){
    if (tmp->keycode == event.xkey.keycode){
      MySendFvwmPipe(fd, tmp->action, item->id);
      return;
    }
    tmp = tmp->next;
  }
}
