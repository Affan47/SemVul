__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_OnVScroll(struct __ecereNameSpace__ecere__com__Instance * this, int action, int position, unsigned int key)
{
struct __ecereNameSpace__ecere__gui__controls__EditBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox = (struct __ecereNameSpace__ecere__gui__controls__EditBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__EditBox->offset) : 0);
int oldViewY = __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY;

position /= __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h;
if(position < __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY)
{
for(; position < __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY && __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_prev(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine); __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine = __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_prev(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine), __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY--)
;
__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style = (__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & ~0x400000) | (((unsigned int)0x1) << 22);
}
else if(position > __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY)
{
struct __ecereNameSpace__ecere__gui__controls__EditLine * oldViewLine = __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine;

for(; position > __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY && __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_next(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine); __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine = __ecereProp___ecereNameSpace__ecere__gui__controls__EditLine_Get_next(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewLine), __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY++)
;
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_FigureStartSyntaxStates(this, oldViewLine, 0x0);
}
if(action != 8)
{
if(!__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->mouseMove && ((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & 0x800000) >> 23)) && !__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SelSize(this))
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_SetCursorToViewY(this);
}
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->x != __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->selX || __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->y != __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->selY)
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_DirtyLine(this, __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->y);
{
__ecereMethod___ecereNameSpace__ecere__gui__Window_Scroll(this, 0, (int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY - oldViewY) * __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h));
}
if(__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->viewY - oldViewY > 0)
{
struct __ecereNameSpace__ecere__sys__Size __simpleStruct1;
struct __ecereNameSpace__ecere__sys__Size __simpleStruct0;
struct __ecereNameSpace__ecere__sys__Box box =
{
0, 0, (int)((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct0), __simpleStruct0.w - 1)), (((unsigned int)((__ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->style & 0x4) >> 2)) ? 1 : (((__ecereProp___ecereNameSpace__ecere__gui__Window_Get_clientSize(this, &__simpleStruct1), __simpleStruct1.h + 1) - __ecerePointer___ecereNameSpace__ecere__gui__controls__EditBox->space.h) / 2)) - 1
};

__ecereMethod___ecereNameSpace__ecere__gui__Window_Update(this, &box);
}
__ecereMethod___ecereNameSpace__ecere__gui__controls__EditBox_UpdateDirty(this);
}
