findDelay(QVector<double> &wattsArray, QVector<double> &hrArray, int rideTimeSecs)
{
    int delay = 0;
    double maxr = 0;

    if (rideTimeSecs>= 60) {

        for (int a = 10; a <=60; ++a) {

            QVector<double> delayHr(rideTimeSecs);

            for (int j = a; j<rideTimeSecs; ++j) {
                delayHr[j-a] = hrArray[j];
            }
            for (int j = rideTimeSecs-a; j<rideTimeSecs; ++j) {
                delayHr[j] = 0.0;
            }

            double r = corr(wattsArray, delayHr, rideTimeSecs-a);


            if (r>maxr) {
                maxr = r;
                delay = a;
            }
        }
    }

    delayEdit->setText(QString("%1").arg(delay));
    rDelayEdit->setText(QString("%1").arg(delay));
    delaySlider->setValue(delay);
    rDelaySlider->setValue(delay);
    return delay;
}
