FindWithNameSpace(struct __ecereNameSpace__ecere__sys__BinaryTree * tree, char * name)
{
int c;
char nameSpace[1024];
char * namePart;
unsigned int gotColon = 0x0;

nameSpace[0] = '\0';
for(c = strlen(name) - 1; c >= 0; c--)
if(name[c] == ':')
{
gotColon = 0x1;
break;
}
namePart = name + c + 1;
while(c >= 0 && name[c] == ':')
c--;
if(c >= 0)
{
memcpy(nameSpace, name, c + 1);
nameSpace[c + 1] = (char)0;
return ScanWithNameSpace(tree, nameSpace, namePart);
}
else if(gotColon)
{
struct Symbol * symbol = (struct Symbol *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(tree, namePart);

return symbol;
}
else
return ScanWithNameSpace(tree, "", namePart);
return (((void *)0));
}
