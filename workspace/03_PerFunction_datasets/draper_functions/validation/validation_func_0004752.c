Itcl_DeleteList(listPtr)
    Itcl_List *listPtr;
{
    Itcl_ListElem *elemPtr;

    assert(listPtr->validate == ITCL_VALID_LIST);

    elemPtr = listPtr->head;
    while (elemPtr) {
        elemPtr = Itcl_DeleteListElem(elemPtr);
    }
    listPtr->validate = 0;
}
