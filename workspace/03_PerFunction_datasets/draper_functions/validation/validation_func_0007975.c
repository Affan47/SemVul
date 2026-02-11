CQRExp( CQRQuaternionHandle quaternion, CQRQuaternionHandle q ) {

        CQRQuaternion impart;
        double angle;
        double rat;

        if (!quaternion || ! q) return CQR_BAD_ARGUMENT;

        CQRGetQuaternionIm(&impart,q);
        CQRMNorm(angle,impart);

        if (angle <= DBL_MIN) {

            quaternion->w = cos(angle)*exp(q->w);
            quaternion->x = 0.;
            quaternion->y = 0.;
            quaternion->z = 0.;

        } else {

            rat = exp(q->w)*sin(angle)/angle;
            quaternion->w = cos(angle)*exp(q->w);
            quaternion->x = rat*q->x;
            quaternion->y = rat*q->y;
            quaternion->z = rat*q->z;

        }

        return CQR_SUCCESS;

    }
