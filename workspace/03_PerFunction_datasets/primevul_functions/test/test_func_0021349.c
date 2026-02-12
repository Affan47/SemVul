PublicMarshalAndComputeName(
			    TPMT_PUBLIC     *publicArea,
			    TPM2B_NAME      *name
			    )
{


    TPM2B_TEMPLATE       marshaled;

    BYTE                *buffer = (BYTE *)&marshaled.t.buffer;

    if(publicArea->nameAlg == TPM_ALG_NULL)
	name->t.size = 0;
    else
	{

	    marshaled.t.size = TPMT_PUBLIC_Marshal(publicArea, &buffer, NULL);

	    ObjectComputeName(marshaled.t.size, marshaled.t.buffer,
			      publicArea->nameAlg, name);
	}
    return name;
}
