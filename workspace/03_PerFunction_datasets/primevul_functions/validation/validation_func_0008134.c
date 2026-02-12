yaffs_validate_integer_field(std::string numStr){
    unsigned int i;


    if(numStr.length() == 0){
        return 1;
    }


    for(i = 0;i < numStr.length();i++){
        if(isdigit(numStr[i]) == 0){
            return 1;
        }
    }

    return 0;
}
