cut_iterated_test_clear_data (CutIteratedTest *test)
{
    CutIteratedTestPrivate *priv;

    priv = CUT_ITERATED_TEST_GET_PRIVATE(test);
    if (priv->data)
        cut_test_data_set_value(priv->data, NULL, NULL);
}
