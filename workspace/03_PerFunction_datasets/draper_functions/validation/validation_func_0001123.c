Reference(struct Type * source)
{
void * __ecereTemp1;
struct Type * type = (((void *)0));

if(source)
{
type = (__ecereTemp1 = __ecereNameSpace__ecere__com__eInstance_New(__ecereClass_Type), ((struct Type *)__ecereTemp1)->kind = 13, ((struct Type *)__ecereTemp1)->type = source, ((struct Type *)__ecereTemp1)->refCount = 1, ((struct Type *)__ecereTemp1));
source->refCount++;
}
return type;
}
