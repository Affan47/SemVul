size_t olm_clear_pk_signing(OlmPkSigning *sign) {

    olm::unset(sign, sizeof(OlmPkSigning));

    new(sign) OlmPkSigning();
    return sizeof(OlmPkSigning);
}
