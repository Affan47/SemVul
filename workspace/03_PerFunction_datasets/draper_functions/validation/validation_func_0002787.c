__ecereNameSpace__ecere__com__eClass_AddMethod(struct __ecereNameSpace__ecere__com__Class * _class, char * name, char * type, void * function, int declMode)
{
if(_class && name)
{
struct __ecereNameSpace__ecere__com__Class * base;

for(base = _class; base; base = base->base)
{
struct __ecereNameSpace__ecere__com__Method * method = (struct __ecereNameSpace__ecere__com__Method *)__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindString(&base->methods, name);

if(method)
{
if(method->type == 1)
{
struct __ecereNameSpace__ecere__sys__OldLink * deriv;
void * oldFunction = _class->_vTbl[method->vid];

if(method->vid > _class->vTblSize)
printf("error");
else
_class->_vTbl[method->vid] = function ? function : __ecereNameSpace__ecere__com__DefaultFunction;
for(deriv = _class->derivatives.first; deriv; deriv = deriv->next)
{
struct __ecereNameSpace__ecere__com__Class * derivClass = deriv->data;

if(derivClass->_vTbl[method->vid] == oldFunction)
__ecereNameSpace__ecere__com__eClass_AddMethod(derivClass, name, type, function, declMode);
}
{
struct __ecereNameSpace__ecere__sys__OldLink * templateLink;

for(templateLink = _class->templatized.first; templateLink; templateLink = templateLink->next)
{
struct __ecereNameSpace__ecere__com__Class * template = templateLink->data;

for(deriv = template->derivatives.first; deriv; deriv = deriv->next)
{
struct __ecereNameSpace__ecere__com__Class * derivClass = deriv->data;

if(derivClass->_vTbl[method->vid] == oldFunction)
__ecereNameSpace__ecere__com__eClass_AddMethod(derivClass, name, type, function, declMode);
}
}
}
}
else
{
if(base == _class)
{
break;
}
base = (((void *)0));
break;
}
return method;
}
}
if(!base)
{
struct __ecereNameSpace__ecere__com__Method * method = (method = __ecereNameSpace__ecere__com__eSystem_New0(52), method->name = __ecereNameSpace__ecere__sys__CopyString(name), method->function = function ? function : __ecereNameSpace__ecere__com__DefaultFunction, method->_class = _class, method->dataTypeString = __ecereNameSpace__ecere__sys__CopyString(type), method->memberAccess = declMode, method);

__ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_Add(&_class->methods, (struct __ecereNameSpace__ecere__sys__BTNode *)method);
return method;
}
}
return (((void *)0));
}
