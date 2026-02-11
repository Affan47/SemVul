__ecereRegisterModule_CodeObject(struct __ecereNameSpace__ecere__com__Instance * module)
{
struct __ecereNameSpace__ecere__com__Class * class;

class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(4, "CodeObjectType", 0, 0, 0, 0, 0, module, 2, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass_CodeObjectType = class;
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeClass", 0);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeData", 1);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeMethod", 2);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeEvent", 3);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeProperty", 4);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeNameSpace", 5);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeDataType", 6);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeEnumValue", 7);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeDataPrivate", 8);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typeMethodPrivate", 9);
__ecereNameSpace__ecere__com__eEnum_AddFixedValue(class, "typePropertyPrivate", 10);
__ecereNameSpace__ecere__com__eSystem_RegisterFunction("mystrlen", "int mystrlen(const char * s)", mystrlen, module, 2);
class = __ecereNameSpace__ecere__com__eSystem_RegisterClass(5, "CodeObject", 0, sizeof(struct CodeObject), 0, 0, 0, module, 2, 1);
if(((struct __ecereNameSpace__ecere__com__Module *)(((char *)module + 24)))->application == ((struct __ecereNameSpace__ecere__com__Module *)(((char *)__thisModule + 24)))->application && class)
__ecereClass_CodeObject = class;
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnDisplay", 0, __ecereMethod_CodeObject_OnDisplay, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnCompare", 0, __ecereMethod_CodeObject_OnCompare, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnFree", 0, __ecereMethod_CodeObject_OnFree, 1);
__ecereNameSpace__ecere__com__eClass_AddMethod(class, "OnGetString", 0, __ecereMethod_CodeObject_OnGetString, 1);
}
