#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

typedef struct product product;
typedef struct category category;
typedef struct shop shop;

struct product
{
    char name[40];
    float price;
    int quantity;
};

struct category
{
    char name[40];
    product *products;
    int productCount;
};

struct shop
{
    category* categories;
    int categoryCount;
};
int removeProducts(shop*myshop,char *name)
{
    int categoryIndex=findCategoryIndexBasedOnProduct(myshop,name);
    int productcount=myshop->categories[categoryIndex].productCount;
    int productIndex=-1;
    if(categoryIndex!=-1)
    {
     for(int i=0;i<productcount;i++)
     {
         if(strcmp(name,myshop->categories[categoryIndex].products[i].name)==0)
         {
             productIndex=i;
         }

     }
    } for(int j=productIndex;j<productcount-1;j++)
    {

        myshop->categories[categoryIndex].products[j]=myshop->categories[categoryIndex].products[j+1];
    }
    myshop->categories[categoryIndex].productCount--;

}
void addCategory(shop* myShop) {
    while (1) {
        // Allocate or resize memory for categories
        if (myShop->categoryCount == 0) {
            myShop->categories = (category*)malloc(sizeof(category));
        } else {
            myShop->categories = realloc(myShop->categories, (myShop->categoryCount + 1) * sizeof(category));
        }

        char name[40];
        printf("Please enter the new category name:");
        scanf("%39s", name);

        int findCategory = searchCategory(myShop, name);

        if (findCategory == -1) {
            // Set the category details
            strcpy(myShop->categories[myShop->categoryCount].name, name);
            myShop->categories[myShop->categoryCount].productCount = 0;

            printf("Category %s added successfully!\n", myShop->categories[myShop->categoryCount].name);

            printf("Do you want to add products now? (y/n)");
            char enter = getch();
            system("cls");

            if (enter == 'y' || enter == 'Y') {
                while (1) {
                    addProduct(myShop);

                    printf("Do you want to add more products? (y/n)\n");
                    char enter = getch();
                    system("cls");
                    if (enter != 'y' && enter != 'Y') {
                        break;
                    }
                }
            }

            // Increment the category count
            myShop->categoryCount++;

            printf("Do you want to add more categories? (y/n)\n");
             enter = getch();
            system("cls");

            if (enter != 'y' && enter != 'Y') {
                break; // Exit the loop if the user doesn't want to add more categories
            }
        } else {
            printf("The category %s already exists\n", name);
        }
    }
}

void displayCategories(shop* myShop)
{
    printf("              ________________All Categories______________________                 \n");
    printf("\n\n\n");
    for (int i = 0; i < myShop->categoryCount; i++)
    {
        printf("____________________________________  Category %d: %s __________________________________\n", i + 1, myShop->categories[i].name);

        for (int j = 0; j < myShop->categories[i].productCount; j++)
        {
            printf("  Product %d: %s\n", j + 1, myShop->categories[i].products[j].name);
            printf("  Product price is : %0.2f\n",  myShop->categories[i].products[j].price);
            printf("  Product quantity is %d:\n", myShop->categories[i].products[j].quantity);


        }
        if(myShop->categories[i].productCount>1){
        printf("     _______________________________________________________________________________       \n");
    }}
}
int findCategoryIndexBasedOnProduct(shop* myshop, const char productName[40])
{
    int categoryCount = myshop->categoryCount;

    for (int i = 0; i < categoryCount; i++)
    {
        int productCount = myshop->categories[i].productCount;

        for (int j = 0; j < productCount; j++)
        {
            if (strcmp(myshop->categories[i].products[j].name, productName) == 0)
            {
                return i;
            }
        }
    }

    // Product not found in any category
    return -1;
}
int searchCategory(shop*myshop,char name[40]) //Search in categories and return the index of the category if exist and return -1 if not
{
    int categoryIndex=myshop->categoryCount;
    int index=-1;
    for(int i=0; i<categoryIndex; i++)
    {
        if (strcmp(myshop->categories[i].name,name)==0)
        {
            index=i;
        }
    }
    return index;
}

int findProductIndex(shop* myshop, const char productName[40])
{
    int categoryCount = myshop->categoryCount;

    for (int i = 0; i <categoryCount; i++)
    {
        int productCount = myshop->categories[i].productCount;

        for (int j = 0; j < productCount; j++)
        {
            if (strcmp(myshop->categories[i].products[j].name, productName) == 0)
            {

                return j;
            }
        }
    }

    // Product not found in any category
    return -1;
}


