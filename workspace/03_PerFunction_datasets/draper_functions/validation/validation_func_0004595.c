loadThread(struct donneesPub *dp){
    int i;


    for(i=0; i<dp->nclnt; i++){
        write(0,".",1);
        initClientPThread(i, dp);
    }
    return 0;
}
