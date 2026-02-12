static void XYcZ_add(uECC_word_t * X1,
                     uECC_word_t * Y1,
                     uECC_word_t * X2,
                     uECC_word_t * Y2,
                     uECC_Curve curve) {

    uECC_word_t t5[uECC_MAX_WORDS];
    wordcount_t num_words = curve->num_words;

    uECC_vli_modSub(t5, X2, X1, curve->p, num_words);
    uECC_vli_modSquare_fast(t5, t5, curve);
    uECC_vli_modMult_fast(X1, X1, t5, curve);
    uECC_vli_modMult_fast(X2, X2, t5, curve);
    uECC_vli_modSub(Y2, Y2, Y1, curve->p, num_words);
    uECC_vli_modSquare_fast(t5, Y2, curve);

    uECC_vli_modSub(t5, t5, X1, curve->p, num_words);
    uECC_vli_modSub(t5, t5, X2, curve->p, num_words);
    uECC_vli_modSub(X2, X2, X1, curve->p, num_words);
    uECC_vli_modMult_fast(Y1, Y1, X2, curve);
    uECC_vli_modSub(X2, X1, t5, curve->p, num_words);
    uECC_vli_modMult_fast(Y2, Y2, X2, curve);
    uECC_vli_modSub(Y2, Y2, Y1, curve->p, num_words);

    uECC_vli_set(X2, t5, num_words);
}
