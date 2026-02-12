floorLog2 (int x)
{


    int y = 0;

    while (x > 1)
    {
	y +=  1;
	x >>= 1;
    }

    return y;
}
