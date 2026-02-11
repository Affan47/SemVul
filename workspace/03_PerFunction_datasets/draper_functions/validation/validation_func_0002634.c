encrypt_display(void)
{
    printf("Autoencrypt for output is %s. Autodecrypt for input is %s.\r\n",
	   autoencrypt?"on":"off", autodecrypt?"on":"off");

    if (encrypt_output)
	printf("Currently encrypting output with %s\r\n",
	       ENCTYPE_NAME(encrypt_mode));
    else
	printf("Currently not encrypting output\r\n");

    if (decrypt_input)
	printf("Currently decrypting input with %s\r\n",
	       ENCTYPE_NAME(decrypt_mode));
    else
	printf("Currently not decrypting input\r\n");
}
