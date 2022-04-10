#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct virus {
    unsigned short SigSize;
    unsigned char* sig;
    char virusName[16];
} virus;

typedef struct link link;

struct link {
    link *nextVirus;
    virus *vir;
};


void printHex(unsigned char* buffer,int size) {
    for (int i = 0; i < size; ++i) {
        printf("%02hhX ",buffer[i]);
        if( i % 16 == 0 && i != 0)
            printf("\n");
    }
    printf("\n");
}




void readVirus(virus* vir, FILE* input) {
    fread(&vir->SigSize,sizeof (unsigned short ),1,input);
    unsigned char *sig = (unsigned char *)calloc(vir->SigSize, sizeof(unsigned char));
    fread(sig,sizeof (unsigned char ),vir->SigSize,input);
    vir->sig = sig;
    fread(vir->virusName, sizeof(char ),16,input);
}

void printVirus(virus* vir, FILE* output) {
    fprintf(output,"Virus name : %s\n", vir->virusName);
    fprintf(output,"Virus size : %d\n", vir->SigSize);
    fprintf(output,"signature:\n");
    printHex(vir->sig,vir->SigSize);
}


void list_print(link *virus_list, FILE* output) {
    virus *head = virus_list->vir;
    while (head != NULL) {
        printVirus(head,output);
        virus_list = (link *) virus_list->nextVirus;
        head = virus_list->vir;
    }

}

link* list_append(link* virus_list, link* to_add) {
    to_add->nextVirus = virus_list;
    return to_add;
}


void list_free(link *virus_list) {
    virus *head = virus_list->vir;
    if(head != NULL) {
        list_free(virus_list->nextVirus);
        free(head->sig);
        free(head);
        free(virus_list);
    }
    else
        free(virus_list);
}

link *Load_signature(link *virus_list) {

    FILE *input;
    char messege[256];
    scanf("%s",messege);
    input= fopen(messege,"rb");
    if(input == NULL) {
        printf("empty file\n");
        free(virus_list);
        exit(0);
    }
    fseek(input,0,SEEK_END);
    int endoffile = ftell(input);
    fseek(input,0,SEEK_SET);
    int start = 0;
    while (endoffile != start) {
        virus *virus1 = (virus*)malloc(sizeof(virus));
        readVirus(virus1,input);
        link *link1 = (link*) malloc(sizeof (link));
        link1->vir = virus1;
        link1->nextVirus = virus_list;
        start = ftell(input);
        virus_list = list_append(virus_list,link1);
    }
    fclose(input);
    return virus_list;
}

void detect_virus(char *buffer, unsigned int size, link *virus_list) {
    virus *head = virus_list->vir;
    unsigned short i = 0;
    while (head != NULL) {
        while (i <= size && head != NULL) {
            if (memcmp((buffer + i),head->sig,head->SigSize) == 0) {
                printf("Byte location: %d\n", i);
                printf("Virus name: %s\n", head->virusName);
                printf("Virus signature size: %d\n\n", head->SigSize);
                virus_list = (link *) virus_list->nextVirus;
                head = virus_list->vir;
                i = 0;
            }
            if(i == size) {
                virus_list = (link *) virus_list->nextVirus;
                head = virus_list->vir;
                i = 0;
            }
            else {
                i = i + 1;
            }
        }

    }

}


void kill_virus(char *fileName, int signatureOffset, int signatureSize) {
    FILE *in;
    in= fopen(fileName,"rb+");
    if(in == NULL) {
        printf("no file");
        exit(0);
    }
    unsigned char fix[signatureSize];
    for (int i = 0; i < signatureSize; ++i) {
        fix[i] = 0x90;
    }
    fseek(in,signatureOffset,SEEK_SET);
    fwrite(fix, sizeof(unsigned char ),signatureSize,in);
    fclose(in);
}


int main(int argc, char *argv[]) {

    int load = 0;
    link *head = (link*) malloc(sizeof (link));
    head->vir = NULL;
    head->nextVirus = NULL;
    while (1) {
        int c;
        printf("please choose a function:\n");
        printf("1) Load signatures\n");
        printf("2) Print signatures\n");
        printf("3) Detect viruses\n");
        printf("4) Fix file\n");
        printf("5) Quit\n");
        printf("option: ");
        c = (fgetc(stdin)) - '0';
        if (c == -38)
            c = (fgetc(stdin)) - '0';
        else
            fgetc(stdin);
        switch (c) {
            case 1: {
                head = Load_signature(head);
                load = 1;
                break;
            }
            case 2: {
                if(load == 1)
                    list_print(head,stdout);
                break;
            }
            case 3: {
                char buffer[10000] = {};
                char messege[256];
                scanf("%s",messege);
                FILE *in;
                in= fopen(messege,"rb");
                fseek(in,0,SEEK_END);
                int size = ftell(in);
                fseek(in,0,SEEK_SET);
                fread(buffer,sizeof (char ),size,in);
                detect_virus(buffer, size,head);
                fclose(in);
                break;
            }
            case 4: {
                char messege[256];
                scanf("%s",messege);
                int byte;
                scanf("%d",&byte);
                int size;
                scanf("%d",&size);
                kill_virus(messege,byte,size);
                break;
            }
            case 5: {
                list_free(head);
                return 0;
            }
        }
    }


}