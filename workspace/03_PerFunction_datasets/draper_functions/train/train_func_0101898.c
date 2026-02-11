read_awars(AW_root *awr,const char *awar_prefix){
    char buffer[1024];
    int x,y;
    for (x = 0;x<size;x++){
        if (x_description[x]){
            for (y = 0;y<size;y++){
                if (y_description[y]){
                    sprintf(buffer,"%s/B%s/B%s",awar_prefix,x_description[x],y_description[y]);
                    this->set(x,y,awr->awar(buffer)->read_float());
                }
            }
        }
    }
}
