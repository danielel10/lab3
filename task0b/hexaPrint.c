//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//void printHex(char* buffer,int size) {
//    for (int i = 0; i < size; ++i) {
//        printf("%02hhX ",buffer[i]);
//    }
//    printf("\n");
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
//    int size = ftell(in);
//    char arr[size];
//
//    fseek(in,0,SEEK_SET);
//
//    fread(arr,sizeof (char ),size,in);
//    printHex(arr,size);
//
//    fclose(in);
//
//    return 0;
//
//
//}
