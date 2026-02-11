getGridSize(const std::vector<UDim>& colSizes,
        const std::vector<UDim>& rowSizes) const
{
    UVector2 ret(UDim(0, 0), UDim(0, 0));

    for (size_t i = 0; i < colSizes.size(); ++i)
    {
        ret.d_x += colSizes[i];
    }

    for (size_t i = 0; i < rowSizes.size(); ++i)
    {
        ret.d_y += rowSizes[i];
    }

    return ret;
}
