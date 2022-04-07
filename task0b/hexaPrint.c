#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *file;
    file= fopen(*(argv + 1),"rb");
    char arr[10];
    if(file == NULL) {
        printf("empty file\n");
        return 0;
    }
    fread(arr,sizeof (char ),10,file);
    for (int i = 0; i < n; ++i) {
        printf("%X ",arr[i]);
    }

}
