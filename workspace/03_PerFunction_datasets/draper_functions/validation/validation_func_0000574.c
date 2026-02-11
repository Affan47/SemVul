heightMediaFeatureEval(CSSValueImpl* value, RenderStyle* style, KHTMLPart* part,  MediaFeaturePrefix op)
{
    KHTMLPart* rootPart = part;
    while (rootPart->parentPart()) rootPart = rootPart->parentPart();
    DOM::DocumentImpl *doc =  static_cast<DOM::DocumentImpl*>(rootPart->document().handle());
    QPaintDevice *pd = doc->paintDevice();
    bool printing = pd ? (pd->devType() == QInternal::Printer) : false;
    int height;
    if (printing)
        height = pd->height();
    else {
        height = part->view()->visibleHeight();
        doc = static_cast<DOM::DocumentImpl*>(part->document().handle());
    }
    int logicalDpiY = doc->logicalDpiY();
    if (value)
        return value->isPrimitiveValue() && compareValue(height, static_cast<CSSPrimitiveValueImpl*>(value)->computeLength(style, logicalDpiY), op);

    return height > 0;
}
