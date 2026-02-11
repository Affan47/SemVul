OutputIntlStrings()
{
if(((struct __ecereNameSpace__ecere__com__CustomAVLTree *)(((char *)intlStrings + structSize_Instance)))->count)
{
char * srcFile = GetSourceFile();
char * objFile = GetOutputFile();
char srcFileFixed[797];
char potFile[797];
struct __ecereNameSpace__ecere__com__Instance * f;

__ecereNameSpace__ecere__sys__ChangeExtension(objFile, "bowl", potFile);
f = __ecereNameSpace__ecere__sys__FileOpen(potFile, 2);
if(f)
{
char * filePrefix = "";

if(!(srcFile[0] && (srcFile[1] == ':' || srcFile[0] == '/')))
filePrefix = "./";
__ecereNameSpace__ecere__sys__GetSlashPathBuffer(srcFileFixed, srcFile);
{
struct __ecereNameSpace__ecere__com__MapIterator s = (s.container = (void *)0, s.pointer = (void *)0, __ecereProp___ecereNameSpace__ecere__com__MapIterator_Set_map(&s, (intlStrings)), s);

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&s))
{
struct ContextStringPair pair = (*(struct ContextStringPair *)__ecereProp___ecereNameSpace__ecere__com__MapIterator_Get_key(&s));

{
struct __ecereNameSpace__ecere__com__Iterator l =
{
((struct __ecereNameSpace__ecere__com__Instance *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&s)), 0
};

while(__ecereMethod___ecereNameSpace__ecere__com__Iterator_Next(&l))
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "#: %s%s:%d\n", filePrefix, srcFileFixed, (*(struct Location *)__ecereProp___ecereNameSpace__ecere__com__Iterator_Get_data(&l)).start.line);
}
if(pair.context)
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "msgctxt \"%s\"\n", pair.context);
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "msgid \"%s\"\n", pair.string);
__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(f, "msgstr \"%s\"\n\n", pair.string);
}
}
(__ecereNameSpace__ecere__com__eInstance_DecRef(f), f = 0);
}
((void (*)(struct __ecereNameSpace__ecere__com__Instance *))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = intlStrings;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__com__Map->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__com__Container_Free])(intlStrings);
}
}
