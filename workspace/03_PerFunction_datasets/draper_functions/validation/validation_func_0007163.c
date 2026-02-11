_acceptObject(SPObject * const obj) const
{
    if (IS_LIVEPATHEFFECT(obj)) {
        SPObject * const owner = getOwner();

        for ( SPObject *iter = owner ; iter ; iter = SP_OBJECT_PARENT(iter) ) {
            if ( iter == obj ) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}
