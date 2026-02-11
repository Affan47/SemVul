__ecereInstMeth___ecereNameSpace__ecere__gui__controls__MenuItem_NotifySelect__00000028(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * selection, unsigned int mods)
{
struct IDEWorkSpace * __ecerePointer_IDEWorkSpace = (struct IDEWorkSpace *)(this ? (((char *)this) + __ecereClass_IDEWorkSpace->offset) : 0);

if(__ecereProp_IDESettings_Get_ideProjectFileDialogLocation(ideSettings))
__ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Set_currentDirectory(ideProjectFileDialog, __ecereProp_IDESettings_Get_ideProjectFileDialogLocation(ideSettings));
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(ideProjectFileDialog, (__ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Open Additional Project", (((void *)0)))));
for(; ; )
{
if(__ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(ideProjectFileDialog) == 0x3)
{
if(__ecereMethod_IDEWorkSpace_OpenFile(this, __ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_filePath(ideProjectFileDialog), 0, 0x1, ((struct __ecereNameSpace__ecere__gui__dialogs__FileType *)((struct __ecereNameSpace__ecere__com__Array *)(((char *)projectTypes + 24)))->array)[__ecereProp___ecereNameSpace__ecere__gui__dialogs__FileDialog_Get_fileType(ideProjectFileDialog)].typeExtension, 0, 1, ((unsigned int)((mods & 0x2) >> 1)) && ((unsigned int)((mods & 0x1) >> 0))))
break;
if(__ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__dialogs__MessageBox);

__ecereProp___ecereNameSpace__ecere__gui__dialogs__MessageBox_Set_type(__ecereInstance1, 1), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_master(__ecereInstance1, this), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(__ecereInstance1, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Error opening project file", (((void *)0)))), __ecereProp___ecereNameSpace__ecere__gui__dialogs__MessageBox_Set_contents(__ecereInstance1, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Add a different project?", (((void *)0)))), __ecereInstance1;
})) == 0x2)
{
break;
}
}
else
break;
}
return 0x1;
}
