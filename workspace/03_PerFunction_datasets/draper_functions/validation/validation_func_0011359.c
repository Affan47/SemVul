replaceChild ( NodeImpl *newChild, NodeImpl *oldChild, int &exceptioncode )
{
    handleChildRemove( oldChild );
    HTMLElementImpl::replaceChild( newChild, oldChild, exceptioncode );
    if ( !exceptioncode )
        handleChildAdd( newChild );
}