void addProduct(shop* myShop)
{
    int productCount = myShop->categories[myShop->categoryCount].productCount; // Use the last added category
    if (productCount == 0)
    {
       myShop->categories[myShop->categoryCount].products=(product*)malloc(sizeof(product));
    }
    else
    {
       myShop->categories[myShop->categoryCount].products=realloc(myShop->categories[myShop->categoryCount].products,(productCount+1)*sizeof(product));
    }

        char name[40];
        float price;
        int quantity;

        printf("Enter the product name: ");
        scanf("%s", name);
        printf("Enter the product price: ");
        scanf("%f", &price);
        printf("Enter the product quantity: ");
        scanf("%i", &quantity);


       int productIndex=-1;
        for(int i=0;i<myShop->categories[myShop->categoryCount].productCount;i++)
        {
            if(strcmp(name,myShop->categories[myShop->categoryCount].products[i].name)==0)
            {
                productIndex=i;
                // myShop->categories[myShop->categoryCount].productCount--;
            }

        }
        if (productIndex != -1) // Product already exists
        {
            myShop->categories[myShop->categoryCount].products[productIndex].quantity += quantity;
            return;
        }
        else
        {
            // Product doesn't exist, add a new entry
            myShop->categories[myShop->categoryCount].products[productCount].quantity = quantity;
            myShop->categories[myShop->categoryCount].products[productCount].price = price;
            strcpy(myShop->categories[myShop->categoryCount].products[productCount].name, name);
            myShop->categories[myShop->categoryCount].productCount++;
        }

}

void addNewProduct(shop*myshop)
{
    char name[40];
    printf("choose category : ");
    scanf("%s",name);
    int index=searchCategory(myshop,name);



    if(index!=-1)
    {
        int productCount=myshop->categories[index].productCount;
        if(myshop->categories[index].productCount==0)
        {
          myshop->categories[index].products=(product*)malloc(sizeof(product));
        }else{
         myshop->categories[index].products=realloc(myshop->categories[index].products,(productCount+1)*sizeof(product));

        }
        char name[40];
        printf("enter the product name :");
        scanf("%s",name);
        printf("enter the product price :");
        float price;
        scanf("%f",&price);
         int quantity;
        printf("enter the product quantity : ");
        scanf("%i",&quantity);
        int productIndex=findProductIndex(myshop,name);
        if(productIndex!=-1)
        {
             myshop->categories[index].products[productIndex].quantity+=quantity;

        }else{
        strcpy(myshop->categories[index].products[myshop->categories[index].productCount].name,name);

        myshop->categories[index].products[myshop->categories[index].productCount].price=price;

        myshop->categories[index].products[myshop->categories[index].productCount].quantity=quantity;
        printf("Product %s  added successfully to category: %s\n", myshop->categories[index].products[myshop->categories[index].productCount].name,myshop->categories[index].name);

        myshop->categories[index ].productCount++;
        }
    }
    else
    {

        printf("%s non exist product ",name);
    }


}

void removeCategory(shop*myshop)
{
    printf("enter the category you want to remove :");
    char name[40];
    scanf("%s",name);
    int index=searchCategory(myshop,name);
    if (index!=-1)
    {
        int categoryCount=myshop->categoryCount;
        for(int i=index; i<categoryCount-1; i++)
        {
            myshop->categories[i]=myshop->categories[i+1];
        }
        myshop->categoryCount--;
        printf("the category %s deleted successfully!! \n",name);
    }
    else
    {

        printf("this category not exist \n ");
    }
}
void removeProduct(shop* myshop)
{   printf("\n\n");
    diplayProducts(myshop);
     printf("\n\n");
    int index = -1;
    printf("Enter the product you want to remove: ");
    char name[40];
    scanf("%s", name);
    int categoryCount = myshop->categoryCount;

    for (int i = 0; i < categoryCount; i++)
    {
        int productCount = myshop->categories[i].productCount;

        for (int j = 0; j < productCount; j++)
        {
            if (strcmp(myshop->categories[i].products[j].name, name) == 0)
            {
                index = j;
                for (int h = index; h < productCount; h++)
                {
                    myshop->categories[i].products[h] = myshop->categories[i].products[h + 1];
                }
                myshop->categories[i].productCount--;

                printf("Product '%s' deleted successfully from category '%s'\n",name,myshop->categories[i].name);
                system("pause");
                system("cls");
                displayCategories(myshop);

                return; // Exit the function after printing the success message
            }
        }
    }

    // If the function reaches here, it means the product was not found
    printf("Product '%s' not found in any category\n", name);
}


