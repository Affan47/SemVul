detectOptimizationMode (const vector<sliceOptimizationData>& optData)
{
    OptimizationMode w;


#ifdef IMF_HAVE_SSE2


    switch(optData.size())
    {
        case 3 : break;
        case 4 : break;
        case 6 : break;
        case 8 : break;
        default :
            return w;
    }


    size_t bankSize = optData.size()>4 ? optData.size()/2 : optData.size();

    for(size_t i=0;i<optData.size();i++)
    {
        const sliceOptimizationData& data = optData[i];

        if(data.fill)
        {
            if(i!=3 && i!=7)
            {
                return w;
            }
        }


        if(data.xStride !=bankSize*2)
        {
            return w;
        }


        if(i!=0 && i!=bankSize)
        {
            if(data.base!=optData[i-1].base+2)
            {
                return w;
            }
        }
        if(i!=0)
        {

            if(data.yStride!=optData[i-1].yStride)
            {
                return w;
            }
        }
    }


    w._ySampling=optData[0].ySampling;
    w._optimizable=true;

#endif

    return w;
}
