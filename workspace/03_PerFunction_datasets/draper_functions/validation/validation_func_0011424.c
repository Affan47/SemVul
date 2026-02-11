__ecereProp_ProjectNode_Set_folder(struct ProjectNode * this, char * value)
{
this->nodeType = 1;
if(strchr(value, '/'))
{
char p[797];
char n[274];

__ecereFunction___ecereNameSpace__ecere__sys__GetLastDirectory(value, n);
__ecereFunction___ecereNameSpace__ecere__sys__StripLastDirectory(value, p);
this->name = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(n);
this->path = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(p);
}
else
this->name = __ecereFunction___ecereNameSpace__ecere__sys__CopyString(value);
}
