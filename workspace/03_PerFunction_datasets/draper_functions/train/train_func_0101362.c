simplify(void) const
{
    Polygon simplified = *this;
    std::vector<Point>::iterator it = simplified.ps.begin();
    if (it != simplified.ps.end()) ++it;


    for (size_t j = 2; j < simplified.size(); )
    {
        if (vecDir(simplified.ps[j - 2], simplified.ps[j - 1],
                simplified.ps[j]) == 0)
        {


            it = simplified.ps.erase(it);
        }
        else
        {
            ++j;
            ++it;
        }
    }

    return simplified;
}
