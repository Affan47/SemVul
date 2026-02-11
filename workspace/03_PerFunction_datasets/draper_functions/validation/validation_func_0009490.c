t_checkminspeed(transfer * const t) {
   char *tempstr2;

   updatecontext();

   if (t->tr_status != TRANSFER_STATUS_SENDING)      return;
   if (t->connecttime+MIN_TL > gdata.curtime)        return;
   if (t->nomin || (t->xpack->minspeed) == 0.0)      return;
   if ( t->lastspeed+0.11 > t->xpack->minspeed )     return;

   tempstr2 = mycalloc(maxtextlength);
   snprintf(tempstr2,maxtextlength-1,
        "Under Min Speed Requirement, %2.1fK/sec is less than %2.1fK/sec",
         t->lastspeed,t->xpack->minspeed);
   if (!gdata.attop) gototop();
   t_closeconn(t,tempstr2,0);
   mydelete(tempstr2);

   if (gdata.punishslowusers)
     {
       char *tempstr;
       igninfo *ignore;
       pqueue *pq;
       transfer *tr;

       for (tr = irlist_get_head(&gdata.trans); tr; tr = irlist_get_next(tr))
         {
           if ((tr->tr_status != TRANSFER_STATUS_DONE) &&
               (strcasecmp(tr->nick,t->nick) == 0))
             {
               t_closeconn(tr, "You are being punished for your slowness", 0);
             }
         }

       pq = irlist_get_head(&gdata.mainqueue);
       while(pq)
         {
           if (strcasecmp(pq->nick,t->nick) == 0)
             {
               notice(pq->nick,"** Removed From Queue: You are being punished for your slowness");
               mydelete(pq->nick);
               mydelete(pq->hostname);
               pq = irlist_delete(&gdata.mainqueue, pq);
             }
           else
             {
               pq = irlist_get_next(pq);
             }
         }

       ignore = irlist_add(&gdata.ignorelist, sizeof(igninfo));
       ignore->regexp = mycalloc(sizeof(regex_t));

       ignore->hostmask = mycalloc(strlen(t->hostname)+5);
       sprintf(ignore->hostmask,"*!*@%s",t->hostname);

       tempstr = hostmasktoregex(ignore->hostmask);
       if (regcomp(ignore->regexp,tempstr,REG_ICASE|REG_NOSUB))
         {
           ignore->regexp = NULL;
         }
       mydelete(tempstr);

       ignore->flags |= IGN_IGNORING;
       ignore->lastcontact = gdata.curtime;
       ignore->bucket = (gdata.punishslowusers*60)/gdata.autoignore_threshold;

       ioutput(CALLTYPE_NORMAL,OUT_S|OUT_L|OUT_D,COLOR_NO_COLOR,
               "Punish-ignore activated for %s (%s) %d minutes",
               t->nick,
               ignore->hostmask,
               gdata.punishslowusers);

       notice(t->nick,"Punish-ignore activated for %s (%s) %d minutes",
              t->nick,
              ignore->hostmask,
              gdata.punishslowusers);

       write_statefile();
     }

   }
