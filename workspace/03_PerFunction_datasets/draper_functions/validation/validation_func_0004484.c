__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000020(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct __ecereNameSpace__ecere__com__Instance * w = __ecereProp___ecereNameSpace__ecere__gui__Window_Get_activeClient(this);

if(w)
__ecereMethod___ecereNameSpace__ecere__gui__Window_MenuFileSave(w, (((void *)0)), 0);
return 0x1;
}
