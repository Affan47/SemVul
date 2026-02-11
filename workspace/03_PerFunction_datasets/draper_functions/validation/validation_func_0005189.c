enter_number() {
    char mstr[5]={'\0','\0','\0','\0','\0'};
    int c;
    int input;
    int in_digits[4]={0,0,0,0};
    bool reinput;
    do {
        reinput = false;
        printf(_("Input a 4-digit number:"));
        if(fgets(mstr, sizeof mstr, stdin) == NULL)
            err_exit(_("Something's got wrong, I'd better quit...\n"));


        bool flag = false;
        if(mstr[0]!='\n'&& mstr[1]!='\n'&& mstr[2]!='\n' &&mstr[3]!='\n')

            while((c = getchar()) != '\n' && c != EOF)
                flag = true;
        if (flag == true) {
            fprintf(stderr, _("Input too long!\n"));
            reinput = true;
            continue;
        }
        input = atoi(mstr);
        if (input < 1000 || input > 9999) {
            fprintf(stderr, _("Must be a number between 1000 and 9999!\n"));
            reinput = true;
            continue;
        }
        for(int i=0; i<4; i++)
            in_digits[i]=(int) (input / tenpow(3-i) )%10;
        if(in_digits[0]==in_digits[1] || in_digits[1]==in_digits[2]
                || in_digits[2]==in_digits[3] || in_digits[0]==in_digits[2]
                || in_digits[0]==in_digits[3] || in_digits[1]==in_digits[3])
        {
            fprintf(stderr, _("Four digits must be unique.\n"));
            reinput = true;
            continue;
        }
    }while(reinput);
    return input;
}
