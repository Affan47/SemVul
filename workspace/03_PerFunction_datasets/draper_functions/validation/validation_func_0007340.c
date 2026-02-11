__ecereInstMeth___ecereNameSpace__ecere__gui__controls__Button_NotifyClicked__00000006(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * b, int x, int y, unsigned int mods)
{
struct CompilersTab * __ecerePointer_CompilersTab = (struct CompilersTab *)(this ? (((char *)this) + __ecereClass_CompilersTab->offset) : 0);
struct __ecereNameSpace__ecere__com__Instance * compilersDetectionDialog = (compilersDetectionDialog = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_CompilersDetectionDialog), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_parent(compilersDetectionDialog, __ecereProp___ecereNameSpace__ecere__gui__Window_Get_parent(__ecereProp_GlobalSettingsSubTab_Get_dialog(this))), compilersDetectionDialog);

if(__ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(compilersDetectionDialog))
{
if(((struct CompilersDetectionDialog *)(((char *)compilersDetectionDialog + __ecereClass_CompilersDetectionDialog->offset)))->selectedCompilerType)
{
char uniqueName[1025];
struct __ecereNameSpace__ecere__com__Instance * newCompiler = __ecereProp_CompilersDetectionDialog_Get_compilerConfig(compilersDetectionDialog);

__ecereMethod_CompilersTab_FindUniqueCompilerName(this, __ecereProp_CompilerConfig_Get_name(newCompiler), (((void *)0)), uniqueName);
__ecereProp_CompilerConfig_Set_name(newCompiler, uniqueName);
__ecereMethod_CompilersTab_AddCompiler(this, newCompiler, 0x1);
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x1);
}
}
return 0x1;
}
