#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* input_fonksiyon(){
    char *fonksiyon = (char*)(malloc(sizeof(char)*200));
    printf("Matematiksel fonksiyon giriniz: ");
    scanf("%s", fonksiyon);
    return fonksiyon;
}

char* inputOperator(){
    int i;
    char *operatorler; 
    operatorler = (char*)malloc(sizeof(char)*200);
    return operatorler;
}

char** inputVeriler(){
    int a;
    char **veriler;
    veriler = (char**)malloc(sizeof(char*)*200);
    for(a=0;a<200;a++){
        veriler[a] = (char*)malloc(sizeof(char)*200);
    }
    return veriler;
}

double xAlma(){
    double x;
    printf("x degerini giriniz: ");
    scanf("%lf", &x);
    return x;
}



void fonksiyonAyir(char* fonksiyonStr, char *operatorlar, char **veriler, int* operatorSayisi, int* veriSayisi) {
    *operatorSayisi = 0;
    *veriSayisi = 0;

    int i = 0, j = 0, k = 0;
    while (fonksiyonStr[i] != '\0') {
        if ((fonksiyonStr[i] >= '0' && fonksiyonStr[i] <= '9') || fonksiyonStr[i] == '.') {
            veriler[k][j++] = fonksiyonStr[i];
        } else if (fonksiyonStr[i] == 'x') {
            if (j != 0) {
                veriler[k][j] = '\0';
                k++;
                (*veriSayisi)++;
                operatorlar[*operatorSayisi] = '*';
                (*operatorSayisi)++;
            }
            veriler[k][0] = 'x';
            veriler[k][1] = '\0';
            k++;
            (*veriSayisi)++;
            j = 0;
        } else if (fonksiyonStr[i] == '+' || fonksiyonStr[i] == '-' || fonksiyonStr[i] == '*' || fonksiyonStr[i] == '/' || fonksiyonStr[i] == '^') {
            if (j != 0) {
                veriler[k][j] = '\0';
                k++;
                (*veriSayisi)++;
                j = 0;
            }
            operatorlar[*operatorSayisi] = fonksiyonStr[i];
            (*operatorSayisi)++;
        }
        i++;
    }
    if (j != 0) {
        veriler[k][j] = '\0';
        k++;
        (*veriSayisi)++;
    }
}

double* cevir(char **veriler, int veriSayisi, double x) {
    double *veriDegerleri = (double*)malloc(sizeof(double) * (veriSayisi + 1));
    for (int i = 0; i <= veriSayisi; i++) {
        if (strchr(veriler[i], 'x') != NULL) {
            double katsayi = 1.0;
            int j = 0;
            if (veriler[i][0] != 'x') {
                sscanf(veriler[i], "%lf", &katsayi);
                while (veriler[i][j] != 'x') j++;
            }
            double us = 1.0;
            if (veriler[i][j + 1] == '^') {
                sscanf(veriler[i] + j + 2, "%lf", &us);
            }
            veriDegerleri[i] = katsayi * pow(x, us);
        } else {
            sscanf(veriler[i], "%lf", &veriDegerleri[i]);
        }
    }
    return veriDegerleri;
}

