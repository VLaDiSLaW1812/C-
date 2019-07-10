// Course work.cpp: определ€ет точку входа дл€ консольного приложени€.
//
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include <time.h>
using namespace std;

struct cars
{ int  Number;
  char  Brand [30];
  int  Run ;
  char  Rent [30];
  char  Signaling [30];
  float  Price;
};

//1
void add_record(char* name)
{cars z;
FILE* f;
f=fopen(name,"ab");
if (f==NULL)  {cout<<"Cannot create file to add record\n"; return;}
scanf("%i %s %i %s %s %g",&z.Number,z.Brand,&z.Run,z.Rent,z.Signaling,&z.Price);
fwrite (&z,sizeof(cars),1,f);
fclose(f);
}

//2
void view_file(char*name)  
{cars z;
FILE* f;
f=fopen(name,"rb");
if (f==NULL) {cout<<"Cannot open file to view\n";return;}
cout<<"\nView file"<<endl;
cout<<"Number\tBrand\tRun\tRent\tSignaling\tPrice\n"<<endl;
while(fread(&z,sizeof(cars),1,f))
{printf("%i\t%s\t%i\t%s\t%s\t%6.2f\n",z.Number,z.Brand,z.Run,z.Rent,z.Signaling,z.Price);}
fclose(f);
}

//3
int number_of_records2(char*name)
{ FILE* f;
int n=0; cars z;
f=fopen(name, "rb");
if(f==NULL) {cout<<"Cannot open file\n"; return 0;}
while(fread(&z,sizeof(z),1,f))
  n++;
return n;
}

//4
void create_array(cars * a, int kol, char*name)
{ int i=0; //»ндекс массива
cars z;
FILE* f;
f=fopen(name, "rb");
if(f==NULL) {cout<<"Cannot open file to veiw\n"; return ;}
//—читывать по очереди все записи, записывать их в очередной элемент массива и 
//увеличивать индекс массива на 1
while(fread(&z,sizeof(cars), 1, f))
{
	a[i]=z; i++; }
  fclose(f);

}

//5
//—ортировка массива по убыванию цены
void sort_array(cars*a, int kol)
{ int i; cars x; bool f;
//÷икл пока массив не отсортирован. ѕризнаком того, что массив уже отсортирован будет 
//значение переменной f, равное 0, после очередного прохода по массиву
do{
    f=0;
//¬ каждом проходе по массиву сравниваютс€ два соседних элемента. ќни мен€ютс€ местами, 
//если сто€т в неправильном пор€дке
	for (i=0; i<kol-1; i++)
	    if (a[i].Price<a[i+1].Price)
		{ 
		x=a[i]; a[i]=a[i+1]; a[i+1]=x;
		  f=1;
	}
  }while(f);
}

//6
//¬ывод динамического массива на экран
void view_array(cars*a, int kol)
{
cout<<"Number\tBrand\tRun\tRent\tSignaling\tPrice\n"<<endl;
for (int i=0; i<kol; i++)
printf ("%i\t%s\t%i\t%s\t%s\t%6.2f\n",a[i].Number,a[i].Brand,a[i].Run,a[i].Rent,a[i].Signaling,a[i].Price);
}

//7

void array_to_file(cars*a, int kol, char*name)
{ FILE* f;
f=fopen(name, "wb");
if(f==NULL) {cout<<"Cannot create file to add record\n"; return;}
for (int i=0; i<kol; i++)
{
 fwrite (&a[i],sizeof(cars), 1, f);
   }
fclose(f);
}

//8
void Without_Signaling(char* name)
{ cars z; 
FILE* f;
f=fopen(name, "rb");
if(f==NULL) {cout<<"Cannot open file to veiw\n"; return;}
cout<<"\nSelect records"<<endl;
cout<<"Number\tBrand\tRun\tRent\tSignaling\tPrice\n"<<endl;
while(fread(&z,sizeof(cars), 1,f))
    if (strcmp(z.Signaling,"No")==0 && strcmp(z.Brand,"Ford")==0){
printf("%i\t%s\t%i\t%s\t%s\t %6.2f\n",z.Number,z.Brand,z.Run,z.Rent,z.Signaling,z.Price);}
fclose(f);
}

//9
void create_text_file(char* name, char* tname)
{ FILE* f, * ft; 
cars z;
time_t t, t1;
struct tm tmstr;
int seconds, yearinseconds=365.25*24*60*60; 
t = time(NULL); 
f=fopen(name, "rb");
if(f==NULL) {cout<<"Cannot open file\n"; return;}
ft=fopen(tname, "wt");
if(ft==NULL) {cout<<"Cannot create text file\n"; return;}
while(fread(&z,sizeof(cars), 1, f))
{    
  sscanf(z.Rent,"%d.%d.%d", &tmstr.tm_mday, &tmstr.tm_mon, &tmstr.tm_year);
  tmstr.tm_mon-=1; tmstr.tm_year-=1900; tmstr.tm_hour=0;tmstr.tm_min=0;tmstr.tm_sec=0;
  t1=mktime ( &tmstr ); seconds=difftime(t,t1);
  if (difftime(t, t1)<yearinseconds)
     fprintf(ft,"%i\t%s\t%i\t%s\t%s\t%g\n",z.Number,z.Brand,z.Run,z.Rent,z.Signaling,z.Price);
}
fclose(f); fclose(ft); 
}

