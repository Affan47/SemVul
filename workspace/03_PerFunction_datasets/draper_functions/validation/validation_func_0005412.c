__ecereMethod_BuildTab_OnClose(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int parentClosing)
{
struct BuildTab * __ecerePointer_BuildTab = (struct BuildTab *)(this ? (((char *)this) + __ecereClass_BuildTab->offset) : 0);

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_modifiedDocument(this))
{
int64 diagRes = __ecereMethod___ecereNameSpace__ecere__gui__Window_Modal(__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass___ecereNameSpace__ecere__gui__dialogs__MessageBox);

__ecereProp___ecereNameSpace__ecere__gui__dialogs__MessageBox_Set_type(__ecereInstance1, 3), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_master(__ecereInstance1, ((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace), __ecereProp___ecereNameSpace__ecere__gui__Window_Set_text(__ecereInstance1, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Save changes to project settings?", (((void *)0)))), __ecereProp___ecereNameSpace__ecere__gui__dialogs__MessageBox_Set_contents(__ecereInstance1, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "Would you like to save changes made to the build options?", (((void *)0)))), __ecereInstance1;
}));

if(diagRes == 0x2)
__ecereMethod_BuildTab_RevertChanges(this);
if(diagRes == 0x0)
return 0x0;
if(diagRes == 0x1)
{
__ecereMethod_Project_MarkChanges(project, __ecerePointer_BuildTab->backupNode);
project->topNode->modified = 0x1;
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->projectView, 0x1);
__ecereMethod_IDEWorkSpace_UpdateToolBarActiveConfigs(((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace, 0x0);
__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->projectView, (((void *)0)));
}
__ecereProp___ecereNameSpace__ecere__gui__Window_Set_modifiedDocument(this, 0x0);
}
return 0x1;
}
