static void apply_z(uECC_word_t * X1,
                    uECC_word_t * Y1,
                    const uECC_word_t * const Z,
                    uECC_Curve curve) {
    uECC_word_t t1[uECC_MAX_WORDS];

    uECC_vli_modSquare_fast(t1, Z, curve);
    uECC_vli_modMult_fast(X1, X1, t1, curve);
    uECC_vli_modMult_fast(t1, t1, Z, curve);
    uECC_vli_modMult_fast(Y1, Y1, t1, curve);
}
