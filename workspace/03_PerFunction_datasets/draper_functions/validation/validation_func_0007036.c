updateFrame()
{
    int v = m_solid ? CSS_VAL_SOLID : CSS_VAL_OUTSET;
    if ( frame & Above )
         addCSSProperty(CSS_PROP_BORDER_TOP_STYLE, v);
    else
        addCSSProperty(CSS_PROP_BORDER_TOP_STYLE, CSS_VAL_NONE);
    if ( frame & Below )
        addCSSProperty(CSS_PROP_BORDER_BOTTOM_STYLE, v);
    else
        addCSSProperty(CSS_PROP_BORDER_BOTTOM_STYLE, CSS_VAL_NONE);
    if ( frame & Lhs )
        addCSSProperty(CSS_PROP_BORDER_LEFT_STYLE, v);
    else
        addCSSProperty(CSS_PROP_BORDER_LEFT_STYLE, CSS_VAL_NONE);
    if ( frame & Rhs )
        addCSSProperty(CSS_PROP_BORDER_RIGHT_STYLE, v);
    else
        addCSSProperty(CSS_PROP_BORDER_RIGHT_STYLE, CSS_VAL_NONE);
}
