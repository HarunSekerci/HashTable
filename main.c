#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	int musteri_no;
	char ad[20];
	char soyad[20];
	
}Musteri;
Musteri *veri_liste[10];
Musteri *buffer[10];//Dosyadan okunacak degerlerin gecici bir diziye atamak için oluşturduğum dizi
int hash_tablo[10][2];

void cleaner(){//Veri listesine null ve hash tablosuna -1 atanması
	int i=0;
	while(i<10){
		veri_liste[i]=NULL;
		hash_tablo[i][0]=-1;
		hash_tablo[i][1]=-1;
		i++;
	}
}

FILE *fp;
int constant=0;//Listemdeki toplam veri sayısını tuttuğum sabit.
int constant2=0;//Listede veri varsa   sayısını tuttuğum sabit.

int sorting(){//Ekleme fonksiyonu
	
	//constant++;
	int index,x,y,d;
	printf("%d\n",constant);
	buffer[constant]=(Musteri*)malloc(sizeof(Musteri));//Eklenecek veri için önce yer açılması
	printf("Eklemek istediginiz kisinin numarasini giriniz:\n");
	scanf("%d",&buffer[constant]->musteri_no);//Eklenecek verinin once buffer a atanması
	printf("Eklemek istediginiz kisinin adini giriniz:\n");
	scanf("%s",buffer[constant]->ad);
	printf("Eklemek istediginiz kisinin soyadini giriniz:\n");
	scanf("%s",buffer[constant]->soyad);
	constant++;
	//printf("constant:%d\n",constant);
	if(constant<=10){//Listenin dolu olup olmadığının kontrolü
	while(constant2<constant){//Önceki eklenenden en son gelen değer kadar çalışan döngüm.
		index=(buffer[constant2]->musteri_no%10);//Bufferda okunan degerinin modunun alınıp index e atanması
		//printf("%d",i+1);
		if(hash_tablo[index][0]==-1){//hash tabloda anahtar kısmın bos olup olmadıgının kontrolü
			//printf("Debugggg\n\n");
			hash_tablo[index][0]=buffer[constant2]->musteri_no;//hash_tablosuna numara bılgısının atanması
			veri_liste[index]=(Musteri*)malloc(sizeof(Musteri));//Veri listesi için yer açılması
			veri_liste[index]->musteri_no=buffer[constant2]->musteri_no;
			//veri_liste[index]->ad=buffer[constant2]->ad;
			//veri_liste[index]->soyad=buffer[constant2]->soyad;//Bu atamalar hata verdigi için alttaki fonksiyonu kullandım.
			memcpy(veri_liste[index]->ad,buffer[constant2]->ad,sizeof(buffer[constant2]->ad));//hedef kaynak boyut seklınde calısan kopyalama yapan memcpy fonksıyonu kullandım.
			memcpy(veri_liste[index]->soyad,buffer[constant2]->soyad,sizeof(buffer[constant2]->soyad));
			//k++;
			//printf("%d",k);
		}
		else{//Anahtar kısım dolu ise çalısacak kısım
			if(hash_tablo[index][1]==-1){//Anahtar kısım dolu ve sonraki kismı boş ise çalışacak olan kısım.
				for(x=0;x<constant;x++){//Veri listesini baştan sona tarayan döngü
					if(veri_liste[x]==NULL){//Veri listeside ilk boş olan kısmın kontrolü
						veri_liste[x]=(Musteri*)malloc(sizeof(Musteri));
						veri_liste[x]->musteri_no=buffer[constant2]->musteri_no;
						memcpy(veri_liste[x]->ad,buffer[constant2]->ad,sizeof(buffer[constant2]->ad));
						memcpy(veri_liste[x]->soyad,buffer[constant2]->soyad,sizeof(buffer[constant2]->soyad));
						hash_tablo[index][1]=x;// anahtar kısmın sonrakine indis ataması
						hash_tablo[x][0]=buffer[constant2]->musteri_no;
						break;
					}
				}
				//k++;
			}
			else{//Anahtar kısmın sonraki kismida dolu ise çalışacak olan son koşul
				for(y=0;y<10;y++){//Hash tablonun baştan sona taranması
					if(hash_tablo[y][0]==-1){//Hash tablonun boş bulunan kısmına ekleme işlemi
						hash_tablo[y][0]=buffer[constant2]->musteri_no;
							for(d=0;d<constant;d++){//Veri listenin baştan sona taranması
								if(veri_liste[d]==NULL){//Veri listenin boş bulunan kısmına ekleme işlemi
									veri_liste[d]=(Musteri*)malloc(sizeof(Musteri));
									veri_liste[d]->musteri_no=buffer[constant2]->musteri_no;
									memcpy(veri_liste[d]->ad,buffer[constant2]->ad,sizeof(buffer[constant2]->ad));
									memcpy(veri_liste[d]->soyad,buffer[constant2]->soyad,sizeof(buffer[constant2]->soyad));
									hash_tablo[x][1]=d;//hash tablosuna indis ataması
									break;
					}
				}
					
					break;	
					}
				}
			}
		}
		constant2++;
	}
}
else {
	printf("Listede yer yok.\n");
}
	//return constant;
}
int seeking(){//Arama fonksiyonu
	int index,count,i=0;
	printf("Aramak istediginiz kisinin numarasini giriniz:\n");
	scanf("%d",&count);
	index=count%10;//Aranılan sayının anahtar kısmının atanması
	while(i<constant){//Hash tablonun bastan sona taranması
	if(hash_tablo[index][0]==count){//anahtar kısmın hash tablosunda tespıt edılmesı
		printf("%d %s %s\n",veri_liste[index]->musteri_no,veri_liste[index]->ad,veri_liste[index]->soyad);
		printf("%d.adimda bulundu.\n",i+1);
		return i;
	}
	else{
		index=hash_tablo[index][1];//anahtar kısım ilk seferde bulunamaz ise index kısmın sonraki indis ile değiştirilmesi
	}
	i++;
	}
}
void hashPrint(){//Hash tablosunun yazdırılması
	int i;
		for(i=0;i<10;i++){
		printf("hash_tablo[%d][0]:%d | hash_tablo[%d][1]:%d\n",i,hash_tablo[i][0],i,hash_tablo[i][1]);
	}
}
void dataPrint(){//Veri listesinin yazdırılması
	int i,y=0;
	for(i=0;y<constant;i++){//Veri listesinin bos olan veya sılınen kısımların yazdırılırken programın sonlanmasısonucu bu sekılde bır for kullandım.
		if(veri_liste[i]!=NULL){
				printf("%d %s %s\n",veri_liste[i]->musteri_no,veri_liste[i]->ad,veri_liste[i]->soyad);
				y++;//veri listesinin degeri basıldıkca artan degısken
	}
	else{
		
	}
}
}
void dataClear(){//Sİlme fonksiyonu
	int deleteCount,temp,i=0,index;
	printf("Silmek istediginiz kisinin numarasini giriniz:\n");
	scanf("%d",&deleteCount);
	index=deleteCount%10;//Silenecek degerın anahtar kısmının bulunması
	//printf("Debugggggg");
	while(i<constant){//veri listesindeki toplam deger kadar calısan döngü
		//printf("Debuggg");
		if(hash_tablo[index][0]==deleteCount && hash_tablo[index][1]==-1){//Silenecek degerın sonrasında bır deger tutmaması durumunda calısan kısım.
			hash_tablo[index][0]=-1;//hash tablosundan sılme ıslemı
			//veri_liste[index]=NULL;
			veri_liste[index]=NULL;//veri listesinden silme islemi
			constant--;//dizideki toplam eleman sayısını tutan degıskenın degerının azaltılması
			printf("Silme basarili\n");
			break;
		}
		else{
			if(hash_tablo[index][0]==deleteCount && hash_tablo[index][1]!=-1){//Silenecek degerın sonrasında bır deger var ise calısan kısım
			temp=hash_tablo[index][1];//sonraki indisin gecici bir degiskene atanması
			hash_tablo[index][0]=-1;// hash tablosundan sılme ıslemı
			hash_tablo[index][1]=-1;
			veri_liste[index]=NULL;
			hash_tablo[index][1]=hash_tablo[temp][1];//silinen elemanın sonrakinin yerine sonraki elemanın sonrakinin indisinin  atanması
			hash_tablo[index][0]=hash_tablo[temp][0];// silinen elemanın yerıne sonraki elemaının atanması
			hash_tablo[temp][0]=-1;//sonraki kısmın silinmesi
			hash_tablo[temp][1]=-1;
			constant--;
			printf("Silme basarili\n");
			break;
		}
		else{//elemanın ılk seferde bulunamaması halinde anahtar kısmın sonraki indisle yer değiştirmesi
			index=hash_tablo[index][1];
			//printf("\ndebug\n");
		}
		}
		i++;
	}
	if(i<=10){//yukardaki işlemlerin yapılıp yapılmadıgının kontrolü
		printf("Listede olmayan numara girisi yapildi.\n");
	}
	
	
}
void Steps(){//Ortalama adım sayisini bulan fonksiyon
	int i,z,k=0,total=0;
	int toplam[constant];//Toplam dizisinın her bir indisi veri listesindeki anahtar kısımdaki degerlerin kaç adımda bulundugunu tutacak.
	memset(toplam,0,sizeof(toplam));//toplam dizisinin icinin sıfırlanması
	for(i=0;i<10;i++){
		if(hash_tablo[i][0]!=-1){//hash tablosunda deger var mı kontrolü
			toplam[hash_tablo[i][0]%10]++;//hash tablosundaki verinin anahtar kısmının toplam dizisindeki o indisindeki sayinin varsa artırılması
		}
	}
	while(k<constant){
		z=toplam[k];//toplam dızınsındekı her adım sayısının toplanması
		total+=(z*(z+1))/2;
		k++;
	}
	//(total/y);
	printf("Toplam adim sayisi:%d\n",total);
	printf("Listedeki toplam eleman sayisi:%d\n",constant);
	printf("Ortalama adim sayisi:%f\n",(double)total/constant);
}
int hash(){//dosyadan okunan degerlerın ılk ataması yapılması
//Ekleme fonksiyonumla birebir aynı mantıkla çalışıyor.
	int index,x,y,d;
	while(constant2<constant){
		index=(buffer[constant2]->musteri_no%10);
		//printf("%d",i+1);
		if(hash_tablo[index][0]==-1){
			//printf("Debug2\n");
			hash_tablo[index][0]=buffer[constant2]->musteri_no;//hash atama
			veri_liste[index]=(Musteri*)malloc(sizeof(Musteri));
			veri_liste[index]->musteri_no=buffer[constant2]->musteri_no;
			memcpy(veri_liste[index]->ad,buffer[constant2]->ad,sizeof(buffer[constant2]->ad));
			memcpy(veri_liste[index]->soyad,buffer[constant2]->soyad,sizeof(buffer[constant2]->soyad));
		}
		else{
			if(hash_tablo[index][1]==-1){
				for(x=0;x<constant;x++){
					if(veri_liste[x]==NULL){
						veri_liste[x]=(Musteri*)malloc(sizeof(Musteri));
						veri_liste[x]->musteri_no=buffer[constant2]->musteri_no;
						memcpy(veri_liste[x]->ad,buffer[constant2]->ad,sizeof(buffer[constant2]->ad));
						memcpy(veri_liste[x]->soyad,buffer[constant2]->soyad,sizeof(buffer[constant2]->soyad));
						hash_tablo[index][1]=x;// hash tablosunun sonraki kismina atama
						hash_tablo[x][0]=buffer[constant2]->musteri_no;
						break;
					}
				}
			}
			else{
				for(y=0;y<10;y++){
					if(hash_tablo[y][0]==-1){
						hash_tablo[y][0]=buffer[constant2]->musteri_no;
							for(d=0;d<constant;d++){
								if(veri_liste[d]==NULL){
									veri_liste[d]=(Musteri*)malloc(sizeof(Musteri));
									veri_liste[d]->musteri_no=buffer[constant2]->musteri_no;
									memcpy(veri_liste[d]->ad,buffer[constant2]->ad,sizeof(buffer[constant2]->ad));
									memcpy(veri_liste[d]->soyad,buffer[constant2]->soyad,sizeof(buffer[constant2]->soyad));
									hash_tablo[x][1]=d;
									break;
					}
				}
					
					break;	
					}
				}
			}
		}
		constant2++;
	}
}
int main(){
	fp=fopen("veri.txt","r");
	int secim=0;
	cleaner();//veri listesine null ve hash tablosuna -1 atanması

		while(!feof(fp)){//okunan dosyanın sonuna kadar giden döngü
		buffer[constant]=(Musteri*)malloc(sizeof(Musteri));//buffer da yer açılması
		fscanf(fp,"%d %s %s",&buffer[constant]->musteri_no,buffer[constant]->ad,buffer[constant]->soyad);//dosyada var olan verilerin buffer atanması
		constant++;
	}
	hash();//dosyadan okunan degerlerın hash tablosuna atılması
	//constant=constant-1;
	while(true){//Menü
		printf("Ekleme --> 1\nArama--> 2\nSilme --> 3\nHash Tablosu --> 4\nVeri listesi --> 5\nOrtalama adim sayisi --> 6\nCikis --> 7\n");
		scanf("%d",&secim);
		system("CLS");
		switch(secim){
			case 1:
				//printf("\n%d\n",constant);
				sorting();
				break;
			case 2:
				seeking();
				break;
			case 3:
				dataClear();
				break;
			case 4:
				hashPrint();
				break;
			case 5:
				dataPrint();
				break;
			case 6:
				Steps();
				break;
			case 7:
				exit(1);
				break;
		}
	}
	//z=sorting(i);
	//printf("\nz=%d\n",z);
	//Steps(z);
	//printf("\n");
	//seeking();
	//printf("%d",seeking());
	//hashPrint();
	//printf("\nDebug\n\n");
	//dataPrint();
	//printf("\nDebug");
	//dataClear();
	//dataPrint();
	//hashPrint();
	//Steps(z);
	fclose(fp);
	return 0;
}
