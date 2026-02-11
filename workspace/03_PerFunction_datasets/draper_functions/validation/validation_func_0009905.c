collidesWithSprite(const Sprite &s) const
{
    const Sprite &s1 = *this;
    const Sprite &s2 = s;
    const Couple &pos1  = s1.getPos() + s1.collBoxPos;
    const Couple &size1 = s1.collBoxSize;
    const Couple &pos2  = s2.getPos() + s2.collBoxPos;
    const Couple &size2 = s2.collBoxSize;

    if (pos1.x + size1.x <= pos2.x)
        return false;
    if (pos1.y + size1.y <= pos2.y)
        return false;
    if (pos2.x + size2.x <= pos1.x)
        return false;
    if (pos2.y + size2.y <= pos1.y)
        return false;

    return true;
}
