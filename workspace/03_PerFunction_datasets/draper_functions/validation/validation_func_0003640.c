X509_d2i_fp(FILE *out, X509** buf) {
   if (K_ASN1_d2i_fp) return reinterpret_cast<X509 *>((K_ASN1_d2i_fp)(reinterpret_cast<char *(*)()>(K_X509_new), reinterpret_cast<char *(*)()>(K_d2i_X509), out, reinterpret_cast<unsigned char **>(buf)));
   else return 0L;
}
