stats_within_stdev(stats *stats, long double mean, long double stdev, uint64_t n) {
    long double upper = mean + (stdev * n);
    long double lower = mean - (stdev * n);
    uint64_t sum = 0;

    for (uint64_t i = 0; i < stats->limit; i++) {
        uint64_t x = stats->data[i];
        if (x >= lower && x <= upper) sum++;
    }

    return (sum / (long double) stats->limit) * 100;
}
