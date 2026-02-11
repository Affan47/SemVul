getPointAlign(long x, long y, float height, Alignment align, Vector3* outpos) const
    {
        switch(align)
        {
        case ALIGN_X_Z:
            outpos->y = height;
            outpos->x = x * mScale + mBase;
            outpos->z = y * -mScale - mBase;
            break;
        case ALIGN_Y_Z:
            outpos->x = height;
            outpos->z = x * -mScale - mBase;
            outpos->y = y * mScale + mBase;
            break;
        case ALIGN_X_Y:
            outpos->z = height;
            outpos->x = x * mScale + mBase;
            outpos->y = y * mScale + mBase;
            break;
        };

    }
