usm_remove_usmUser_from_list(struct usmUser *user, struct usmUser **ppuserList)
{
    struct usmUser *nptr, *pptr;


    if (ppuserList == NULL)
        ppuserList = &userList;

    if (*ppuserList == NULL)
        return SNMPERR_USM_UNKNOWNSECURITYNAME;


    for (nptr = *ppuserList, pptr = NULL; nptr != NULL;
         pptr = nptr, nptr = nptr->next) {
        if (nptr == user)
            break;
    }

    if (nptr) {


        if (pptr) {
            pptr->next = nptr->next;
        }
        if (nptr->next) {
            nptr->next->prev = pptr;
        }
    } else {


        return SNMPERR_USM_UNKNOWNSECURITYNAME;
    }
    if (nptr == *ppuserList)

        *ppuserList = nptr->next;
    return SNMPERR_SUCCESS;
}