double hesapla(double *degerler, int veriSayisi, int operatorSayisi, char* operatorler) {
    for (int i = 0; i < operatorSayisi; i++) {
        if (operatorler[i] == '^') {
            degerler[i] = pow(degerler[i], degerler[i + 1]);
            for (int j = i + 1; j < veriSayisi; j++) {
                degerler[j] = degerler[j + 1];
                operatorler[j - 1] = operatorler[j];
            }
            i--;
            operatorSayisi--;
            veriSayisi--;
        }
    }

    for (int i = 0; i < operatorSayisi; i++) {
        if (operatorler[i] == '*') {
            degerler[i] = degerler[i] * degerler[i + 1];
            for (int j = i + 1; j < veriSayisi; j++) {
                degerler[j] = degerler[j + 1];
                operatorler[j - 1] = operatorler[j];
            }
            i--;
            operatorSayisi--;
            veriSayisi--;
        } else if (operatorler[i] == '/') {
            degerler[i] = degerler[i] / degerler[i + 1];
            for (int j = i + 1; j < veriSayisi; j++) {
                degerler[j] = degerler[j + 1];
                operatorler[j - 1] = operatorler[j];
            }
            i--;
            operatorSayisi--;
            veriSayisi--;
        }
    }

    for (int i = 0; i < operatorSayisi; i++) {
        if (operatorler[i] == '+') {
            degerler[i] = degerler[i] + degerler[i + 1];
            for (int j = i + 1; j < veriSayisi; j++) {
                degerler[j] = degerler[j + 1];
                operatorler[j - 1] = operatorler[j];
            }
            i--;
            operatorSayisi--;
            veriSayisi--;
        } else if (operatorler[i] == '-') {
            degerler[i] = degerler[i] - degerler[i + 1];
            for (int j = i + 1; j < veriSayisi; j++) {
                degerler[j] = degerler[j + 1];
                operatorler[j - 1] = operatorler[j];
            }
            i--;
            operatorSayisi--;
            veriSayisi--;
        }
    }

    return degerler[0];
}

//VERİ VE OPERATÖRLER DİZİSİN YAZDIRIR.
void yazdir(char* fonksiyonStr, char *operatorlar, char **veriler, int* operatorSayisi,int* veriSayisi){
    printf("\nOperatorler:\n");
    int i,j;
    for (i = 1; i <= *operatorSayisi; i++) {
        if(operatorlar[i] != '\0'){printf("%c ", operatorlar[i]);}
    }

    printf("\nVeriler:\n");
    for (i = 0; i <= *veriSayisi; i++) {
        for (int j = 0; veriler[i][j] != '\0'; j++) {
            printf("%c", veriler[i][j]);
        }   
        printf("\t");
    }

}

int Menu_Goster(){
    int option;
    printf("1. Bisection yontemi\n2. Regula-Falsi yontemi\n3. Newton-Rapshon yontemi\n4. Matrisin tersi\n5. Gauus Eleminasyon\n6. Gauss Seidal yontemleri\n7. Sayisal Turev\n8. Simpson yontemi\n9. Trapez yontemi\n10. Gregory newton Enterpolasyonu");
    scanf("%d", &option);
    return option;
}

//4 MATRİSİN TERSİ
double** Matris_Alma(int N){
    double **matris;
    int i,j;
    double matris_deger;
    matris = (double**) malloc(N*(sizeof(double*)));
    
    for(i = 0; i < N; i++) {
        matris[i] = (double *)malloc(N* sizeof(double) );
    }
    for (i=0;i< N;i++)
    {
        for(j=0; j<N;j++)
        {
            printf("[%d][%d]\n",i,j);
            scanf("%lf", &matris_deger);
            matris[i][j] = matris_deger;
        }
    }
    
    return matris;

}

//birim matris
double** Birim_matris_alma(int N){
    double **matris;
    int i,j;
    matris = (double**) malloc(N*(sizeof(double*)));
    
    for(i = 0; i < N; i++) {
        matris[i] = (double*)malloc(N* sizeof(double) );
    }
    for (i=0;i< N;i++)
    {
        for(j=0; j<N;j++)
        {   
            if (i==j){
                matris[i][j] = 1;
            }
            else{
                matris[i][j] = 0;
            }
        }
    }
    
    return matris;    
}

