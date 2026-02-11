__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000063(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * colorPicker = (colorPicker = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__dialogs__ColorPicker), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_master(colorPicker, this), colorPicker);

__ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(colorPicker);
return 0x1;
}
