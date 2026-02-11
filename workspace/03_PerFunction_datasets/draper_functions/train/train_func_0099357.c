parseAttribute(AttributeImpl *attr)
{
    switch(attr->id())
    {
    case ATTR_ALIGN:
    {
        DOMString v = attr->value().lower();
        if ( strcmp( v, "middle" ) == 0 || strcmp( v, "center" ) == 0 )
            addCSSProperty(CSS_PROP_TEXT_ALIGN, CSS_VAL__KHTML_CENTER);
        else if (strcmp(v, "left") == 0)
            addCSSProperty(CSS_PROP_TEXT_ALIGN, CSS_VAL__KHTML_LEFT);
        else if (strcmp(v, "right") == 0)
            addCSSProperty(CSS_PROP_TEXT_ALIGN, CSS_VAL__KHTML_RIGHT);
        else
            addCSSProperty(CSS_PROP_TEXT_ALIGN, v);
        break;
    }
    default:
        HTMLElementImpl::parseAttribute(attr);
    }
}
