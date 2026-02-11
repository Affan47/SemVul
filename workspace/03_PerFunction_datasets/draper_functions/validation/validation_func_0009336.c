gnc_owner_get_owner (GtkWidget *widget, GncOwner *owner)
{
    g_return_if_fail (widget != NULL);
    g_return_if_fail (owner != NULL);


    owner->owner.undefined =
        gnc_general_search_get_selected (GNC_GENERAL_SEARCH (widget));
}
