ObjectComputeName(
		  UINT32           size,
		  BYTE            *publicArea,
		  TPM_ALG_ID       nameAlg,
		  TPM2B_NAME      *name
		  )
{

    name->t.size = CryptHashBlock(nameAlg, size, publicArea,
				  sizeof(name->t.name) - 2,
				  &name->t.name[2]);

    UINT16_TO_BYTE_ARRAY(nameAlg, name->t.name);
    name->t.size += 2;
    return name;
}
