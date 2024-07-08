
#include<stdio.h>
#include<stdlib.h>

struct map {
    int filename;
    int size;
    int req;
    int start;
    int all[100];
};
struct map b1[100];
int k=0;

struct map1 {
    int filename;
    int size;
    int req;
    int start;
};
struct map1 b2[100];
int w=0;
int link[100];


struct map3 {
    int filename;
    int size;
    int req;
    int index;
};
struct map3 b3[100];
int z=0;
int a3[100][100];

void indexall(int ms,int ds){
    int c,n,j,p,x;
    printf("enter filename:");
    scanf("%d",&c);
    b3[z].filename=c;
    printf("enter file size:");
    scanf("%d",&n);
    b3[z].size=n;

    if(n%ds==0)
        j=n/ds;
    else
        j=(n/ds)+1;
    
    b3[z].req=j+1;
    printf("enter index block:");
    scanf("%d",&x);
    b3[z].index=x;
    printf("enter %d req values:",j);

    for(int i=0;i<j;i++){
        scanf("%d",&p);
        a3[x][i]=p;
    }

    printf("filename\tfilesize\tnoofblock\tindex\tallocateblock\n");

    printf("%d\t\t%d\t\t%d\t\t%d\t\t",b3[z].filename,b3[z].size,b3[z].req,b3[z].index);
    x=b3[z].index;

    for(int i=0;i<j-1;i++){
        printf("%d->",a3[x][i]);
    }
    z++;
    printf("\n");
}

void indexd(int ms,int ds){
    int x;

    printf("filename\tfilesize\tnoofblock\tindex\tallocateblock\n");

    for(int j=0;j<z;j++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t",b3[j].filename,b3[j].size,b3[j].req,b3[j].index);
        x=b3[j].index;

        for(int i=0;i<b3[j].req-1;i++){
            printf("%d->",a3[x][i]);
        }
        printf("\n");
    }
}

void indexds(int ms,int ds){
    int x,p;
    printf("enter filename:");
    scanf("%d",&p);
    printf("filename\tfilesize\tnoofblock\tindex\tallocateblock\n");

    for(int j=0;j<z;j++){
        if(p==b3[j].filename){
            printf("%d\t\t%d\t\t%d\t\t%d\t\t",b3[j].filename,b3[j].size,b3[j].req,b3[j].index);
            x=b3[j].index;

            for(int i=0;i<b3[j].req-1;i++){
                printf("%d->",a3[x][i]);
            }
        }
    }
    printf("\n");
}

void linall(int ms,int ds){
    int c,n,j,past;
    printf("enter filename:");
    scanf("%d",&c);
    b2[w].filename=c;
    printf("enter file size:");
    scanf("%d",&n);
    b2[w].size=n;
    int x;

    if(n%ds==0)
        j=n/(ds-1);
    else
        j=(n/(ds-1))+1;

    b2[w].req=j;
    printf("enter %d required values:",j);

    for(int i=0;i<j;i++){
        if(i==0){
            scanf("%d",&x);
            b2[w].start=x;
            past=x;
        }
        else{
            scanf("%d",&x);
            link[past]=x;
            past=x;
        }
    }

    link[past]=-1;
    printf("filename\tfilesize\tnoofblock\tstartblock\tallocateblock\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t",b2[w].filename,b2[w].size,b2[w].req,b2[w].start);
    x=b2[w].start;

    for(int i=0;i<b2[w].req && x!=-1;i++){
        printf("%d->",x);
        x=link[x];
    }
    w++;
    printf("\n");
}

void lind(int ms,int ds){
    int x;
    printf("filename\tfilesize\tnoofblock\tstartblock\tallocateblock\n");

    for(int i=0;i<w;i++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t",b2[i].filename,b2[i].size,b2[i].req,b2[i].start);
        x=b2[i].start;

        for(int j=0;j<b2[i].req&&x!=-1;j++){
            printf("%d->",x);
            x=link[x];
        }
        printf("\n");
    }
}

