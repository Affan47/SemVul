__ecereInstMeth___ecereNameSpace__ecere__gui__Timer_DelayExpired__00000001(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct __ecereNameSpace__ecere__gui__controls__ListBox * __ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox = (struct __ecereNameSpace__ecere__gui__controls__ListBox *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__ecere__gui__controls__ListBox->offset) : 0);

__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->typedString[0] = '\0';
__ecereMethod___ecereNameSpace__ecere__gui__Timer_Stop(__ecerePointer___ecereNameSpace__ecere__gui__controls__ListBox->typingTimer);
return 0x1;
}
