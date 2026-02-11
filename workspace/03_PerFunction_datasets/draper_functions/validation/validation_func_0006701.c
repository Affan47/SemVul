__ecereProp_BuildTab_Get_selectedConfigName(struct __ecereNameSpace__ecere__com__Instance * this)
{
struct BuildTab * __ecerePointer_BuildTab = (struct BuildTab *)(this ? (((char *)this) + __ecereClass_BuildTab->offset) : 0);

if(__ecereProp___ecereNameSpace__ecere__gui__Window_Get_created(this))
{
struct __ecereNameSpace__ecere__com__Instance * button = __ecereProp___ecereNameSpace__ecere__gui__controls__SelectorBar_Get_selectedButton(__ecerePointer_BuildTab->configSelector);

if(button && __ecereProp___ecereNameSpace__ecere__gui__Window_Get_id(button))
{
struct ProjectConfig * config = (struct ProjectConfig *)__ecereProp___ecereNameSpace__ecere__gui__Window_Get_id(button);

return config->name;
}
}
return "";
}