void linds(int ms,int ds){
    int p,x;
    printf("enter filename:");
    scanf("%d",&p);
    printf("filename\tfilesize\tnoofblock\tstartblock\tallocateblock\n");

    for(int i=0;i<w;i++){
        if(p==b2[i].filename){
            printf("%d\t\t%d\t\t%d\t\t%d\t\t",b2[i].filename,b2[i].size,b2[i].req,b2[i].start);
            x=b2[i].start;

            for(int j=0;j<b2[i].req&&x!=-1;j++){
                printf("%d->",x);
                x=link[x];
            }
        }
    }
    printf("\n");
}

void seqall(int ms,int ds) {
    int c,n,p,i,j;
    int a[ms/ds];
    printf("enter filename:");
    scanf("%d",&c);
    b1[k].filename=c;
    printf("enter file size:");
    scanf("%d",&n);
    b1[k].size=n;
    printf("starting point:");
    scanf("%d",&p);
    b1[k].start=p;

    if(n%ds==0)
        j=n/ds;
    else
        j=(n/ds)+1;

    b1[k].req=j;
    printf("filename\tfilesize\tnoofblock\tstartblock\tallocateblock\n");
    printf("%d\t\t%d\t\t%d\t\t%d\t\t",c,n,j,p);

    for(i=p;i<p+j;i++) {
        printf("%d, ",i);
        b1[k].all[i-p]=i;
    }
    k++;
    printf("\n");
}

void seqd(int ms,int ds){
    printf("filename\tfilesize\tnoofblock\tstartblock\tallocateblock\n");

    for(int j=0;j<k;j++){
        printf("%d\t\t%d\t\t%d\t\t%d\t\t",b1[j].filename,b1[j].size,b1[j].req,b1[j].start);

        for(int i=0;i<b1[j].req;i++){
            printf("%d, ",b1[j].all[i]);
        }
        printf("\n");
    }
}

void seqds(int ms,int ds){
    int x;
    printf("enter file name:");
    scanf("%d",&x);
    printf("filename\tfilesize\tnoofblock\tstartblock\tallocateblock\n");

    for(int j=0;j<k;j++){
        if(x==b1[j].filename){
            printf("%d\t\t%d\t\t%d\t\t%d\t\t",b1[j].filename,b1[j].size,b1[j].req,b1[j].start);

            for(int i=0;i<b1[j].req;i++){
                printf("%d, ",b1[j].all[i]);
            }
        }
    }
    printf("\n");
}

void seq(int ms,int ds){
    int x,y=1;

    while(y==1){
        printf("select 1:allocate file 2:display file info 3:display specific file info:");
        scanf("%d",&x);

        switch(x){
            case 1: seqall(ms,ds);
                    break;
            case 2: seqd(ms,ds);
                    break;
            case 3: seqds(ms,ds);
                    break;
        }

        printf("enter to cont 1/0:");
        scanf("%d",&y);
    }
}

void inde(int ms,int ds){
    int x,y=1;

    while(y==1){
        printf("select 1:allocate file 2:display file info 3:display specific file info:");
        scanf("%d",&x);

        switch(x){
            case 1: indexall(ms,ds);
                    break;
            case 2: indexd(ms,ds);
                    break;
            case 3: indexds(ms,ds);
                    break;
        }

        printf("enter to cont 1/0:");
        scanf("%d",&y);
    }
}

void linked(int ms,int ds){
    int x,y=1;

    while(y==1){
        printf("select 1:allocate file 2:display file info 3:display specific file info:");
        scanf("%d",&x);

        switch(x){
            case 1: linall(ms,ds);
                    break;
            case 2: lind(ms,ds);
                    break;
            case 3: linds(ms,ds);
                    break;
        }

        printf("enter to cont 1/0:");
        scanf("%d",&y);
    }
}

void main(){
    int ms,ds,x;

    printf("enter memory size:");
    scanf("%d",&ms);
    printf("enter data block size:");
    scanf("%d",&ds);
    printf("select 1:sequence 2:linked 3:indexed 4:exit:");
    scanf("%d",&x);

    switch(x){
        case 1: seq(ms,ds);
                break;
        case 2: linked(ms,ds);
                break;
        case 3: inde(ms,ds);
                break;
    }
}