double determinant(double **a, int N)
{
    double s = 1, det = 0;
    double **b;
    int i, j, m, n, c;
    b = (double**) malloc(N*(sizeof(double*)));
    for(i = 0; i < N; i++) {
        b[i] = (double*)malloc(N* sizeof(double) );
    }
    if (N == 1){
       return (a[0][0]);
    }
    else{
        det = 0;
        for (c = 0; c < N; c++){
            m = 0;
            n = 0;
            for (i = 0;i < N; i++){
                for (j = 0 ;j < N; j++){
                    b[i][j] = 0;
                    if (i != 0 && j != c){
                        b[m][n] = a[i][j];
                        if (n < (N - 2))
                        n++;
                        else{n = 0;m++;}
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, N - 1));
            s = -1 * s;
        }
    }
    
    return (det);
}



void transpoz(double **num, double **fac, int N)
{
    int i, j;
    double **b, **inverse, d;
    b = (double**) malloc(N*(sizeof(double*)));
    inverse = (double**) malloc(N*(sizeof(double*)));
    for(i = 0; i < N; i++) {
        b[i] = (double*)malloc(N* sizeof(double) );
        inverse[i] = (double*)malloc(N* sizeof(double) );
    }

    for (i = 0;i < N; i++)
        {
        for (j = 0;j < N; j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, N);
    for (i = 0;i < N; i++)
    {
        for (j = 0;j < N; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
    printf("\n\n\nmatrisin tersi : \n");
 
    for (i = 0;i < N; i++)
    {
        for (j = 0;j < N; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
    printf("\n");
    }
}

void kofaktor(double **num, int N){
    
    int p, q, m, n, i, j;
    double **b, **fac;
    b = (double**) malloc(N*(sizeof(double*)));
    fac = (double**) malloc(N*(sizeof(double*)));
    for(i = 0; i < N; i++) {
        b[i] = (double*)malloc(N* sizeof(double) );
        fac[i] = (double*)malloc(N* sizeof(double) );
    }

    for (q = 0;q < N; q++){
        for (p = 0;p < N; p++){
            m = 0;
            n = 0;
            for (i = 0;i < N; i++){
                for (j = 0;j < N; j++){
                    if (i != q && j != p){
                        b[m][n] = num[i][j];
                        if (n < (N - 2))
                            n++;
                        else{n = 0;m++;}
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, N - 1);
        }
    }
    transpoz(num, fac, N);
}




double** Matris_yazdirma(double **n,int N){
    int i,j;
    for ( i = 0; i <N; i++)
    {
        for ( j = 0; j < N; j++)
        {
            printf("%lf\t",n[i][j]);
        }
        printf("\n");
    }
    
}
//GAUSS ELEMİNASYON
double* B_matrisi_alma(int N){
    double *B,sayi;
    int i;
    B = (double*) malloc(sizeof(double)*N);

    for(i=0;i<N;i++){
        printf("B[%d] icin deger girin\n", i);
        scanf("%lf", &sayi);
        B[i] = sayi;
    }
    
    return B;
}



void Gauss_Eleminasyon(double **A,double *B,int N){
    int i,j,k;
    double **sonuc, temp, *x,sum;

    x = (double*)malloc(N*sizeof(double));


    for(i=0;i<N;i++){
        temp = A[i][i];
        for(j=0;j<N;j++){
            A[i][j] = A[i][j] / temp;
        }
        B[i] = B[i] / temp;

        for(j=i+1;j<N;j++){
            temp = A[j][i];
            if(temp == 0){
                printf("Kosegende 0 olamaz! Mathematical Error!");
                return;
            }
            for(k=0;k<N;k++){ 
                A[j][k] = A[j][k] - A[i][k]*temp;
            }
            B[j] = B[j] - B[i]*temp;
        }

    }
    for (i=0;i<N;i++){
        printf("[");
        for(j=0;j<N;j++){
            printf("%lf ", A[i][j]);
        }
        printf("]");
        printf(" [x%d] " , i);
        printf(" [%lf] ", B[i]);
        printf("\n");
    }
    
    x[N-1] = B[N-1] / A[N-1][N-1];

    for(i=N-2; i>-1; i--)
    {
        sum=0;
        for(j=i+1; j<N; j++)
        {
            sum=sum+A[i][j]*x[j];
        }
        x[i]=(B[i]-sum)/A[i][i];
    }

    printf("\nThe solution is: \n");
    for(i=0; i<N; i++)
    {
        printf("\nx%d=%lf\t",i,x[i]); 
    }
}

// GAUSS SEİDAL
void Gauss_Seidel(int N, double **A, double *B, double *x, double epsilon) {
    double *x_old;
    double sum;
    int iter = 0;
    int kontrol;
    double error[N];
    x_old = (double*)malloc(sizeof(double)*N);


    do {
        kontrol = 1; 
        for (int i = 0; i < N; i++) {
            x_old[i] = x[i];

        }

        printf("Iterasyon %d:\n", iter + 1);
        for (int i = 0; i < N; i++) {
            sum = B[i];
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    sum -= A[i][j] * x[j];
                }
            }
            x[i] = sum / A[i][i];
            if ((x[i] - x_old[i]) < 0) {error[i] = x_old[i] - x[i];}
            if ((x[i] - x_old[i]) > 0) {error[i] = -x_old[i] + x[i];}
            printf("x[%d] = %lf, hata = %lf\n", i, x[i], error[i]);
            if ((x[i] - x_old[i]) < 0) {if(-(x[i]- x_old[i])>=epsilon){kontrol = 0;}}
            if ((x[i] - x_old[i]) > 0) {if((x[i]- x_old[i])>=epsilon){kontrol = 0;}}
        }

        iter++;
    } while (!kontrol);

    printf("Gauss-Seidel yontemi %d iterasyonda sonuclandi.\n", iter);
    printf("Result: (x):\n");
    for (int i = 0; i < N; i++) {
        printf("%lf\n", x[i]);
    }
}



int main(){
    double **A, **I, *B;
    int N,i,j,choice,kontrol = 1;
    char *fonksiyonStr; // Kullanıcıdan alınacak fonksiyon stringi
    char *operatorler; // Operatörleri tutacak karakter dizisi
    char **veriler; // Verileri tutacak iki boyutlu karakter dizisi
    int operatorSayisi, veriSayisi;
    int maxIteration;
    double xValues[50];
    double fxValues[50][50];
    int sayac = 0;
    kontrol = 1;
    int k;
    double x,start,end,mid,fmid,fstart,fend,*degerler,next,fnext,tstart,ftstart,turev,h,prev,fprev,toplam,toplam2,Alan,sonuc,carpim,epsilon;
    double *matris_X;
    switch (Menu_Goster())
    {
    case 0:
        break;
    
    case 1:
        N = 1;
        fonksiyonStr = input_fonksiyon();
        operatorler = inputOperator();
        veriler = inputVeriler();
        //yazdir(fonksiyonStr, operatorler,veriler, &operatorSayisi, &veriSayisi);
        printf("epsilon degeri girin:");
        scanf("%lf", &x);
        printf("baslangic degerini girin: ");
        scanf("%lf", &start);
        printf("bitis degerini girin: ");
        scanf("%lf", &end);
        printf("maksimum iterasyon sayisini girin: ");
        scanf("%d", &maxIteration);
        printf("durma kosulu secin:\n1- f(x) <= epsilon\n2- (end-start)/2^n <= epsilon");
        scanf("%d", &choice);
        for(i=0;i<maxIteration && kontrol == 1;i++){
            mid = (start + end)/2;
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fend = hesapla(cevir(veriler,veriSayisi,end),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fmid = hesapla(cevir(veriler,veriSayisi,mid),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
            printf("start: %lf\n", start);
            printf("end: %lf\n", end);
            printf("mid: %lf\n", mid);
            printf("f(start): %lf\n", fstart);
            printf("f(end): %lf\n", fend);
            printf("f(mid): %lf\n", fmid);
            printf("iterasyon: %d\n\n", N);
            
            switch (choice)
            {
            case 1:
                if(fmid < 0){if(-fmid <= x){;kontrol = 0;}}
                if(fmid > 0){if(fmid <= x){kontrol = 0;}}
                printf("result: %lf\n",mid);
                break;
        
            case 2:
                if(end-start<0){if(-(end-start)/ pow(2,N) <= x){kontrol = 0;}}
                if(end-start>0){if((end-start)/ pow(2,N) <= x){kontrol = 0;}}
                printf("result: %lf\n",mid);
                break;
        
            }
            if(fmid*fend <= 0){
                start = mid;
            }
            else if(fmid*fstart <= 0){
                end = mid;
            }
            else{
                printf("girilen degeler arasinda kok bulunamaz f(start) ve f(end) degerlerinin isaretleri ayni");
                break;
            }
            N++;
        }

        
        break;
    
    case 2:
        N=1;
        fonksiyonStr = input_fonksiyon();
        operatorler = inputOperator();
        veriler = inputVeriler();
        printf("epsilon degeri girin:");
        scanf("%lf", &x);
        printf("baslangic degerini girin: ");
        scanf("%lf", &start);
        printf("bitis degerini girin: ");
        scanf("%lf", &end);
        printf("maksimum iterasyon sayisini girin: ");
        scanf("%d", &maxIteration);
        printf("durma kosulu secin:\n1- f(x) <= epsilon\n2- (end-start)/2^n <= epsilon");
        scanf("%d", &choice);
        for(i=0;i<maxIteration && kontrol == 1;i++){
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fend = hesapla(cevir(veriler,veriSayisi,end),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
            mid = (end*fstart-start*fend)/(fstart - fend);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fmid = hesapla(cevir(veriler,veriSayisi,mid),veriSayisi,operatorSayisi,operatorler);
            printf("start: %lf\n", start);
            printf("end: %lf\n", end);
            printf("mid: %lf\n", mid);
            printf("f(start): %lf\n", fstart);
            printf("f(end): %lf\n", fend);
            printf("f(mid): %lf\n", fmid);
            printf("iterasyon: %d\n\n", N);
            
            switch (choice)
            {
            case 1:
                if(fmid < 0){if(-fmid <= x){;kontrol = 0;}}
                if(fmid > 0){if(fmid <= x){kontrol = 0;}}
                printf("result: %lf\n",mid);
                break;
        
            case 2:
                if(end-start<0){if(-(end-start)/ pow(2,N) <= x){kontrol = 0;}}
                if(end-start>0){if((end-start)/ pow(2,N) <= x){kontrol = 0;}}
                printf("result: %lf\n",mid);
                break;
        
            }
            if(fmid*fend <= 0){
                start = mid;
            }
            else if(fmid*fstart <= 0){
                end = mid;
            }
            else{
                printf("girilen degeler arasinda kok bulunamaz f(start) ve f(end) degerlerinin isaretleri ayni");
                break;
            }
            N++;
        }
    break;

    //NEWTON RAPSHON
    case 3:
        N=1;
        fonksiyonStr = input_fonksiyon();
        operatorler = inputOperator();
        veriler = inputVeriler();
        printf("epsilon degeri girin:");
        scanf("%lf", &x);
        printf("baslangic degerini girin: ");
        scanf("%lf", &start);
        printf("maksimum iterasyon sayisini girin: ");
        scanf("%d", &maxIteration);
        
        for(i=0;i<maxIteration && kontrol == 1;i++){
            tstart = start + 0.000001; //Türev için
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            ftstart = hesapla(cevir(veriler,veriSayisi,tstart),veriSayisi,operatorSayisi,operatorler);
            turev = (ftstart - fstart)/(tstart-start);
            next = start - fstart/turev;
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fnext = hesapla(cevir(veriler,veriSayisi,next),veriSayisi,operatorSayisi,operatorler);
            printf("xn: %lf\n", start);
            printf("xn+1: %lf\n", next);
            printf("f(xn): %lf\n", fstart);
            printf("f'(xn): %lf\n", turev);
            printf("iterasyon: %d\n\n", N);

            if(next-start < 0){if(-(next-start) <= x){;kontrol = 0;}}
            if(next-start > 0){if(next-start <= x){kontrol = 0;}}

            start = next;
            N++;
        }
        printf("result: %f",next);

        
        break;
    double d;
    case 4:
        printf("NxN lik bir matris icin N degerini girin: ");
        scanf("%d", &N);
        A = Matris_Alma(N);
        Matris_yazdirma(A,N);
        printf("\n");
        d = determinant(A,N);
        if(d == 0){
            printf("determinant = 0!");
        }
        else {
            kofaktor(A,N);
        }
        
        for ( i = 0; i < N; i++)
        {
            free(A[i]);
        }
        free(A);
        

        break;

    case 5:
        printf("NxN lik bir matris icin N degerini girin: ");
        scanf("%d", &N);
        printf("Ax = B icin A matrisinin degerini girin: " );
        A = Matris_Alma(N);
        printf("Ax = B icin B matrisinin degerini girin: " );
        B = B_matrisi_alma(N);
        Gauss_Eleminasyon(A,B,N);
        


        break;

    case 6:
        printf("NxN lik bir matris icin N degerini girin: ");
        scanf("%d", &N);
        printf("Ax = B icin A matrisinin degerini girin: " );
        A = Matris_Alma(N);
        printf("Ax = B icin B matrisinin degerini girin: " );
        B = B_matrisi_alma(N);
        matris_X = (double*)malloc(sizeof(double)*N);
        for(i=0;i<N;i++){
            printf("x%d degerini girin",i);
            scanf("%lf", &matris_X[i]);
        }
        printf("epsilon degerini girin");
        scanf("%lf", &epsilon);
        Gauss_Seidel(N,A,B,matris_X,epsilon);
    
        break;
    
    
    //Sayısal türev
    case 7:
        printf("1-Ileri Farklar\n2-Geri Farklar\n3-Merkezi Farklar\n");
        scanf("%d", &choice);
        fonksiyonStr = input_fonksiyon();
        operatorler = inputOperator();
        veriler = inputVeriler();
        printf("x degerini girin: ");
        scanf("%lf", &start);
        printf("h degerini giriniz: ");
        scanf("%lf", &h);
        switch (choice)
        {
        case 1:
  
            next = start + h;
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fnext = hesapla(cevir(veriler,veriSayisi,next),veriSayisi,operatorSayisi,operatorler);
            turev = (fnext - fstart)/(next-start);
            printf("xn: %lf\n", start);
            printf("xn+1: %lf\n", next);
            printf("f(xn): %lf\n", fstart);
            printf("f(xn+1): %lf\n", fnext);
            printf("f'(xn): %lf", turev);

            
            break;
        
        case 2:
            prev = start - h;
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fprev = hesapla(cevir(veriler,veriSayisi,prev),veriSayisi,operatorSayisi,operatorler);
            turev = (fstart-fprev)/(start-prev);
            printf("xn: %lf\n", start);
            printf("xn-1: %lf\n", prev);
            printf("f(xn): %lf\n", fstart);
            printf("f(xn-1): %lf\n", fprev);
            printf("f'(xn): %lf", turev);
            break;

        case 3:
            next = start + h;
            prev = start - h;
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fprev = hesapla(cevir(veriler,veriSayisi,prev),veriSayisi,operatorSayisi,operatorler);
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fnext = hesapla(cevir(veriler,veriSayisi,next),veriSayisi,operatorSayisi,operatorler);
            turev = (fnext-fprev)/(prev-next);
            printf("xn-1: %lf\n", prev);
            printf("xn+1: %lf\n", next);
            printf("f(xn-1): %lf\n", fprev);
            printf("f(xn+1): %lf\n", fnext);
            printf("f'(xn): %lf", turev);
            break;
        default:
            break;
        }

        break;
    
    case 8:
        toplam = 0;
        toplam2 = 0;
        N = 1;
        fonksiyonStr = input_fonksiyon();
        operatorler = inputOperator();
        veriler = inputVeriler();
        printf("h degerini girin: \n");
        scanf("%lf", &h);
        printf("x baslangic degerini girin: \n");
        scanf("%lf", &start);
        printf("x bitis degerini girin: \n");
        scanf("%lf", &end);
        fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
        fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
        fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
        fend = hesapla(cevir(veriler,veriSayisi,end),veriSayisi,operatorSayisi,operatorler);
        next = start + h;
        printf("x0: %lf\n", start);
        printf("f(x0): %lf\n\n", fstart);
        for(next;next != end;next = next+h){
            if(N%2==0){
                fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
                fnext = hesapla(cevir(veriler,veriSayisi,next),veriSayisi,operatorSayisi,operatorler);
                toplam = toplam + fnext;
                printf("x%d: %lf\n",N,next);
                printf("f(x%d): %lf\n\n",N,fnext);
            }
            else{
                fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
                fnext = hesapla(cevir(veriler,veriSayisi,next),veriSayisi,operatorSayisi,operatorler);
                toplam2 = toplam2 + fnext;
                printf("x%d: %lf\n",N,next);
                printf("f(x%d): %lf\n\n",N,fnext);

            }
            N++;
        }
        printf("x%d: %lf\n",N, end);
        printf("f(x%d): %lf\n\n",N, fend);
        
        Alan = h/3*((fstart+fend)+4*toplam2+2*toplam);


        printf("Integral: %lf", Alan);


        break;
    //TRAPEZ YÖNTEMİ
    case 9:
        toplam = 0;
        N = 1;
        fonksiyonStr = input_fonksiyon();
        operatorler = inputOperator();
        veriler = inputVeriler();
        
        printf("h degerini girin: \n");
        scanf("%lf", &h);
        printf("x baslangic degerini girin: \n");
        scanf("%lf", &start);
        printf("x bitis degerini girin: \n");
        scanf("%lf", &end);
        fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
        fstart = hesapla(cevir(veriler,veriSayisi,start),veriSayisi,operatorSayisi,operatorler);
        fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
        fend = hesapla(cevir(veriler,veriSayisi,end),veriSayisi,operatorSayisi,operatorler);
        next = start + h;
        printf("x0: %lf\n", start);
        printf("f(x0): %lf\n\n", fstart);
        for(next;next != end;next = next+h){
            fonksiyonAyir(fonksiyonStr, operatorler, veriler, &operatorSayisi, &veriSayisi);
            fnext = hesapla(cevir(veriler,veriSayisi,next),veriSayisi,operatorSayisi,operatorler);
            toplam = toplam + fnext;
            printf("x%d: %lf\n",N,next);
            printf("f(x%d): %lf\n\n",N,fnext);
            N++;
        }
        printf("x%d: %lf\n",N, end);
        printf("f(x%d): %lf\n\n",N, fend);
        
        Alan = h*((fstart+fend)/2+toplam);


        printf("Alan: %lf", Alan);
        break;

    case 10:
        carpim = 1;
        printf("enterpolasyon fonksiyonun derecesini girin: ");
        scanf("%d", &N);
        j = N;
        for ( i = 0; i <= N; i++)
        {
            printf("x = %d icin f(x) degerini girin: ",i);
            scanf("%lf", &fxValues[0][i]);
            
        }
        printf("hangi x noktasindaki degeri bulmak istiyorsunuz: ");
        scanf("%lf", &start);
        k = 0;
        while (k<N){

            for ( i = 0; i+1 < j+1; i++){
                fxValues[N-j+1][i] = fxValues[N-j][i+1] -fxValues[N-j][i];
            }

            j--;
            k++; 
        }
        sonuc = fxValues[0][0];
        // j bir azaldıgı için üstteki gibi n-j+2 yazmadım.
        k = 1;
        for(i=1;i<N-j+1;i++){
            carpim = carpim * (start-k+1)/k;
            sonuc = sonuc + carpim*fxValues[i][0];
            k++;
        } 
        printf("result: %lf", sonuc);


        
        break;
    
    default:
        break;


    }
}