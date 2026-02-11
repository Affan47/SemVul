__ecereMethod___ecereNameSpace__ecere__gfx__ColorDropBox_OnCloseDropDown(struct __ecereNameSpace__ecere__com__Instance * this, struct __ecereNameSpace__ecere__com__Instance * pullDown)
{
struct __ecereNameSpace__ecere__gfx__ColorDropBox * __ecerePointer___ecereNameSpace__ecere__gfx__ColorDropBox = (struct __ecereNameSpace__ecere__gfx__ColorDropBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gfx__ColorDropBox->offset) : 0);

__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_master(this), (((void *)0)));
__ecereMethod___ecereNameSpace__ecere__gui__Window_Destroy(pullDown, 0);
}
