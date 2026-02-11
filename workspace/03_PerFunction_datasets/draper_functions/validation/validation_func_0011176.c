operator=(const SimpleDateFormat& other)
{
    if (this == &other) {
        return *this;
    }
    DateFormat::operator=(other);

    delete fSymbols;
    fSymbols = NULL;

    if (other.fSymbols)
        fSymbols = new DateFormatSymbols(*other.fSymbols);

    fDefaultCenturyStart         = other.fDefaultCenturyStart;
    fDefaultCenturyStartYear     = other.fDefaultCenturyStartYear;
    fHaveDefaultCentury          = other.fHaveDefaultCentury;

    fPattern = other.fPattern;


    if (fLocale != other.fLocale) {
        delete fTimeZoneFormat;
        fTimeZoneFormat = NULL;
        fLocale = other.fLocale;
    }

    fCapitalizationContext = other.fCapitalizationContext;

    return *this;
}
