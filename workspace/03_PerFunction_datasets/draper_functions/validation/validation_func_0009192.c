Within(const trpg2dPoint &pt) const
{
    if (inRange(ll.x,ur.x,pt.x) && inRange(ll.y,ur.y,pt.y))
        return true;
    return false;
}
