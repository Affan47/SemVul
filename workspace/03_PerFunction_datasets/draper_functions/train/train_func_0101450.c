__ecereMethod___ecereNameSpace__ecere__gfx__BitmapResource_Dereference(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gfx__BitmapResource * __ecerePointer___ecereNameSpace__ecere__gfx__BitmapResource = (struct __ecereNameSpace__ecere__gfx__BitmapResource *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx__BitmapResource->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gfx__BitmapResource->count--;
if(!__ecerePointer___ecereNameSpace__ecere__gfx__BitmapResource->count)
__ecerePointer___ecereNameSpace__ecere__gfx__BitmapResource->bitmap = (((void *)0));
}
