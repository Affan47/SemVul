void *test_a_curve(void *pdata) {
    pthread_pcurve *data = (pthread_pcurve*)pdata;

    data->ret = TaggedSpiroCPsToBezier2(data->spiro,0,data->bc);

    return 0;
}
