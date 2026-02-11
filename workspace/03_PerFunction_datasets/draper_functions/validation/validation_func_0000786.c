nssPKIObjectCollection_AddObject (
  nssPKIObjectCollection *collection,
  nssPKIObject *object
)
{
    pkiObjectCollectionNode *node;
    node = nss_ZNEW(collection->arena, pkiObjectCollectionNode);
    if (!node) {
	return PR_FAILURE;
    }
    node->haveObject = PR_TRUE;
    node->object = nssPKIObject_AddRef(object);
    (*collection->getUIDFromObject)(object, node->uid);
    PR_INIT_CLIST(&node->link);
    PR_INSERT_BEFORE(&node->link, &collection->head);
    collection->size++;
    return PR_SUCCESS;
}
