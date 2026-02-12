usm_add_user_to_list(struct usmUser *user, struct usmUser *puserList)
{
    struct usmUser *nptr, *pptr, *optr;


    for (nptr = puserList, pptr = NULL; nptr != NULL;
         pptr = nptr, nptr = nptr->next) {
        if (nptr->engineIDLen > user->engineIDLen)
            break;

        if (user->engineID == NULL && nptr->engineID != NULL)
            break;

        if (nptr->engineIDLen == user->engineIDLen &&
            (nptr->engineID != NULL && user->engineID != NULL &&
             memcmp(nptr->engineID, user->engineID,
                    user->engineIDLen) > 0))
            break;

        if (!(nptr->engineID == NULL && user->engineID != NULL)) {
            if (nptr->engineIDLen == user->engineIDLen &&
                ((nptr->engineID == NULL && user->engineID == NULL) ||
                 memcmp(nptr->engineID, user->engineID,
                        user->engineIDLen) == 0)
                && strlen(nptr->name) > strlen(user->name))
                break;

            if (nptr->engineIDLen == user->engineIDLen &&
                ((nptr->engineID == NULL && user->engineID == NULL) ||
                 memcmp(nptr->engineID, user->engineID,
                        user->engineIDLen) == 0)
                && strlen(nptr->name) == strlen(user->name)
                && strcmp(nptr->name, user->name) > 0)
                break;

            if (nptr->engineIDLen == user->engineIDLen &&
                ((nptr->engineID == NULL && user->engineID == NULL) ||
                 memcmp(nptr->engineID, user->engineID,
                        user->engineIDLen) == 0)
                && strlen(nptr->name) == strlen(user->name)
                && strcmp(nptr->name, user->name) == 0) {


                if (pptr) {
                  pptr->next = nptr->next;
                }
                if (nptr->next) {
                  nptr->next->prev = pptr;
                }
                optr = nptr;
                nptr = optr->next;

                optr->next=NULL;
                optr->prev=NULL;
                usm_free_user(optr);
                break;
            }
        }
    }


    user->prev = pptr;
    user->next = nptr;


    if (user->next)
        user->next->prev = user;


    if (user->prev)
        user->prev->next = user;


    for (pptr = user; pptr->prev != NULL; pptr = pptr->prev);
    return pptr;
}
