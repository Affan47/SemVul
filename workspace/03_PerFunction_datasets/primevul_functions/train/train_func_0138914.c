size_t olm_clear_pk_decryption(
    OlmPkDecryption *decryption
) {

    olm::unset(decryption, sizeof(OlmPkDecryption));

    new(decryption) OlmPkDecryption();
    return sizeof(OlmPkDecryption);
}
