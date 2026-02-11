__ecereInstMeth___ecereNameSpace__ecere__gui__controls__CalendarControl_OnActivate__00000000(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int active, struct __ecereNameSpace__ecere__com__Instance * previous, unsigned int * goOnWithActivation, unsigned int direct)
{
struct __ecereNameSpace__ecere__gui__controls__CalendarControl * __ecerePointer___ecereNameSpace__ecere__gui__controls__CalendarControl = (struct __ecereNameSpace__ecere__gui__controls__CalendarControl *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__CalendarControl->offset) : 0);

if(!active)
{
struct __ecereNameSpace__ecere__com__Instance * dropBox = (struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this);

__ecereMethod___ecereNameSpace__ecere__gui__Window_Destroy(this, 0);
__ecereMethod___ecereNameSpace__ecere__gui__controls__DataBox_Refresh(((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(dropBox)));
*goOnWithActivation = 0x0;
}
return 0x1;
}
