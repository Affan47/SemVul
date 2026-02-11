__ecereMethod___ecereNameSpace__ecere__sys__File_Printf(struct __ecereNameSpace__ecere__com__Instance * this, char * format, ...)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);
int result = 0;

if(format)
{
char text[1025];
va_list args;

__builtin_va_start(args, format);
vsnprintf(text, sizeof text, format, args);
text[sizeof text - 1] = (char)0;
if(((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(this, text))
result = strlen(text);
__builtin_va_end(args);
}
return result;
}
