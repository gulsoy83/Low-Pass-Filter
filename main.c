#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define DOSYAISMIUZUNLUGU 50
void swap (int *x, int *y){
	int tmp;
	tmp = *x;
	*x = *y;
	*y=tmp;
}
int partition(int *dizi,int p,int r){
	
  int pivot = dizi[p];
    int i=p,j=r+1;
    do{
	    do{
	    	++i;
		}while(i<j && dizi[i]<=pivot);
		
	
	    do{
            --j;	
	    }while(dizi[j]>pivot);
	    swap(&dizi[i],&dizi[j]);
    
	}while(i<j);
	swap(&dizi[i],&dizi[j]);
	swap(&dizi[p],&dizi[j]);
	return j;
}

void quickSort(int *dizi,int p,int r){
	int q;
	if(p<r){
	
		q = partition(dizi,p,r);
	
		quickSort(dizi,p,q-1);
		quickSort(dizi,q+1,r); 
	}
}
unsigned char ** ortfiltre(unsigned char **goruntu,int satir,int sutun,int max){
	int i,j;
	int** yenigoruntu =(int**) malloc(sizeof(int*)*satir);
	for(i=0;i<satir;i++)
    	yenigoruntu[i] = (int *) malloc (sizeof(int)*sutun);
			
    int tmp=0;
	for(i=1;i<satir-1;i++){
		for(j=1;j<sutun-1;j++){
			int x,y;
			tmp = 0;
			for(x=-1;x<=1;x++){
				for(y=-1;y<=1;y++){
					tmp+=goruntu[i+x][j+y] * 1;
				}	
			}
			
			yenigoruntu[i][j] = tmp/9;
		}
	}
	
	i=0;
	for(j=0;j<sutun;j++){
		yenigoruntu[i][j] = goruntu[i][j];
	}
	i=satir-1;
	for(j=0;j<sutun;j++){
		yenigoruntu[i][j] = goruntu[i][j];
	}
	j=0;
	for(i=1;i<satir-1;i++)
	    yenigoruntu[i][j] = goruntu[i][j];
	j=sutun-1;
	for(i=1;i<satir-1;i++)
	    yenigoruntu[i][j] = goruntu[i][j];
	
	
	int min=0,maks=0;
	for(i=0;i<satir;i++){
		for(j=0;j<sutun;j++){
	        if(yenigoruntu[i][j]<min) min=yenigoruntu[i][j];
	        if(yenigoruntu[i][j]>maks) maks =yenigoruntu[i][j];
	    }
	}
	
	for(i=0;i<satir;i++){
		for(j=0;j<sutun;j++){
			if(yenigoruntu[i][j]>max || yenigoruntu[i][j]<0)
			yenigoruntu[i][j] = (yenigoruntu[i][j]-min)/(maks-min);
        }
    }
    
    
    unsigned char** yeni2goruntu =(unsigned char**) malloc(sizeof(unsigned char*)*satir);
	for(i=0;i<satir;i++){
	    yeni2goruntu[i] = (unsigned char*) malloc (sizeof(unsigned char)*sutun);
        for(j=0;j<sutun;j++){
        	yeni2goruntu[i][j] = (unsigned char) yenigoruntu[i][j];
		}
	}
	for(i=0;i<satir;i++)
    free(yenigoruntu[i]);
	   
	free(yenigoruntu);
	
	
	
	return yeni2goruntu;
}


unsigned char** medfiltre(unsigned char **goruntu,int satir,int sutun,int max){
	int i,j;
	int** yenigoruntu =(int**) malloc(sizeof(int*)*satir);
	for(i=0;i<satir;i++)
    	yenigoruntu[i] = (int *) malloc (sizeof(int)*sutun);
			
    int tmp=0,mydizi[9];
	for(i=1;i<satir-1;i++){
		for(j=1;j<sutun-1;j++){
			int x,y;
			tmp = 0;
			int k=0;
			for(x=-1;x<=1;x++){
				for(y=-1;y<=1;y++){
					mydizi[k++]=goruntu[i+x][j+y] * 1;
				}	
			}
			
			quickSort(mydizi,0,8);
			yenigoruntu[i][j] = mydizi[4];
		}
	}
	
	i=0;
	for(j=0;j<sutun;j++){
		yenigoruntu[i][j] = goruntu[i][j];
	}
	i=satir-1;
	for(j=0;j<sutun;j++){
		yenigoruntu[i][j] = goruntu[i][j];
	}
	j=0;
	for(i=1;i<satir-1;i++)
	    yenigoruntu[i][j] = goruntu[i][j];
	j=sutun-1;
	for(i=1;i<satir-1;i++)
	    yenigoruntu[i][j] = goruntu[i][j];
	
	
	int min=0,maks=0;
	for(i=0;i<satir;i++){
		for(j=0;j<sutun;j++){
	        if(yenigoruntu[i][j]<min) min=yenigoruntu[i][j];
	        if(yenigoruntu[i][j]>maks) maks =yenigoruntu[i][j];
	    }
	}
	
	for(i=0;i<satir;i++){
		for(j=0;j<sutun;j++){
			if(yenigoruntu[i][j]>max || yenigoruntu[i][j]<0)
			yenigoruntu[i][j] = (yenigoruntu[i][j]-min)/(maks-min);
        }
    }
    
    
    unsigned char** yeni2goruntu =(unsigned char**) malloc(sizeof(unsigned char*)*satir);
	for(i=0;i<satir;i++){
	    yeni2goruntu[i] = (unsigned char*) malloc (sizeof(unsigned char)*sutun);
        for(j=0;j<sutun;j++){
        	yeni2goruntu[i][j] = (unsigned char) yenigoruntu[i][j];
		}
	}
	for(i=0;i<satir;i++)
    free(yenigoruntu[i]);
	   
	free(yenigoruntu);
	
	
	
	return yeni2goruntu;
}

