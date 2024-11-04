#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int first_screen();
int login();
int AdminPanel();
int ViewProducts();
int AddProducts();
int DeleteProducts();
int BuyProducts(int x);
int MoneyReciept(int x);
int Reciept();

int first_screen() {
    int in;

    printf("\n\t\t* To Login as Authorized Admin Press '1'");
    printf("\n\t\t* To Purchase Products as User Press '2'");
    printf("\n\t\t* To Exit Press '3'");
    printf("\n\n\t\t* Enter Your Choice: ");
    scanf("%i", &in);
    printf("\n");

    if (in == 1) {
        login();
    } else if (in == 2) {
        ViewProducts();
        BuyProducts(0);
    } else if (in == 3) {
        printf("\n\t\t* Thanks For Using This Software.\n");
        exit(0);
    } else {
        printf("\a\t\t* Invalid Input. Please Try Again.\n");
        first_screen();
    }
    return 0;
}

int login() {
    char e[100], p[100];

    printf("\t\t* Enter E-mail: ");
    scanf("%s", e);
    printf("\t\t* Enter Password: ");
    scanf("%s", p);
    printf("\n");

    if (strcmp(e, "njn@supershop.com.bd") == 0 && strcmp(p, "njn12345") == 0) {
        printf("\t\t* Successfully Logged in.\n");
        AdminPanel();
    } else {
        printf("\a\n\t\t* E-mail or Password Does Not Match.\n\t\tPlease re-enter E-mail and Password.\n\n");
        login();
    }
    return 0;
}

int AdminPanel() {
    int c;

    printf("\n\n\t\t\t\tAdmin Panel\n");
    printf("\t\t\t\t___________\n\n");
    printf("\t\t* To View Products Press '1'\n");
    printf("\t\t* To Add New Products Press '2'\n");
    printf("\t\t* To Delete Products Press '3'\n");
    printf("\t\t* To Exit Press '4'\n");

    printf("\n\t\t* Enter Your Choice: ");
    scanf("%i", &c);

    switch (c) {
        case 1:
            ViewProducts();
            AdminPanel();
            break;
        case 2:
            AddProducts();
            AdminPanel();
            break;
        case 3:
            DeleteProducts();
            AdminPanel();
            break;
        case 4:
            printf("\n\t\t* Thanks For Using The Software.\n");
            break;
        default:
            printf("\a\n\t\t* Invalid Input. Please Try again.\n");
            AdminPanel();
    }
    return 0;
}

int ViewProducts() {
    FILE *fproduct;
    char ch;

    fproduct = fopen("Product.txt", "r");

    if (fproduct == NULL) {
        printf("\n\t\t* The Product List is Empty.\n\t\tPlease Add Products and Check it Later.\n");
        AdminPanel();
    } else {
        printf("\n\n\tCode\t\tName\t\t\tQuantity\tPrice\n\n");

        while ((ch = fgetc(fproduct)) != EOF) {
            printf("%c", ch);
        }
    }
    fclose(fproduct);
    return 0;
}

int AddProducts() {
    FILE *fproduct;
    char name[100];
    int id, price, quantity;

    fproduct = fopen("Product.txt", "a");

    while (1) {
        printf("\n\t\t* Enter Product Code, Press '-1' To Break: ");
        scanf("%i", &id);

        if (id == -1) {
            break;
        }
        printf("\t\t* Enter Product Name: ");
        scanf("%s", name);
        printf("\t\t* Enter Product Quantity: ");
        scanf("%d", &quantity);
        printf("\t\t* Enter Product Price Per Piece: ");
        scanf("%d", &price);

        fprintf(fproduct, "\t%d\t\t%s\t\t%d\t\t%d\n", id, name, quantity, price);
    }
    printf("\n\n\t\t* Products Added Successfully.\n");

    fclose(fproduct);
    return 0;
}

int DeleteProducts() {
    int l, count = 0;
    char str[100], temp[] = "temp.txt";
    FILE *fp1, *fp2;

    fp1 = fopen("Product.txt", "r");

    if (!fp1) {
        printf("Something is wrong.\n");
        return 1;
    }
    printf("\n\n\t\t* Before Deleting Products, The Product List: \n");
    ViewProducts();

    fp2 = fopen(temp, "w");

    printf("\n\t\t* Enter The Line Number You Want To Delete: ");
    scanf("%i", &l);

    while (fgets(str, 100, fp1) != NULL) {
        count++;
        if (count != l) {
            fputs(str, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);

    remove("Product.txt");
    rename(temp, "Product.txt");

    printf("\n\n\t\t* After Deleting, The Updated Product List: \n");
    ViewProducts();

    return 0;
}

int BuyProducts(int x) {
    int input;

    printf("\n\t\t* Enter Product Code You Want To Buy From The List: ");
    scanf("%i", &input);

    if (input >= 1 && input <= 5) {
        MoneyReciept(input);
    } else {
        printf("\n\t\t* Invalid Input. Please Try Again.\n");
        BuyProducts(0);
    }
    return 0;
}

int MoneyReciept(int x) {
    int a, b, c = 0;

    printf("\n\t\t* Enter Quantity: ");
    scanf("%i", &a);

    switch (x) {
        case 1: c = a * 8000; break;
        case 2: c = a * 15000; break;
        case 3: c = a * 7500; break;
        case 4: c = a * 8000; break;
        case 5: c = a * 5000; break;
    }

    printf("\n\t\t* Total Price: %i\n", c);
    printf("\n\t\t* To Buy Another Product, Press '1'\n\t\tOr To Generate Money Receipt, Press '0': ");
    scanf("%i", &b);

    if (b == 0) {
        Reciept();
    } else if (b == 1) {
        BuyProducts(c);
    }
    return 0;
}

int Reciept() {
    char name[100], ph[100];

    printf("\n\t\t* Enter Your Name: ");
    scanf("%s", name);
    printf("\n\n\t\t* Enter Your Phone Number: ");
    scanf("%s", ph);

    printf("\n\n\n\t\t\t\tMoney Receipt");
    printf("\n\t\t\t\t_____________\n\n");
    printf("\n\t\t\tName\t : \t%s", name);
    printf("\n\t\t\tContact No.: \t%s", ph);
    printf("\n\n\n\t\tThanks For Using This Software. Good Day.\n");

    return 0;
}

int main() {
    printf("\n\n\n\n\n\n\n\n\t\t\t\tN.J.N Super Shop\n");
    printf("\t\t\t\t________________\n");

    first_screen();

    return 0;
}
