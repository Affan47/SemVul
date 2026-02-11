avgDiamondHeight(int i, int j, int stride){
    if (i == 0){
        return (this->terrain[this->side_size-1-stride][j] +
                    this->terrain[i+stride][j] + this->terrain[i][j-stride] +
                    this->terrain[i][j+stride]) / 4.0f;
    } else if (i == this->side_size-1){
        return (this->terrain[i-stride][j] + this->terrain[stride][j] +
                    this->terrain[i][j-stride] +
                    this->terrain[i][j+stride]) / 4.0f;
    } else if (j == 0){
        return (this->terrain[i-stride][j] + this->terrain[i+stride][j] +
                    this->terrain[i][this->side_size-1-stride] +
                    this->terrain[i][j+stride]) / 4.0f;
    } else if (j == this->side_size-1){
        return (this->terrain[i-stride][j] + this->terrain[i+stride][j] +
                    this->terrain[i][j-stride] +
                    this->terrain[i][stride]) / 4.0f;
    } else {
        return (this->terrain[i-stride][j] + this->terrain[i+stride][j] +
                    this->terrain[i][j-stride] +
                    this->terrain[i][j+stride]) / 4.0f;
    }

}
