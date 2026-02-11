NodeImpl(DocumentImplPtr owner, const DOMString &,
		   const DOMString &qualifiedName) : Node()
{
    init();
    ownerDocument = owner;


    setNodeName(qualifiedName);
}