//10
void view_text_file(char*tname)
{ cars z; 
FILE* f;
f=fopen(tname, "rt");
if(f==NULL) {cout<<"Cannot open text file to veiw\n"; return;}
cout<<"\nView text file"<<endl;
cout<<"Number\tBrand\tRun\tRent\tSignaling\tPrice\n"<<endl;
while(!feof(f))	
{ fscanf(f,"%i\t%s\t%i\t%s\t%s\t%f\n",&z.Number,z.Brand,&z.Run,z.Rent,z.Signaling,&z.Price);
  printf("%i\t%s\t%i\t%s\t%s\t%6.2f\n",z.Number,z.Brand,z.Run,z.Rent,z.Signaling,z.Price);
}
fclose(f);
}


//11...
void delete_txt (char *tname, int &kol)
{cars z;
FILE * f;
f = fopen(tname , "rt");
if (f == NULL) {cout<<"Error!\n"; return; }
cars *a=new cars [kol];
int i=0; kol=0;
//while (fscanf (f,"%i\t%s\t%i\t%s\t%s\t%f",&a[i].Number, a[i].Brand, &a[i].Run, a[i].Rent, a[i].Signaling, &a[i].Price)) {
while(!feof(f))	
{fscanf(f,"%i\t%s\t%i\t%s\t%s\t%f\n",&z.Number,z.Brand,&z.Run,z.Rent,z.Signaling,&z.Price);
 a[i]=z; i++; kol++;
}
fclose(f);

 f = fopen(tname, "wt");
if (f == NULL) {cout<<"Error!\n";return;}
for (i = 0; i < kol; i++) 
    if  (a[i].Run>=50000 ) 
        fprintf(f,"%i\t%s\t%i\t%s\t%s\t%g\n",a[i].Number,a[i].Brand,a[i].Run,a[i].Rent,a[i].Signaling,a[i].Price);
fclose(f);
}



//12
void update_txt(char *tname, int kol)

{ cars z;

FILE *f;

f = fopen(tname , "rt");

if ( f == NULL) {

cout <<"Error!/n"; return; }

cars *a = new cars [kol];

int i = 0;


while (!feof(f)) {
fscanf(f,"%i\t%s\t%i\t%s\t%s\t%f\n",&z.Number,z.Brand,&z.Run,z.Rent,z.Signaling,&z.Price);
a[i]=z; i++; kol++;
  }

fclose(f);

f = fopen(tname, "wt");

for( i=0; i < kol; i++) {

if (strcmp(a[i].Signaling, "No" )==0){ 

a[i].Price=a[i].Price-5*(a[i].Price/100);

fprintf(f,"%i\t%s\t%i\t%s\t%s\t%g\n",a[i].Number,a[i].Brand,a[i].Run,a[i].Rent,a[i].Signaling,a[i].Price);
}
}
fclose(f);

}




//13
void insert_record (char*name,int kol)
{cars z;
	FILE *f;
	int r=0;
	
	cout<<"r="<<endl;
	cin>>r;
	if (r <0)
		r=0;
	if (r>kol)
		r=kol;
	kol = number_of_records2(name);	
	cars*a=new cars [kol];
create_array(a,kol,name);
f=fopen(name, "wb");
if(f==NULL) {cout<<"Cannot create file to add record\n"; return;}
for (int i=0; i<r; i++)
  fwrite (&a[i],sizeof(cars), 1, f);

   scanf("%i %s %i %s %s %g",&z.Number,z.Brand,&z.Run,z.Rent,z.Signaling,&z.Price);
   fwrite (&z,sizeof(cars),1,f);

for (int i=r; i<kol; i++)
  fwrite (&a[i],sizeof(cars), 1, f);


	fclose(f);
 
}

int main()
{
FILE * f=NULL, * ft=NULL;		
char* name="kurs.txt"; char* tname="textfile.txt" ;
cout<<"Input information about cars:"<<endl;
cout<<"Number\tBrand\tRun\tRent\tSignaling\tPrice\n "<<endl;

//add_record(name);

view_file(name);

int kol = number_of_records2(name);

cout<<"Number of records in the file: "<<kol<<endl;

cars *a=new cars [kol];

create_array (a,kol,name);

cout<<"Array:"<<endl;

view_array (a,kol);

sort_array (a,kol);

cout<<"\nSorted array:"<<endl;

view_array (a,kol); 

array_to_file(a,kol,name);
 
view_file(name);
 
Without_Signaling(name);
  
create_text_file(name, tname);

view_text_file (tname);
 
delete_txt(tname, kol); 
	  
view_text_file (tname);
	 
update_txt (tname,kol);

view_text_file (tname);

insert_record (name, kol);

view_file(name);

system ("pause");

return 0;
}