void dosyayayaz(char *filename, unsigned char **goruntu, int height, int width, char *tip){
	FILE *n = fopen(filename,"wb");
	if(n==NULL) exit(-1);
	
	int i,j;
	if(tip[1]=='2'){ 
        fprintf(n,"P2\n#enes\n%d %d\n255\n",width,height);
	    
        for(i=0;i<height;i++){
           for(j=0;j<width;j++){
           	  fprintf(n,"%d ",goruntu[i][j]);
		   }
		   fprintf(n,"\n");
	   }

	}
	else if(tip[1]=='5'){
	   fprintf(n,"P5\n#enes\n%d %d\n255",width,height);
       for(i=0;i<height;i++){
           fwrite(goruntu[i],sizeof(unsigned char),(width),n);
	   }
	
	}
        
       
    fclose(n);
        
    
        
		
	for(i=0;i<height;i++)
    free(goruntu[i]);
	   
	free(goruntu);
	     
}

unsigned char** dosyayioku(char* filename,int *satir, int *sutun, int *maksval, char *pgmtipi){
	FILE *pgmdosya;
	pgmdosya = fopen(filename,"rb");
	if(pgmdosya==NULL){
	  printf("Belirtilen dosya acilamadi.\n");
	  exit(-1);	
	} 
	printf("Okunan dosya: %s\n", filename);


	    
    char tip[3];
    tip[0]=getc(pgmdosya);
    tip[1]=getc(pgmdosya);
	tip[2]='\0'; 
	   
    if (strcmp(tip,"P5") !=0 && strcmp(tip,"P2") != 0){
   	    printf("Gecersiz pgm dosyasi.\n");
       exit(-1);
    }
   
   printf("PGM Tipi: %s\n",tip);

    //dosyanin basinda yazan p2, p5 ... degerini okuyoruz.
    while(getc(pgmdosya) != '\n');
    while (getc(pgmdosya) == '#'){
                while (getc(pgmdosya) != '\n');
        }
        fseek(pgmdosya, -1, SEEK_CUR);
    //yorum satiri varsa atla.
	
    int width,height,maxVal;
    fscanf(pgmdosya,"%d%d", &width,&height);
    
    fscanf(pgmdosya,"%d", &maxVal);
    printf("\nGenislik: %d, Yukseklik: %d\nMax Deger: %d",width,height,maxVal);
   //resmin bilgilerini al.
    unsigned char** goruntu =(unsigned char**) malloc(sizeof(unsigned char*)*height);
    
	int i,j;
    
   
    if(tip[1]=='2'){ 
	    
	    //P2 tipi icin verileri matrise oku.
    	
    	for(i=0;i<height;i++){
    	    goruntu[i] = (unsigned char *) malloc (sizeof(unsigned char)*width);
			for(j=0;j<width;j++){
				fscanf(pgmdosya,"%d ",&goruntu[i][j]);
				
			}
		}
    	
    }
    else if(tip[1]=='5'){
		    //P5 tipi icin goruntuleri matrise oku.
		
    	     for(i=0;i<height;i++){
    	        goruntu[i] = (unsigned char *) malloc (sizeof(unsigned char)*width);
		        fread(goruntu[i],sizeof(unsigned char),(width),pgmdosya);
	    	}
		
	
	}
    
		 
		fclose(pgmdosya); 
		*satir=height;
		*sutun=width;
		*maksval=maxVal;
	    strcpy(pgmtipi,tip);
	     
		return goruntu;    
    	        
}

int main(int argc, char *argv[]) {
	
	char filename[DOSYAISMIUZUNLUGU];
	printf("Acilacak pgm dosyasinin ismini <filename.pgm> formatinda giriniz.\n");
	scanf("%s",filename);
	fflush(stdin);
	
	int satir =0, sutun =0, maxval =0;
	char pgmtipi[3];
	
	unsigned char ** goruntu;
	goruntu = dosyayioku(filename,&satir,&sutun,&maxval,pgmtipi);
	
	
	
	char yazilacakdosyaninadi[DOSYAISMIUZUNLUGU];
	strcpy(yazilacakdosyaninadi,filename);
	char yazilacakdosyaninadi2[DOSYAISMIUZUNLUGU];
	strcpy(yazilacakdosyaninadi2,filename);
	
	unsigned char **ortgoruntu = ortfiltre(goruntu,satir,sutun,maxval);
	unsigned char **medgoruntu = medfiltre(goruntu,satir,sutun,maxval);
	
	
	dosyayayaz(strcat(yazilacakdosyaninadi,"-ort.pgm"),ortgoruntu,satir,sutun,pgmtipi);
	dosyayayaz(strcat(yazilacakdosyaninadi2,"-med.pgm"),medgoruntu,satir,sutun,pgmtipi);
    
	
	
	
	return 0;
}


