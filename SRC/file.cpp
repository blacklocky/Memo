#include"file.h"

int readfilelines(char *path,char lines[][8]){
    FILE *fp;
    char ch;
    int i=0;
    
    if((fp = fopen(path,"r"))==NULL){
        fclose(fp);
        exit(1);
    }
    for(;(ch = fgetc(fp))!=EOF;){
        int j=0;
        lines[i][j] = ch;
        j++;
        for(;(ch = fgetc(fp)) != '\n';j++){
            if(ch == EOF) {
                i--;
                break;
            }
            lines[i][j] = ch;
        }
        i++;
    }
    fclose(fp);
    return i;
}

void logmessage(char *msg){
    FILE *flog;
    if((flog = fopen(LOGMSGPATH,"r"))==NULL){

        flog = fopen(LOGMSGPATH,"w+");
        fclose(flog);
    }else{
        fclose(flog);
        flog = fopen(LOGMSGPATH,"a+");
        fprintf(flog,"%s\n",msg);
        fclose(flog);

    }
}

