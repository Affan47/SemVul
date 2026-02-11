sec2disp(long seconds) {
    static char buffer[50];

    if (seconds<0) seconds = 0;
    if (seconds<100) {
        sprintf(buffer, "%li sec", seconds);
    }
    else {
        long minutes = (seconds+30)/60;

        if (minutes<60) {
            sprintf(buffer, "%li min", minutes);
        }
        else {
            long hours = minutes/60;
            minutes    = minutes%60;

            sprintf(buffer, "%lih:%02li min", hours, minutes);
        }
    }
    return buffer;
}
