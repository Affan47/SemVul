size_t olm_clear_pk_encryption(
    OlmPkEncryption *encryption
) {

    olm::unset(encryption, sizeof(OlmPkEncryption));

    new(encryption) OlmPkEncryption();
    return sizeof(OlmPkEncryption);
}
