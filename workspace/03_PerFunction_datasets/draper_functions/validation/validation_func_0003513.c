qtFilter(const QString& filter)
{


    QStringList filters;
    if (filter.isEmpty())
        filters += i18n("*|All files");
    else {

      int pos = filter.indexOf('/');
      if (pos > 0 && filter[pos - 1] != '\\')
          filters = mime2KdeFilter(filter.split(QLatin1Char(' '), QString::SkipEmptyParts));
      else
          filters = filter.split('\n', QString::SkipEmptyParts);
    }
    return qtFilter(filters);
}
