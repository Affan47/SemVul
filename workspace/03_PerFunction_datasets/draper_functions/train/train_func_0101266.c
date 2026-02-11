__ecereMethod_GDBDialog_TrimEscapedNewLineChar(struct __ecereNameSpace__ecere__com__Instance * this, char * s)
{
struct GDBDialog * __ecerePointer_GDBDialog = (struct GDBDialog *)(this ? (((char *)this) + __ecereClass_GDBDialog->offset) : 0);
int len = strlen(s);

if(s[len - 1] == 'n' && s[len - 2] == '\\')
{
s[len - 2] = '\0';
len -= 2;
}
return len;
}