void moveProduct(shop* myshop)
{
    displayCategories(myshop);
    printf("\n\n\n");

    char productName[40];
    char categoryName[40];
    printf("Enter the product you want to move: ");
    scanf("%s", productName);
    printf("Enter the new category: ");
    scanf("%s", categoryName);

    int sourceCategoryIndex = findCategoryIndexBasedOnProduct(myshop, productName);
    int destinationCategoryIndex = searchCategory(myshop, categoryName);
    if (sourceCategoryIndex != -1 && destinationCategoryIndex != -1)
    {
        // Find the product in the source category
        int productIndex = -1;
        for (int i = 0; i < myshop->categories[sourceCategoryIndex].productCount; i++)
        {
            if (strcmp(myshop->categories[sourceCategoryIndex].products[i].name, productName) == 0)
            {
                productIndex = i;
                break;
            }
        }

            myshop->categories[destinationCategoryIndex].products = realloc(myshop->categories[destinationCategoryIndex].products, (myshop->categories[destinationCategoryIndex].productCount + 1) * sizeof(product));
                strcpy(myshop->categories[destinationCategoryIndex].products[myshop->categories[destinationCategoryIndex].productCount].name, productName);
                myshop->categories[destinationCategoryIndex].products[myshop->categories[destinationCategoryIndex].productCount].price = myshop->categories[sourceCategoryIndex].products[productIndex].price;
                myshop->categories[destinationCategoryIndex].products[myshop->categories[destinationCategoryIndex].productCount].quantity = myshop->categories[sourceCategoryIndex].products[productIndex].quantity;
                myshop->categories[destinationCategoryIndex].productCount++;


                for (int j = productIndex; j < myshop->categories[sourceCategoryIndex].productCount - 1; j++)
                {
                    myshop->categories[sourceCategoryIndex].products[j] = myshop->categories[sourceCategoryIndex].products[j + 1];
                }
                myshop->categories[sourceCategoryIndex].productCount--;

                printf("Product '%s' moved successfully to category '%s'\n", productName, categoryName);
                system("pause");
                system("Cls");

                printf("the updated menu \n\n");
                displayCategories(myshop);



        }
    else
    {
        printf("Either source or destination category does not exist.\n");
    }
}
void diplayProducts(shop*myshop)
{
     printf("       __________________________________________All Products _________________________________                 \n");
    printf("\n\n");
    for (int i = 0; i < myshop->categoryCount; i++)
    {
        for (int j = 0; j < myshop->categories[i].productCount; j++)
        {
            printf("  Product %d: %s\n", j + 1, myshop->categories[i].products[j].name);
            printf("  Product price is : %0.2f\n",  myshop->categories[i].products[j].price);
            printf("  Product quantity is %d:\n", myshop->categories[i].products[j].quantity);
            printf("_________\n");

        }
        printf("     _______________________________________________________________________________       \n");
    }
}


