insert_blist(blist, block)
struct blocks_list *blist;
Block *block;
{
   struct blocks_list *cur;


   cur = blist;
   while (cur->next != NULL) cur = cur->next;

   if (cur->block != NULL)
   { cur->next = make_blist(); cur = cur->next; }

   strcpy(cur->fam, block->family);
   cur->block = block;
   cur->pssm = block_to_matrix(block, 3);

}
