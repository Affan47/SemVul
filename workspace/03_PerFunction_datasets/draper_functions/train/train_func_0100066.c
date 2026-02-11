__ecereInstMeth___ecereNameSpace__ecere__gui__controls__EditBox_NotifyActivate__00000013(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * control, unsigned int active, struct __ecereNameSpace__ecere__com__Instance * previous)
{
struct __ecereNameSpace__ecere__gui__dialogs__FileDialog * __ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog = (struct __ecereNameSpace__ecere__gui__dialogs__FileDialog *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__dialogs__FileDialog->offset) : 0);

if(active)
{
char * selectedFileName = (((void *)0));
char * editText;

if(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->getNameFromListBox)
{
struct __ecereNameSpace__ecere__com__Instance * row = __ecereProp___ecereNameSpace__ecere__gui__controls__ListBox_Get_currentRow(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->listBox);

if(row)
{
if(__ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_GetNamesFromRow(this, row, &selectedFileName))
{
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Clear(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_PutS(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName, selectedFileName);
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_Select(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName, (((void *)0)), 0, 0, (((void *)0)), 0, 0);
}
__ecereMethod___ecereNameSpace__ecere__gui__dialogs__FileDialog_GetNameFromListBox(this, 0x0);
}
}
(__ecereNameSpace__ecere__com__eSystem_Delete(selectedFileName), selectedFileName = 0);
editText = __ecereProp___ecereNameSpace__ecere__gui__controls__EditBox_Get_contents(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->fileName);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_disabled(__ecerePointer___ecereNameSpace__ecere__gui__dialogs__FileDialog->ok, !editText || !editText[0]);
}
return 0x1;
}
