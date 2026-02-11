AddLineOffset( SizeT lineOffset, RefDNode astR)
{
astR->SetLine( astR->getLine() + lineOffset);
if( astR->getFirstChild() != NULL) AddLineOffset( lineOffset, (RefDNode)astR->getFirstChild() );
if( astR->getNextSibling() != NULL) AddLineOffset( lineOffset, (RefDNode)astR->getNextSibling() );
}
