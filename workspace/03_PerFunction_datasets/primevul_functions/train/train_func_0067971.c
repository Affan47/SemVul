Node::InsertionNotificationRequest HTMLBodyElement::insertedInto(ContainerNode* insertionPoint)
 {
     HTMLElement::insertedInto(insertionPoint);
    return InsertionShouldCallDidNotifySubtreeInsertions;
}

void HTMLBodyElement::didNotifySubtreeInsertionsToDocument()
{


    Element* ownerElement = document().ownerElement();
    if (!isHTMLFrameElementBase(ownerElement))
        return;
    HTMLFrameElementBase& ownerFrameElement = toHTMLFrameElementBase(*ownerElement);
    int marginWidth = ownerFrameElement.marginWidth();
    int marginHeight = ownerFrameElement.marginHeight();
    if (marginWidth != -1)
        setIntegralAttribute(marginwidthAttr, marginWidth);
    if (marginHeight != -1)
        setIntegralAttribute(marginheightAttr, marginHeight);
 }
