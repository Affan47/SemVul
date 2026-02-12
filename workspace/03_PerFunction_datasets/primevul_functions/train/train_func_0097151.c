int lpGetEdgeStreamID(unsigned char *lp, int first, streamID *master_id, streamID *edge_id)
{
   if (lp == NULL)
       return 0;

   unsigned char *lp_ele;


   if (first) {

       lp_ele = lpFirst(lp);
       lp_ele = lpNext(lp, lp_ele);
       lp_ele = lpNext(lp, lp_ele);
       int64_t master_fields_count = lpGetInteger(lp_ele);
       lp_ele = lpNext(lp, lp_ele);


       for (int64_t i = 0; i < master_fields_count; i++)
           lp_ele = lpNext(lp, lp_ele);


       lp_ele = lpNext(lp, lp_ele);
       if (lp_ele == NULL)
           return 0;
   } else {


       lp_ele = lpLast(lp);


       int64_t lp_count = lpGetInteger(lp_ele);
       if (lp_count == 0)
           return 0;

       while (lp_count--)
           lp_ele = lpPrev(lp, lp_ele);
   }

   lp_ele = lpNext(lp, lp_ele);


   streamID id = *master_id;
   id.ms += lpGetInteger(lp_ele);
   lp_ele = lpNext(lp, lp_ele);
   id.seq += lpGetInteger(lp_ele);
   *edge_id = id;
   return 1;
}
