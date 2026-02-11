each_pattern_pixel(int pos,int *x,int *y)
    {
        switch(pos){
        case 0:
            if(this->_pattern_c>14)
                return(NULL);
            break;
        case 1:
            if(this->_pattern_c>15)
                return(NULL);
            break;
        default:
            return(NULL);
        }

        *x=format_info_addr[pos][this->_pattern_c][0];
        *y=format_info_addr[pos][this->_pattern_c][1];

        this->_pattern_c++;
        return(this);
    }
}