void printBill(product* bill, int itemCount, float totalPurchase) {
    system("cls");
    printf("============================================\n");
    printf("                 Final Bill\n");
    printf("============================================\n\n");

    for (int i = 0; i < itemCount; i++) {
        printf("%-20s %-10.2f %-5d %-10.2f\n", bill[i].name, bill[i].price, bill[i].quantity, bill[i].price * bill[i].quantity);
    }

    printf("\nTotal Purchase Amount: %.2f\n", totalPurchase);
    printf("Press enter to return to the main menu\n");
    system("pause");
}
void sellProduct(shop* myshop) {
    char choice;
    float totalPurchase = 0.0;

    product bill[50];
    int billItemCount = 0;

    do {
        system("cls");
        diplayProducts(myshop);
        char productName[40];
        int quantity;
        float totalprice = 0;
        int categoryCount = myshop->categoryCount;

        printf("Enter the product you want to buy: ");
        scanf("%s", productName);
        printf("Enter the quantity you want: ");
        scanf("%i", &quantity);

        int findproduct = -1, findCategory = -1;

        for (int i = 0; i < categoryCount; i++) {
            int productCount = myshop->categories[i].productCount;
            for (int j = 0; j < productCount; j++) {
                if (strcmp(myshop->categories[i].products[j].name, productName) == 0) {
                    findproduct = j;
                    findCategory = i;
                    break;
                }
            }
        }

        if (findproduct != -1) {
            int productquantity = myshop->categories[findCategory].products[findproduct].quantity;
            if (productquantity >= quantity) {
                myshop->categories[findCategory].products[findproduct].quantity -= quantity;
                if (myshop->categories[findCategory].products[findproduct].quantity == 0) {
                    removeProducts(myshop, myshop->categories[findCategory].products[findproduct].name);
                }
                totalprice = myshop->categories[findCategory].products[findproduct].price * quantity;
                printf("Your purchase done successfully!! You bought %s for %.2f e.g \n", productName, totalprice);
                totalPurchase += totalprice;

                // Add the product to the bill array
                strcpy(bill[billItemCount].name, productName);
                bill[billItemCount].price = myshop->categories[findCategory].products[findproduct].price;
                bill[billItemCount].quantity = quantity;
                billItemCount++;
            } else {
                printf("There is not enough quantity of the product %s. There is only %i\n", productName, myshop->categories[findCategory].products[findproduct].quantity);
            }
        } else {
            printf("%s not available in our store. Check this later!\n", productName);
        }

        printf("Do you want to buy another product? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    // Print the final bill

    printBill(bill, billItemCount, totalPurchase);
}
char storeName[50];

int main()
{
    shop myshop;
    myshop.categoryCount=0;
    myshop.categories=NULL;
    int selected_option = 0;
    int total_options = 8;

     printf("Please enter the name of the store: ");
    scanf("%49[^\n]", storeName);

    while (1)
    {
        system("cls");
        printMainMenu(selected_option);
        char enter = getch();

        if (enter == 27) // escape button
        {
            break;
        }
        else if (enter == 72) // up arrow
        {
            selected_option = (selected_option - 1 + total_options) % total_options;
        }
        else if (enter == 80) // down arrow
        {
            selected_option = (selected_option + 1) % total_options;
        }
        else if (enter == 13) // enter
        {
            switch (selected_option)
            {
            case 0:
                system("cls");

                printf("______________________Create New Category________________ \n");
                addCategory(&myshop);

                break;

            case 1:
                system("cls");
                printf("______________________Create New Product________________ \n");
                addNewProduct(&myshop);
                system("pause");
                break;

            case 2:
                system("cls");
                displayCategories(&myshop);
                system("pause");
                break;

            case 3:
                system("cls");
                sellProduct(&myshop);

                break;

            case 4:
                system("cls");
                printf("__________________________________________Move Product___________________________________ \n");
                moveProduct(&myshop);
                system("pause");
                break;

            case 5:
                system("cls");
                printf("____________ Remove Category ________________________ \n");
                removeCategory(&myshop);
                system("pause");
                break;
            case 6:
                system("cls");
                   printf("____________ Remove  Product ________________________ \n");
               removeProduct(&myshop);
                system("pause");
                break;

            case 7:
                system("cls");
                printf("program Ended \n");
                exit(0);
                break;
            }
        }
    }
 free(myshop.categories);
 free(myshop.categories->products);
    return 0;
}


void printMainMenu(int option) {
    char *menu[] = {
        "1-Create New Category",
        "2-Add New Product",
        "3-show all Categories",
        "4-Buy products",
        "5-Move product",
        "6-Remove Category",
        "7-Remove Product",
        "8-Exit"
    };

    SetColor(34);
   // printf("                  ________________________  Welcome to %s Store  ____________________                                       \n\n\n\n\n ", storeName);

    printf("                                  ============================================\n");
    SetColor(30);
    printf("                                             Welcome to %s Store\n", storeName);
    SetColor(34);
    printf("                                  ============================================\n\n");
    for (int i = 0; i < 8; i++) {
        if (i == option) {
            SetColor(34);
        } else {
            SetColor(30);
        }
        gotoxy(43,  6+ i);
        printf("%s \n", menu[i]);
    }
}
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
