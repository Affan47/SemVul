adjustSizeForCompactIfNeeded(RenderObject* child, CompactInfo& compactInfo)
{


    if (compactInfo.matches(child)) {

        RenderObject* compactChild = compactInfo.compact();
        if (compactChild->height() > child->height())
            m_height += compactChild->height() - child->height();
    }
}
