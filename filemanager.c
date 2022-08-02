#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(void){
	FILE *file ,*file2,*file3;
	int id, status,status2, change, x, i, z, y, n, index, linenumber;
	int linelength = 0, l = 0 , c = 0, line = 0;
	long offset = 0;
	long int character;
	char fileName[30], fileName2[30], helpp[10], dizgi[500], dizgi22[500]; 
	char info, okay,choice,info2,info3;
	char *f = (char*)malloc(120), *s = (char*)malloc(120);
	
	do{
		printf("\n*********************************\n");
		printf("------FILEMANAGER------\n");
		printf("Komut giriniz: \n");
		printf("A --> Yeni bir dosya olusturma\n");
		printf("B --> Mevcut dosyayi silme\n");
		printf("C --> Mevcut bir dosyayi yeniden adlandirma\n");
		printf("D --> Dosya kopyalama\n");
		printf("E --> Dosyayi bir klasorden digerine tasima\n");
		printf("**Text dosyasi islemleri**\n");
		printf("F --> Dosyanin sonuna metin ekleme;\n");
		printf("G --> Dosya icinde belirli bir konuma metin ekleme;\n");
		printf("K --> Bir dosyada bulunan tum metni kaldirma/silme\n");
		printf("J --> Dosyayi belirli bir yere kadar okuma\n");
		printf("H --> HELP KOMUTU BILGI\n");
		printf("Q --> CIKIS\n");
		printf("*********************************");
		printf("\nKomutunuz: ");
        scanf(" %c",&choice);
        
        
        if(toupper(choice) == 'A'){ //yeni dosya yaratma
			printf("\nDosya adi giriniz: ");
			scanf("%s",fileName);
			
			
			if(access(fileName,F_OK)==0){  //ayný isimli dosya mevcut olduðunda dosya oluþturmaya izin verilmiyor
				printf("Ayni isimli dosya zaten mevcut,dosya olusturulamadi!\nMenuye yonlendirme yapiliyor...");
			}
			else{
				file= fopen(fileName,"a+"); //dosya yaratiliyor
				printf("Dosya basariyla olusturuldu...");
				fclose(file);
			}	
		}
		else if(toupper(choice) == 'B'){ //dosya silme 
			printf("\nSilinecek dosya adini yaziniz: ");
			scanf("%s",fileName);
      		printf("\nDosya silinecek onayliyor musunuz? (E/H): ");
            scanf(" %c",&okay);
      		
			if(toupper(okay) == 'E')
			{   
                status = remove(fileName); //dosyayi siliyoruz
			    if(status == 0) 
                    
				    printf("\n%s dosyasi basariyla silindi...", fileName);
			    else
			    {
                    
				    perror("\nERROR");
				    printf("\nMenuye yonlendirme yapiliyor...");
			    }
             }
            else if(toupper(okay) == 'H')
                    printf("\nIslem iptal ediliyor...");
            else
                    printf("\nHatali giris yapildi...\nMenuye yonlendirme yapiliyor...");
            }
			
	
		else if(toupper(choice) == 'C'){ //dosya adi degistirme
			
			printf("\nDegistirmek istediginiz dosyanin adini giriniz : ");
			scanf("%s",fileName);
			if(file == NULL){ //dosyanin varligi sorgulaniyor
		       perror("Error"); //hata kontrolu menuye yonlendirme yapýlýyor
		       printf("\nMenuye yonlendirme yapiliyor...");}
		    else{
				printf("\nDosyanin yeni adini giriniz : ");
				scanf("%s",fileName2);
				change = rename(fileName,fileName2); //dosya ismini rename ile degistiriyoruz
				if (change == 0) { //0 a eþitse basarili bir sekilde degiþtirilmistir
					printf("Dosya adi basarili bir sekilde degiþtirildi!");
				}
	    		else {
				perror("ERROR"); //hata kontrolu menüye yönlendirme yapýlýyor
	    		printf("\nMenuye yonlendirme yapiliyor... ");
	    	    }
	    		
				}
		}
		else if(toupper(choice) == 'D'){ //dosya kopyalama
		
			printf("\nKopyalanacak dosyanin adini girin:\n");
		    scanf("%s",fileName);
		
		    file = fopen(fileName, "r");
		
		    if(!access(fileName,F_OK)==0){ //dosyanin varligi kontrol edilir.
		       perror("ERROR");
		       printf("\nMenuye yonlendirme yapiliyor...");
		   }
			else{
				printf("Hedef dosyanin adini yazin\n");
			    scanf("%s",fileName2);
				
				file2 = fopen(fileName2, "a+");
				while ((info = fgetc(file)) != EOF) //file'daki bilgiler file2'ye aktariliyor.
				    fputc(info, file2);
				
				printf("Dosya basariyla kopyalandi.\n");
			}
		
		    fclose(file);
		    fclose(file2);
		    
		}
		else if(toupper(choice) == 'E'){ //dosyanin sonuna metin ekleme
			printf("\nBaska dizine tasimak istediginiz dosyanin adini giriniz : ");
			scanf("%s",fileName);
			file = fopen(fileName, "r");
			
			if(!access(fileName,F_OK)==0){ //dosyanin varligi kontrol edilir.
		       perror("ERROR");
		       printf("\nMenuye yonlendirme yapiliyor...");
		    }
			else{
				printf("\nTasimak istediginiz dizini dosya adiyla birlikte giriniz : ");
			    scanf("%s",fileName2); //dosyanin tasinacagi dizini kullanicidan aliyoruz
				
			    file3 = fopen("gecicidosya.txt", "w"); //aktarma islemi icin gecici dosya aciyoruz
			    while ((info2 = fgetc(file)) != EOF) //file'daki bilgiler gecici dosyaya aktariliyor.
				    	fputc(info2, file3);	
				fclose(file);
				remove(fileName); //file kapatilip siliniyor
				fclose(file3);
				
				file3 = fopen("gecicidosya.txt", "r+"); // gecici dosya kapatildiktan sonra file 2 ye aktarým icin tekrar aciyoruz
				file2 = fopen(fileName2, "a"); //file2 a modunda aciliyor
                if(!access(fileName2,F_OK)==0){  //dosya olusturma hata kontrolu
			        perror("ERROR");
				    printf("Dosya olusturulamadi!\nMenuye yonlendirme yapiliyor...");}
				while ((info3 = fgetc(file3)) != EOF) {//gecici dosyadaki bilgiler file2'ye aktarýlýyor.
				    fputc(info3, file2);}
				fclose(file3);
				remove("gecicidosya.txt"); //gecici dosya aktarma yapildiktan sonra siliniyor
				fclose(file2);
                printf("\nDosya tasima islemi basariyla gerceklestirildi...");
				}}
			
		else if(toupper(choice) == 'F'){ //dosyanin sonuna metin ekleme
			
			printf("\nSonuna ekleme yapilacak dosyanin adini giriniz:\n");
		    scanf("%s",fileName);
			
			file= fopen(fileName, "r"); //dosya varligi kontrolu icin okuma modunda dosyayi  aciyoruz
			
		    if(!access(fileName,F_OK)==0){ //dosyanin varligi kontrolu
		       perror("ERROR"); 
		       printf("\nMenuye yonlendirme yapiliyor...");
		    }
			else{
				fclose(file); //dosyayi kapatip sonuna ekleme modunda aciyoruz
				file = fopen(fileName, "a");
				printf("\nDosyaya eklenecek metni giriniz:\n");
		    	fscanf(stdin," %499[^\n]", dizgi);
		    	fputs(dizgi,file); //girdigimiz metni fputs ile dosyaya yazdiriyoruz
			    printf("Dosyaya basariyla ekleme yapildi.\n");
			}
			fclose(file);
		}
		else if(toupper(choice) == 'G') //belirli bir konuma text ekleme
		{ 
			printf("\nDosyanin adini girin: ");
			scanf("%100s",f);
			
			if (access(f, F_OK)!=-1) // eger dosya varsa
			{
				if(access(f,W_OK)!=-1)// eger dosyanin yazma izni varsa
        		{
            		file=fopen(f, "r+");
            		file2=fopen("f2.txt", "w+");

            		printf("\n\nTexte eklemek istediginizi yaziniz: \n");
            		scanf(" %100[^\n]",s);

            		printf("Hangi satira eklemek istiyorsunuz: ");
            		scanf("%d", &x);
            		x--;
            		while((z=fgetc(file))!=EOF)//file, file2'ye kopyalaniyor.
            		{
                		fputc(z,file2);
                		if(z == '\n' && ++l == x){
                    		offset = ftell ( file);//dosya icindeki konumu kaydedilir.
                    		while ( ( z = fgetc ( file)) != '\n' && z != EOF) {
                        		linelength++;//satirdaki karakterler sayiliyor.
                    		}
                    		fseek ( file, offset, SEEK_SET);//satýr baþýna dönülür.
                    		//metnin nereden ekleneceginin index'i alýnýr
                    		do {
                        		printf("\nsatirin kacinci indexinden itibaren eklensin(%d'den az olmali): \n", linelength);
                        		if ( ( scanf("%d", &index)) != 1) { 
                            		scanf ( "%*[^\n]");//input int deðil, buffer'ý temizle
                            		index = linelength;
                       		 	}
                    		} while ( index >= linelength || index <= 0); 

                    		while (index) { //file'dan karakterleri okuyup file2'ye tek tek yazar
                    		//istenen index'ten baslayarak
                        		z = fgetc (file);
                        		fputc(z,file2);
                        		index--;
                    	}
                   		fprintf(file2, "%s ", s);//eklenen text file2'ye ekleniyor.
                	}
            	}
            	printf("\nBasariyla eklendi\nMenuye yonlendiriliyor..");
            	fclose(file);
            	fclose(file2); 
				
				//file2'ye eklenenlerle birlikte yeni text dosyasi file'a eklenir.
				//file2 yani f2.txt dosyasý bu islemden sonra silinir.
				file=fopen(f, "w+");
            	file2=fopen("f2.txt", "r");
            	while((y=fgetc(file2))!=EOF){
                    	fputc(y,file);
            	}
            	fclose(file2);
            	fclose(file);
            	remove("f2.txt");		
				}
				else
            		printf("\n%s Text dosyasýnýn yazma izni yok! Menüye yönlendiriliyor..", f);
       		}else
        		printf("Böyle bir dosya yok! Menüye yönlendiriliyor..\n");
		}
		else if(toupper(choice) == 'K'){ //text dosyasýndaki tum texti silme.
			printf("\nIcerigi silinecek dosyanin adini giriniz:\n");
		    scanf("%s",fileName);
		    file = fopen(fileName, "r"); //okuma modunda dosyayi aciyoruz
		
		    if (file == NULL){
		       perror("ERROR"); //hata kontrolu
		       printf("Icerigi silinecek dosya bulunamadi!\nMenuye yonlendirme yapiliyor...");
		   }
			else{
                fclose(file); //dosya kapatiliyor
			    file = fopen(fileName, "w"); // w modunda icerigi bos olarak aciliyor
			    printf("Dosya icerigi basariyla silindi.\nMenuye yonlendirme yapiliyor...");}
		
		    fclose(file);	//dosyayi kapatiyoruz
		}
		
		else if(toupper(choice) == 'J'){ //text dosyasinin icerigini gosterme
			
			printf("\nDosyanin adini girin: ");
			scanf("%s",fileName);
			
			if(access(fileName,F_OK)==0){ //dosya varligi kontrolu
			 	printf("\nKacinci satira kadar okumak istiyorsunuz: ");
            	scanf("%d", &linenumber);
			
				file=fopen(fileName, "r+");
            		
            	while((c = fgetc(file)) != EOF) //satir okunuyor.
            	{
            		putchar(c);
            		if(c == '\n' && ++linenumber == line)
            			printf("\nDosya basariyla okundu.\n Menuye yonlendiriliyor..");
				}
				fclose(file);
            }
            else
            	printf("Bu dosya mevcut degil.\nMenuye yonlendiriliyor..");
      }
		else if(toupper(choice) == 'H'){ //Komutlar hakkinda bilgi verilir.
			
			printf("\nKomutlar hakkinda bilgi almak icin komut_adi/h giriniz.\n");
			printf("KOMUTLAR:\nA\tB\tC\tD\nE\tF\tG\tI\nJ\tH\tQ");
			printf("\nHangi komut hakkinda bilgi almak istiyorsunuz: ");
			scanf("%s",helpp);
			printf("%s",helpp);
			
			//buyuk harf ve kucuk harf ayný komutu calistirdigindan bu sekilde olusturuldu
			if(strcmp(helpp,"A/h")==0  || strcmp(helpp,"a/h")==0)
				printf("\nBu komut yeni bir dosya olusturmanizi saglar");
			else if(strcmp(helpp,"B/h")==0 || strcmp(helpp,"b/h")==0)
				printf("\nBu komut mevcut dosyayi silmemimizi saglar");
			else if(strcmp(helpp,"C/h")==0 || strcmp(helpp,"c/h")==0)
				printf("\nBu komut mevcut bir dosyayi yeniden adlandirmamizi saglar");
			else if(strcmp(helpp,"D/h")==0 || strcmp(helpp,"d/h")==0)
				printf("\nBu komut Dosya kopyalamamizi saglar");
			else if(strcmp(helpp,"E/h")==0 || strcmp(helpp,"e/h")==0)
				printf("\nBu komut dosyayi bir klasorden digerine tasimamizi saglar");
			else if(strcmp(helpp,"F/h")==0 || strcmp(helpp,"f/h")==0)
				printf("\nBu komut dosyanin sonuna metin eklememizi saglar.");
			else if(strcmp(helpp,"G/h")==0 || strcmp(helpp,"g/h")==0)
				printf("\nBu komut dosya icinde belirli bir konuma metin eklememizi saglar");
			else if(strcmp(helpp,"K/h")==0 || strcmp(helpp,"k/h")==0)
				printf("\nBu komut dosyada bulunan tüm metni silmemizi saglar");
			else if(strcmp(helpp,"J/h")==0 || strcmp(helpp,"j/h")==0)
				printf("\nBu komut dosyayi belirli bir yere kadar okumamizi saglar");
			else if(strcmp(helpp,"H/h")==0 || strcmp(helpp,"h/h")==0)
				printf("\nBu komut dosya yöneticisinin komutlarý hakkýnda kullanýcýye bilgi verir");
			else if(strcmp(helpp,"Q/h")==0 || strcmp(helpp,"q/h")==0)
				printf("\nBu komut dosya yöneticisini kapatmamizi saglar.");
			else
				printf("\nYanlis secim yapildi menuye yonlendirme yapiliyor... ");	
		}
		else{
			printf("\nYanlis secim yapildi menuye yonlendirme yapiliyor... ");
		}
		
	}while(toupper(choice) != 'Q'); // Q girilmedikce programimiz devam eder
	printf("\n**** Program sonlandiriliyor ****");
	return 0;
}
