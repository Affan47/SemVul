eina_quadtree_add(Eina_QuadTree *q, const void *object)
{
   Eina_QuadTree_Item *result;

   EINA_MAGIC_CHECK_QUADTREE(q, NULL);

   if (!object)
      return NULL;

   result = eina_trash_pop(&q->items_trash);
   if (!result)
      result = eina_mempool_malloc(_eina_quadtree_items_mp, sizeof (Eina_QuadTree_Item));
   else
      q->items_count--;

   if (!result)
      return NULL;

   result->quad = q;
   result->root = NULL;
   result->object = object;

   result->index = q->index++;

   result->change = EINA_TRUE;
   result->delete_me = EINA_FALSE;
   result->visible = EINA_TRUE;
   result->hidden = EINA_FALSE;

   EINA_MAGIC_SET(result, EINA_MAGIC_QUADTREE_ITEM);


   q->change = eina_inlist_append(q->change, EINA_INLIST_GET(result));

   return result;
}
