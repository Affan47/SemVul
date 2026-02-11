__ecereMethod___ecereNameSpace__ecere__com__List_SetData(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Link * link, uint64 value)
{
if(((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[6].dataTypeClass->type == 1)
memcpy((void *)&link->data, (void *)value, ((struct __ecereNameSpace__ecere__com__Instance *)(char *)this)->_class->templateArgs[6].dataTypeClass->structSize);
else
link->data = value;
return 0x1;
}
