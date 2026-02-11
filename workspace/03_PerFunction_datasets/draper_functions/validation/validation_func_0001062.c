Scm_Matrix4fToQuatfv(float q[], const float m[])
{
    float trace = m[0] + m[5] + m[10];
    float s;
    if (trace > 0.0) {
        s = 0.5 / sqrtf(trace + 1.0);
        q[0] = (m[6]-m[9])*s;
        q[1] = (m[8]-m[2])*s;
        q[2] = (m[1]-m[4])*s;
        q[3] = 0.25 / s;
    } else {
        static int next[] = { 1, 2, 0 };
        int i, j, k;

        if (m[0] >= m[5]) {
            if (m[0] >= m[10]) i = 0;
            else i = 2;
        } else {
            if (m[5] >= m[10]) i = 1;
            else i = 2;
        }
        j = next[i]; k = next[j];
        s = sqrtf((m[i*5] - (m[j*5]+m[k*5])) + 1.0);
        if (m[j*4+k] < m[k*4+j]) s *= -1.0;
        q[i] = 0.5 * s;
        s = 0.5 / s;
        q[j] = (m[j*4+i] + m[i*4+j]) * s;
        q[k] = (m[k*4+i] + m[i*4+k]) * s;
        q[3] = (m[j*4+k] - m[k*4+j]) * s;
    }
}
