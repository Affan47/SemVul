__ecereMethod___ecereNameSpace__eda__EDBRow_GoToSysID(struct __ecereNameSpace__ecere__com__Instance * this, int id)
{
struct __ecereNameSpace__eda__EDBRow * __ecerePointer___ecereNameSpace__eda__EDBRow = (struct __ecereNameSpace__eda__EDBRow *)(this ? (((char *)this) + __ecereClass___ecereNameSpace__eda__EDBRow->offset) : 0);

if(__ecerePointer___ecereNameSpace__eda__EDBRow->tbl->allocatedRowsCount >= id && id > 0 && __ecerePointer___ecereNameSpace__eda__EDBRow->tbl->rowPositions[id - 1])
{
__ecerePointer___ecereNameSpace__eda__EDBRow->_num = id;
if(__ecerePointer___ecereNameSpace__eda__EDBRow->index)
__ecerePointer___ecereNameSpace__eda__EDBRow->node = __ecereMethod___ecereNameSpace__ecere__sys__BinaryTree_FindAll(&__ecerePointer___ecereNameSpace__eda__EDBRow->index->tree, id);
return 0x1;
}
return 0x0;
}
