glist_remove( struct glist *list_p, struct group *grp )
{
        struct group *rv = NULL;

        if ( list_p->head  != NULL && list_p->head == grp ) {
                DBG( "Removing group from the head\n" );
                list_p->head = grp->next;
                DBG( "new head [%p] \n" );
                rv = grp;
                list_p->size--;
                return rv;
        }
        rv = list_p->head;
        while ( rv != NULL ) {
               if ( rv->next == grp ) {
                      DBG( "Found group, removing\n" );
                      rv->next = grp->next;
                      rv = grp;
                      list_p->size--;
                      break;
               }
               rv = rv->next;
        }

        return rv;
}
