__ecereMethod___ecereNameSpace__ecere__sys__File_PrintLn(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Class * class, void * object, ...)
{
struct __ecereNameSpace__ecere__sys__File * __ecerePointer___ecereNameSpace__ecere__sys__File = (struct __ecereNameSpace__ecere__sys__File *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__sys__File->offset) : 0);
va_list args;
char buffer[4096];

__builtin_va_start(args, object);
__ecereNameSpace__ecere__com__PrintStdArgsToBuffer(buffer, sizeof buffer, class, object, args);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, const char *  string))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Puts])(this, buffer);
((unsigned int (*)(struct __ecereNameSpace__ecere__com__Instance *, char ch))__extension__ ({
struct __ecereNameSpace__ecere__com__Instance * __internal_ClassInst = this;

__internal_ClassInst ? __internal_ClassInst->_vTbl : __ecereClass___ecereNameSpace__ecere__sys__File->_vTbl;
})[__ecereVMethodID___ecereNameSpace__ecere__sys__File_Putc])(this, '\n');
__builtin_va_end(args);
}
