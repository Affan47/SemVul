normalize()
{
    for (int i=0; i<this->size(); ++i)
    {
        float* r = this->load(i);
        r[0] = r[0] / r[3];
        r[1] = r[1] / r[3];
        r[2] = r[2] / r[3];
        r[3] = r[3] / r[3];
    }
}
