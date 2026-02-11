add_certs_in_dir(X509_LOOKUP *lookup, char *path)
{
    char buf[MAXPATH];
    struct direct *d;
    DIR	*dirp;
    int  ret = 0;

    dirp = opendir(path);
    if(dirp){

        while(!ret && (d=readdir(dirp)) != NULL){
            if(srchrstr(d->d_name, ".crt")){
    	    	build_path(buf, path, d->d_name, sizeof(buf));

    	    	if(!X509_LOOKUP_load_file(lookup, buf, X509_FILETYPE_PEM)){
		    q_status_message1(SM_ORDER, 3, 3, _("Error loading file %s"), buf);
		    ret = -1;
		}
            }

        }

        closedir(dirp);
    }

    return ret;
}
