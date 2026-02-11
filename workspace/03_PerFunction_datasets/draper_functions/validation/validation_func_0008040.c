setValue(const DSRImageReferenceValue &referenceValue)
{
    OFCondition result = DSRCompositeReferenceValue::setValue(referenceValue);
    if (result.good())
    {
        FrameList = referenceValue.FrameList;
        setPresentationState(referenceValue.PresentationState);
    }
    return result;
}
