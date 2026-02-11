raw_distance(const MixtureModel &m1, const MixtureModel &m2)
{
    feature_t features[NUMGAUSS];
    float w1[NUMGAUSS], w2[NUMGAUSS];

    for (int i = 0; i < NUMGAUSS; ++i)
    {
        features[i] = i;
        w1[i] = m1.gauss[i].weight;
        w2[i] = m2.gauss[i].weight;

        for (int j = 0; j < NUMGAUSS; ++j)
            cost[i][j] = KL_Divergence(m1.gauss[i], m2.gauss[j]);
    }

    signature_t s1 = { NUMGAUSS, features, w1 };
    signature_t s2 = { NUMGAUSS, features, w2 };
    return emd(&s1, &s2, EMD::gauss_dist, 0, 0);
}
