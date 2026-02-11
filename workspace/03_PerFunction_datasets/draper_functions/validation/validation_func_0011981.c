WriteScores(void)
{
    FILE *f;

    if ((f=fopen("ETWScores","r")))     {
        int i,j;

        fprintf(f, "%d\n", score_number);

        for(i=0;i<score_number;i++)        {
            for(j=0;j<6;j++)
                if(scores[i*2+1].Text[j]==0)
                    scores[i*2+1].Text[j]=' ';

            scores[i*2+1].Text[5]=' ';
            fprintf(f,"%s\n",scores[i*2+1].Text);

            for(j=0;j<6;j++)
                if(scores[i*2+1].Text[j]==' ')
                    scores[i*2+1].Text[j]=0;
        }

        fclose(f);
    }
}
