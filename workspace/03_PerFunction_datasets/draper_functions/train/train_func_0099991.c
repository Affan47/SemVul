childShouldCreateRenderer(Node* child) const
{


    if (child->hasTagName(SVGNames::aTag))
        return false;
    if (parent() && parent()->isSVGElement())
        return static_cast<SVGElement*>(parent())->childShouldCreateRenderer(child);

    return SVGElement::childShouldCreateRenderer(child);
}

}
