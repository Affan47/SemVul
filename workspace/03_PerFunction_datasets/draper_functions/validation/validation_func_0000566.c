ovflow_into_wheel(void)
{
 int32 stki;
 struct bt_t *btphdr;


 if (__btqroot->btltim > __whetime) return;

 __btndhdrstk[0] = __btndstk[0] = __btqroot;
 btphdr = __btqroot->ofsu.btofs;
 for (__topi = 0;;)
  {
   __btndhdrstk[++__topi] = btphdr;


   if (btphdr->bttyp == BTFRNGE)
    {
     divide_fringe_node(btphdr);
     break;
    }
   divide_internal_node(btphdr);

   btphdr = __btndstk[__topi]->ofsu.btofs;
  }


 if (__btqroot == NULL) return;

 if (__btqroot != NULL)
  {
   for (stki = __topi; stki > 0; stki--)
    __btndstk[stki - 1]->btltim = __btndstk[stki]->btltim;
  }

 for (;;)
  {
   btphdr = __btqroot->ofsu.btofs;
   if (btphdr->bttyp == BTFRNGE || btphdr->btnfill != 1) return;
   if (__debug_flg && __ev_tracing)
    {
     __tr_msg(".. removing redundant size 1 node under root\n");
    }
   __btqroot->ofsu.btofs = btphdr->ofsu.btofs;
   __my_free((char *) btphdr, sizeof(struct bt_t));
   btphdr = NULL;
  }
}
