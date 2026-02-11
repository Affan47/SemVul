Obtain_sessionrkeys(bst128 kappa,u32* rkey_enc){
	u32 tempkeys[44];
	int i,j;
	bst128 counter;

  rijndaelKeySetupEnc(tempkeys,kappa.t);


	for(i=0;i<4;i++){
		rkey_enc[i]^=tempkeys[i+4];
		for(j=2;j<9;j++){
			rkey_enc[4*j+i]^=tempkeys[4*j+i];
		}
		counter.t[i]=tempkeys[36+i];
		rkey_enc[40+i]^=tempkeys[40+i];
	}

	counter.s[0]|=(0x1U);
	counter.s[1]|=(0x1U);
return counter;

}
