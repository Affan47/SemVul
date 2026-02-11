ssl3_GetCurveWithECKeyStrength(PRUint32 curvemsk, int requiredECCbits)
{
    int    i;

    for ( i = 0; bits2curve[i].curve != ec_noName; i++) {
        if (bits2curve[i].bits < requiredECCbits)
            continue;
        if (SSL_IS_CURVE_NEGOTIATED(curvemsk, bits2curve[i].curve)) {
            return bits2curve[i].curve;
        }
    }
    PORT_SetError(SSL_ERROR_NO_CYPHER_OVERLAP);
    return ec_noName;
}
