__ecereMethod_ModelView_OnLeftButtonUp(struct __ecereNameSpace__ecere__com__Instance * this, int x, int y, unsigned int mods)
{
struct ModelView * __ecerePointer_ModelView = (struct ModelView *)(this ? (((char *)this) + __ecereClass_ModelView->offset) : 0);

if(__ecerePointer_ModelView->moving)
{
__ecereMethod___ecereNameSpace__ecere__gui__Window_ReleaseCapture(this);
__ecerePointer_ModelView->moving = 0x0;
}
return 0x1;
}
