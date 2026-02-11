av_program_add_stream_index(AVFormatContext *ac, int progid, unsigned int idx)
{
    int i, j;
    AVProgram *program=NULL;
    void *tmp;

    for(i=0; i<ac->nb_programs; i++){
        if(ac->programs[i]->id != progid)
            continue;
        program = ac->programs[i];
        for(j=0; j<program->nb_stream_indexes; j++)
            if(program->stream_index[j] == idx)
                return;

        tmp = av_realloc(program->stream_index, sizeof(unsigned int)*(program->nb_stream_indexes+1));
        if(!tmp)
            return;
        program->stream_index = tmp;
        program->stream_index[program->nb_stream_indexes++] = idx;
        return;
    }
}
