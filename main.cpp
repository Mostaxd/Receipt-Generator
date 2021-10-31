 #include <stdio.h>

 #include <stdlib.h>

 #include <ctype.h>

 #include <string.h>

 int itemsInList = 0;
 float total;
 int count[256];
 struct Product {
   char productName[50];
   float price;

 };

 struct Product p1;
 struct Product prodList[256];

 void addToList(struct Product p) {

   char lowname[50];
   strcpy(lowname, p.productName);

   int i;
   int found = 0;
   for (i = 0; i < itemsInList; i++) {

     char temp[50];
     strcpy(temp, prodList[i].productName);

     if (strcmp(temp, lowname) == 0) {
       float t = p.price;

       // FOUND, add item to total, increment count, set found to true
       prodList[i].price += t;
       count[i]++;
       found = 1;
       // we could allow loop to continue but for efficiency we end for loop now with break

     }
   }
   // if not found already add NEW entry to end of list
   if (!found) {
     strcpy(prodList[itemsInList].productName, lowname);
     // add with correct total and count
     prodList[itemsInList].price = p.price;
     count[i] = 1;
     // and increment total items in list count
     itemsInList++;
   }
 }

 void printBill() { //internal process
   FILE * fpp;
   fpp = fopen("bill.txt", "w");
   if (fpp == NULL) {
     perror("file that we writing to didn't open");
   }

   for (int i = 0; i < itemsInList; i++) {
     float average = prodList[i].price / count[i];
     fprintf(fpp, "%-10s:\t Produkte:%d\t Mittelwert:%.2f\n", prodList[i].productName, count[i], average);
   }

   fprintf(fpp, "---------------\n");
   fprintf(fpp, "Summe: %.2f", total);
   fclose(fpp);

 }

 int main() {
   total = 0;

   //input file
   FILE * fp;
   fp = fopen("products.txt", "r");
   if (fp == NULL) {
     perror("files didn't open");
   }

   while (1) {
     fscanf(fp, "%s %f", p1.productName, &p1.price);
     total += p1.price;

     addToList(p1);

     if (feof(fp)) {
       break;
       fclose(fp);
     }

   }

   printBill();

   return 0;
 }
