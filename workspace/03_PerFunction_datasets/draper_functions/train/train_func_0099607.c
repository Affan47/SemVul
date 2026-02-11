write_CollectiveClass(fstream& tex, uint64_t cclassType, vector<
        string> xLabels, int xnum, MinMaxMsgData minMax) {

    write_ybarPlotHead(tex, cclassType, INVOCATIONS, vector<string> (),
            minMax.count);
    write_CollectiveClassMetricPlot(tex, cclassType, INVOCATIONS, xnum);
    write_ybarPlotFoot(tex, 0);


    if (cclassType != OTF_COLLECTIVE_TYPE_BARRIER) {
        write_ybarPlotHead(tex, cclassType, MSGLENGTH, vector<string> (),
                minMax.bytes);
        write_CollectiveClassMetricPlot(tex, cclassType, MSGLENGTH, xnum);

        if (minMax.duration.max > 0)
            write_ybarPlotFoot(tex, 0);
    }


    if (minMax.duration.max > 0) {
        write_ybarPlotHead(tex, cclassType, DURATION, xLabels, minMax.duration);

        write_CollectiveClassMetricPlot(tex, cclassType, DURATION, xnum);
    }

    if (cclassType == OTF_COLLECTIVE_TYPE_BARRIER)
        write_ybarPlotFoot(tex, 2);
    else
        write_ybarPlotFoot(tex, 1);
}
