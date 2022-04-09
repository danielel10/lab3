//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct virus {
//    unsigned short SigSize;
//    unsigned char* sig;
//    char virusName[16];
//} virus;
//
//void printHex(char* buffer,int size) {
//    for (int i = 0; i < size; ++i) {
//        printf("%02hhX ",buffer[i]);
//        if( i % 22 == 0 && i != 0)
//            printf("\n");
//    }
//    printf("\n");
//}
//
//
//
//
//void readVirus(virus* vir, FILE* input) {
//    fread(&vir->SigSize,sizeof (unsigned short ),1,input);
//    unsigned char *sig = (unsigned char *)calloc(vir->SigSize, sizeof(unsigned char));
//    fread(sig,sizeof (unsigned char ),vir->SigSize,input);
//    vir->sig = sig;
//    fread(vir->virusName, sizeof(char ),16,input);
//}
//
//void printVirus(virus* vir, FILE* output) {
//    fprintf(output,"Virus name : %s\n", vir->virusName);
//    fprintf(output,"Virus size : %d\n", vir->SigSize);
//    fprintf(output,"signature:\n");
//    printHex(vir->sig,vir->SigSize);
//}
//
//
//int main(int argc, char *argv[]) {
//    FILE *in;
//    in= fopen(*(argv + 1),"rb");
//    if(in == NULL) {
//        printf("empty file\n");
//        return 0;
//    }
//    fseek(in,0,SEEK_END);
//    int endoffile = ftell(in);
//    fseek(in,0,SEEK_SET);
//    int start = 0;
//    while (endoffile != start) {
//        virus virus1;
//        readVirus(&virus1,in);
//        start = ftell(in);
//        printVirus(&virus1,stdout);
//        free(virus1.sig);
//    }
//
//    fclose(in);
//
//    return 0;
//
//
//}