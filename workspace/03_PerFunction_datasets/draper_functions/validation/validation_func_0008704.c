ensSliceCalculateLength(EnsPSlice slice)
{
    return (slice) ?
        ensSliceCalculateRegion(slice, slice->Start, slice->End) : 0U;
}
