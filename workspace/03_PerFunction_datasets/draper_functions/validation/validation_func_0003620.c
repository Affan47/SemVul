getChildWindowContentArea(const bool non_client) const
{
    return non_client ?
        getNonClientChildWindowContentArea_impl() :
        getClientChildWindowContentArea_impl();
}
