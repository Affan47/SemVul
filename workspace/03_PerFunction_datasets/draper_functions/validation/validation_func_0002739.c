getNumDistinct()const
{
int res= 0;
if(size()> 0)
res++;
for(int i= 1;i<size();i++)
if(operator[](i)!=operator[](i-1))
res++;
return res;
}
