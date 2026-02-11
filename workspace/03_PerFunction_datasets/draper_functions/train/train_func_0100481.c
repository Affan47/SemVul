__ecereMethod_FindInFilesDialog_OnKeyHit(struct __ecereNameSpace__ecere__com__Instance * this, unsigned int key, unsigned int ch)
{
struct FindInFilesDialog * __ecerePointer_FindInFilesDialog = (struct FindInFilesDialog *)(this ? (((char *)this) + __ecereClass_FindInFilesDialog->offset) : 0);

if(ch && !((unsigned int)((key & 0x40000) >> 18)) && !((unsigned int)((key & 0x20000) >> 17)) && !((unsigned int)((key & 0x10000) >> 16)) && (__ecereProp___ecereNameSpace__ecere__gui__Window_Get_active(__ecerePointer_FindInFilesDialog->contentMatchCase) || __ecereProp___ecereNameSpace__ecere__gui__Window_Get_active(__ecerePointer_FindInFilesDialog->contentWholeWord)))
{
__ecereMethod___ecereNameSpace__ecere__gui__Window_Activate(__ecerePointer_FindInFilesDialog->findContent);
return ((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, unsigned int key, unsigned int ch))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = __ecerePointer_FindInFilesDialog->findContent;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__gui__Window_OnKeyHit])(__ecerePointer_FindInFilesDialog->findContent, key, ch);
}
return 0x1;
}
