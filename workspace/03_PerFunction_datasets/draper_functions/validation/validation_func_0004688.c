__ecereMethod_ProjectView_DisplayCompiler(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * compiler, unsigned int cleanLog)
{
struct ProjectView * __ecerePointer_ProjectView = (struct ProjectView *)(this ? (((char *)this) + __ecereClass_ProjectView->offset) : 0);

__ecereMethod_LogBox_Logf(((struct OutputView *)(((char *)((struct IDEWorkSpace *)(((char *)((struct IDEMainFrame *)(((char *)ideMainFrame + __ecereClass_IDEMainFrame->offset)))->ideWorkSpace + __ecereClass_IDEWorkSpace->offset)))->outputView + __ecereClass_OutputView->offset)))->buildBox, __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "%s Compiler\n", (((void *)0))), compiler ? __ecereProp_CompilerConfig_Get_name(compiler) : __ecereNameSpace__ecere__GetTranslatedString(__thisModule, "{problem with compiler selection}", (((void *)0))));
return 0x1;
}
