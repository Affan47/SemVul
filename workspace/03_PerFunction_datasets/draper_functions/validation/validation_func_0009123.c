__ecereMethod___ecereNameSpace__ecere__gui__controls__PopupMenu_CheckAccelerators(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * menu, unsigned int key)
{
struct __ecereNameSpace__ecere__gui__controls__PopupMenu * __ecerePointer___ecereNameSpace__ecere__gui__controls__PopupMenu = (struct __ecereNameSpace__ecere__gui__controls__PopupMenu *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__PopupMenu->offset) : 0);
struct __ecereNameSpace__ecere__gui__controls__ItemPtr * ptr;

for(ptr = ((struct __ecereNameSpace__ecere__gui__controls__Menu *)(((char *)menu + __ecereClass___ecereNameSpace__ecere__gui__controls__Menu->offset)))->items.first; ptr; ptr = ptr->next)
{
struct __ecereNameSpace__ecere__com__Instance * item = ptr->item;

if(((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->subMenu)
{
if(!__ecereMethod___ecereNameSpace__ecere__gui__controls__PopupMenu_CheckAccelerators(this, ((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->subMenu, key))
return 0x0;
}
else if(!((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->isDivider)
{
if(((struct __ecereNameSpace__ecere__gui__controls__MenuItem *)(((char *)item + __ecereClass___ecereNameSpace__ecere__gui__controls__MenuItem->offset)))->accelerator == key)
{
if(__ecereMethod___ecereNameSpace__ecere__gui__controls__PopupMenu_MenuItemSelection(this, menu, ptr, key))
return 0x0;
}
}
}
return 0x1;
}
