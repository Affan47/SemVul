setParameterAxisTitle()
{
    QString axislabel;
    switch (series) {

        case RideFile::watts:
            if (zoned) axislabel = tr("Power zone");
            else axislabel = tr("Power (watts)");
            break;

        case RideFile::wattsKg:
            if (zoned) axislabel = tr("Power zone");
            else axislabel = tr("Power (watts/kg)");
            break;

        case RideFile::hr:
            if (zoned) axislabel = tr("Heartrate zone");
            else axislabel = tr("Heartrate (bpm)");
            break;

        case RideFile::cad:
            axislabel = tr("Cadence (rpm)");
            break;

        case RideFile::kph:
            axislabel = QString(tr("Speed (%1)")).arg(mainWindow->useMetricUnits ? tr("kph") : tr("mph"));
            break;

        case RideFile::nm:
            axislabel = QString(tr("Torque (%1)")).arg(mainWindow->useMetricUnits ? tr("N-m") : tr("ft-lbf"));
            break;

        default:
            axislabel = QString(tr("Unknown data series"));
            break;
    }
    setAxisTitle(xBottom, axislabel);
    setAxisTitle(yLeft, absolutetime ? tr("Time (minutes)") : tr("Time (percent)"));
}
