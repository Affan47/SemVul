addRideData(double BS, QDateTime rideDate) {
    int daysIndex = startDate.daysTo(rideDate);

    int d;
    for (d = lastDaysIndex + 1; d < daysIndex ; d++) {
        list[d] = 0.0;
        calculate(d);
    }


    if(daysIndex < 0) return;


    list[daysIndex] += BS;
    calculate(daysIndex);
    lastDaysIndex = daysIndex;
}
