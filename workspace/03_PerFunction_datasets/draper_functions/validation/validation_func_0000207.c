_DeclClass(int symbolID, char * name)
{
struct Symbol * symbol = FindClass(name);

if(!symbol)
{
if(name[0] == ':' && name[1] == ':')
name += 2;
symbol = __extension__ ({
struct Symbol * __ecereInstance1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_Symbol);

__ecereInstance1->string = __ecereNameSpace__ecere__sys__CopyString(name), __ecereInstance1->idCode = symbolID, __ecereInstance1->id = symbolID, __ecereInstance1;
});
if(!__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&globalContext->classes, (struct __ecereNameSpace__ecere__sys__BTNode *)symbol))
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add((&*excludedSymbols), symbol);
{
int start = 0, c;
char ch;

for(c = 0; (ch = name[c]); c++)
{
if(ch == '.' || (ch == ':' && name[c + 1] == ':'))
{
if(ch == ':')
c++;
start = c + 1;
}
}
if(start && c - start)
symbol->shortName = __ecereNameSpace__ecere__sys__CopyString(name + start);
}
}
if(symbolID)
symbol->idCode = symbol->id = symbolID;
return symbol;
}
