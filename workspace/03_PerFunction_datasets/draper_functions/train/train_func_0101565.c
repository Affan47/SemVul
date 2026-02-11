g_pkcs11_pin_get_value (GTlsPassword  *password,
                        gsize         *length)
{
  GPkcs11Pin *self = G_PKCS11_PIN (password);

  if (!self->priv->pin)
    {
      if (length)
        *length = 0;
      return NULL;
    }

  return p11_kit_pin_get_value (self->priv->pin, length);
}
