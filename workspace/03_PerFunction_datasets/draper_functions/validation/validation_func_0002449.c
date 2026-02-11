__ecereNameSpace__ecere__com__eEnum_AddFixedValue(struct __ecereNameSpace__ecere__com__Class * _class, char * string, int value)
{
if(_class && _class->type == 4)
{
struct __ecereNameSpace__ecere__com__EnumClassData * data = (struct __ecereNameSpace__ecere__com__EnumClassData *)_class->data;
struct __ecereNameSpace__ecere__sys__NamedLink * item;

for(item = data->values.first; item; item = item->next)
if(!strcmp(item->name, string))
break;
if(!item)
{
__ecereMethod___ecereNameSpace__ecere__sys__OldList_Add(&data->values, __extension__ ({
struct __ecereNameSpace__ecere__sys__NamedLink * __ecereInstance1 = __ecereNameSpace__ecere__com__eSystem_New0(structSize_NamedLink);

__ecereInstance1->data = (void *)value, __ecereInstance1->name = __ecereNameSpace__ecere__sys__CopyString(string), __ecereInstance1;
}));
if(value > data->largest)
data->largest = value;
}
}
}
