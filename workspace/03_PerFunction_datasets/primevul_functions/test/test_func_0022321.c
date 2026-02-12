static size_t  *populate_cksumlens(void)
	{
	int 		i, j, n;
	static size_t 	*cklens = NULL;

#ifdef KRB5_MIT_OLD11
	n = krb5_max_cksum;
#else
	n = 0x0010;
#endif

#ifdef KRB5CHECKAUTH
	if (!cklens && !(cklens = (size_t *) calloc(sizeof(int),n+1)))  return NULL;

	for (i=0; i < n; i++)  {
		if (!valid_cksumtype(i))  continue;
		for (j=0; j < n; j++)  {
			if (cklens[j] == 0)  {
				cklens[j] = krb5_checksum_size(NULL,i);
				break;
				}
			if (cklens[j] == krb5_checksum_size(NULL,i))  {
				break;
				}
			}
		}
#endif

	return cklens;
	}
