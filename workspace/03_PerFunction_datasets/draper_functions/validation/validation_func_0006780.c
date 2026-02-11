handleVertAlignment(RenderedString& rs, const String& value)
{
    if (value == TopAlignedValueName)
        d_vertAlignment = VF_TOP_ALIGNED;
    else if (value == BottomAlignedValueName)
        d_vertAlignment = VF_BOTTOM_ALIGNED;
    else if (value == CentreAlignedValueName)
        d_vertAlignment = VF_CENTRE_ALIGNED;
    else if (value == StretchAlignedValueName)
        d_vertAlignment = VF_STRETCHED;
    else
        Logger::getSingleton().logEvent(
            "BasicRenderedStringParser::handleVertAlignment: unknown "
            "vertical alignment '" + value + "'.  Ignoring!");
}
