/* ============================================================================
 *                         PRETTY'S COFFEE SHOP
 *                     Coffee Shop Management System
 * ============================================================================
 *  A simple console-based C application to manage coffee orders and stock.
 *
 *  Features:
 *      - Customer panel : browse menu, add coffee & add-ons,
 *                          view / delete items, confirm order
 *      - Admin panel     : password-protected stock management
 *      - Order history   : orders are written to and read from a text file
 *                          (coffeeshop.txt)
 * ==========================================================================*/

#include <stdio.h>
#include <string.h>

/* ----------------------------------------------------------------------------
 * writetoorder()
 *  Writes the finalized order (item names, prices, and total) to
 *  "coffeeshop.txt". Called once the customer confirms their order.
 * --------------------------------------------------------------------------*/
void writetoorder(float total, int count, float *price, char names[50][20]) {

    FILE *file = fopen("coffeeshop.txt", "w");
    if (file == NULL) {

        printf("File doesn't exist.\n");
        return;

    }

    fprintf(file, "Order Details:\n\n");
    fprintf(file, "Item: \n");

    for (int i = 0; i < count; i++) {

        fprintf(file, "%d. %s: $%.2f\n", i + 1, names[i], price[i]);

    }
    fprintf(file, "\nTotal: $%.2f\n", total);

    fclose(file);
}

/* ----------------------------------------------------------------------------
 * readtoorder()
 *  Reads back and prints the contents of "coffeeshop.txt" to the console,
 *  i.e. the receipt for the most recently confirmed order.
 * --------------------------------------------------------------------------*/
void readtoorder() {

    FILE *file = fopen("coffeeshop.txt", "r");
    if (file == NULL) {
        printf("File dosen't exist.\n");
        return;
    }

    printf("Read the file.\n\n");
    char ch;
    while ((ch = fgetc(file)) != EOF) {

        putchar(ch);

    }

    fclose(file);

}

/* ----------------------------------------------------------------------------
 * Addcoffee()
 *  Displays the coffee menu and add-ons, and lets the customer:
 *      1-5 : add a coffee item to the order
 *      6   : add extra add-ons (milk / honey / sugar / flavour)
 *      7   : delete an item already added to the order
 *      8   : confirm the order (writes the receipt to file)
 * --------------------------------------------------------------------------*/
int Addcoffee() {
    const float americano = 5.0;
    const float latte = 3.50;
    const float mocha = 5.50;
    const float cappuccino = 7.0;
    const float macchiato = 6.0;
    printf("\nCoffee Menu:\n");
    printf("1. Americano: $5.0\n");
    printf("2. Latte: $3.50\n");
    printf("3. Mocha: $5.50\n");
    printf("4. Cappuccino: $7.0\n");
    printf("5. Macchiato: $6.0\n");
    printf("6. Addons: \n");
    printf("   a.Milk: $2.50\n");
    printf("   b.Honey: $3.00\n");
    printf("   c.Sugar: $1.00\n");
    printf("   d.Flavour: $3.50\n");
    printf("7. Delete Coffee Item\n");
    printf("8. Confirm Order\n\n");

    int choice;
    char addons;
    float total = 0.0;
    int deletechoice;
    int count = 0;
    float price[50];
    char names[50][20];
    int i;

    do {
        printf("Enter customer choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Added Americano: $%.2f\n", americano);
            price[count] = americano;
            strcpy(names[count], "Americano");
            count++;
            total += americano;
            break;
        case 2:
            printf("Added Latte: $%.2f\n", latte);
            price[count] = latte;
            strcpy(names[count], "Latte");
            count++;
            total += latte;
            break;
        case 3:
            printf("Added Mocha: $%.2f\n", mocha);
            price[count] = mocha;
            strcpy(names[count], "Mocha");
            count++;
            total += mocha;
            break;
        case 4:
            printf("Added Cappuccino: $%.2f\n", cappuccino);
            price[count] = cappuccino;
            strcpy(names[count], "Cappuccino");
            count++;
            total += cappuccino;
            break;
        case 5:
            printf("Added Macchiato: $%.2f\n", macchiato);
            price[count] = macchiato;
            strcpy(names[count], "Macchiato");
            count++;
            total += macchiato;
            break;
        case 6:
            printf("Enter Addons(0 to confirm): ");
            scanf(" %c", &addons);
            while (addons != '0') {
                switch (addons) {
                case 'a':
                    printf("Added Milk.\n");
                    price[count] += 2.50;
                    strcpy(names[count], "Milk");
                    count++;
                    total += 2.50;
                    break;
                case 'b':
                    printf("Added Honey.\n");
                    price[count] += 3.00;
                    strcpy(names[count], "Honey");
                    count++;
                    total += 3.00;
                    break;
                case 'c':
                    printf("Added Sugar.\n");
                    price[count] += 1.00;
                    strcpy(names[count], "Sugar");
                    count++;
                    total += 1.00;
                    break;
                case 'd':
                    printf("Added Flavour.\n");
                    price[count] += 3.50;
                    strcpy(names[count], "Flavour");
                    count++;
                    total += 3.50;
                    break;
                }
                printf("Enter Addons(0 to confirm): ");
                scanf(" %c", &addons);
            }
            break;

        case 7:
            printf("Current Order: \n");
            for (i = 0; i < count; i++) {
                printf("%d. %s: $%.2f\n", i + 1, names[i], price[i]);
            }

            printf("What do you want to delete: ");
            scanf("%d", &deletechoice);

            if (deletechoice >= 1 && deletechoice <= count) {
                total = total - price[deletechoice - 1];
                printf("Deleted %s.\n", names[deletechoice - 1]);

                for (i = deletechoice - 1; i < count - 1; i++) {
                    price[i] = price[i + 1];
                    strcpy(names[i], names[i + 1]);
                }
                count--;
            } else {
                printf("Invalid Deletation.\n");
            }

            break;

        case 8:
            printf("\nOrder Cofirmed. Total Cash: $%.2f\n", total);
            printf("Thanks for your ordering.\n\n");
            writetoorder(total, count, price, names);
            break;

        default:

            printf("Invalid Order\n");

        }
    }

    while (choice != 8);
    return 0;

}

/* ----------------------------------------------------------------------------
 * struct CoffeeItem
 *  Represents a single stock entry (used by the admin panel) with a
 *  name, unit price, and quantity available in stock.
 * --------------------------------------------------------------------------*/
struct CoffeeItem {
    char name[20];
    float price;
    int quantity;
};
struct CoffeeItem stock[10];

/* ----------------------------------------------------------------------------
 * addtostock()
 *  Lets the admin add new items into the "stock" array, entering the
 *  name, price, and quantity for each new item, then prints a summary
 *  of everything currently in stock.
 * --------------------------------------------------------------------------*/
void addtostock() {

    int newitems;
    printf("Enter the number of new items to add: ");
    scanf("%d", &newitems);

    for (int i = 0; i < newitems; i++) {
        printf("Enter name of new item: ");
        scanf("%s", stock[i].name);

        printf("Enter price of %s: $", stock[i].name);
        scanf("%f", &stock[i].price);

        printf("Enter quantity of %s: ", stock[i].name);
        scanf("%d", &stock[i].quantity);

        float total = stock[i].price * stock[i].quantity;

        printf("Added %d %s to stock: $%.2f. (Total: $%.2f)\n", stock[i].quantity, stock[i].name, stock[i].price, total);
    }

    printf("\nAdded to stock:\n");
    for (int i = 0; i < 10; i++) {
        if (stock[i].quantity > 0) {
            float total = stock[i].price * stock[i].quantity;
            printf("%d.Added %d %s: $%.2f each, Quantity: %d. Total: $%.2f\n", i + 1, stock[i].quantity, stock[i].name, stock[i].price, stock[i].quantity, total);
        }
    }

}

/* ----------------------------------------------------------------------------
 * admin()
 *  Handles the admin login (name + password, max 2 attempts) and, on a
 *  successful login, hands control over to addtostock().
 * --------------------------------------------------------------------------*/
int admin() {

    int pass;
    char name[100];

    printf("\nEnter your name: ");
    scanf("%s", &name);

    int count = 0;
    int p = 12345;

    do {
        printf("\nEnter password: ");
        scanf("%d", &pass);
        if (pass == p) {
            printf("Correct Password\n\n");
            addtostock();
            break;
        } else {
            count++;
            printf("Incorrect Password.\n\n");
        }
        if (count == 2) {
            printf("Sorry. You're exiting");
            return 0;
        }
    }

    while (1);

}

/* ----------------------------------------------------------------------------
 * customer()
 *  Displays the customer panel options and routes every selection into
 *  Addcoffee(), then prints the saved receipt back out via
 *  readtoorder().
 * --------------------------------------------------------------------------*/
void customer() {
    printf("1. Add Coffee Item \n");
    printf("2. Add Ons \n");
    printf("3. Display order \n");
    printf("4. Delete Coffee Item\n");
    printf("5. Confirm Order \n\n");
    printf("Choose One: ");

    int select;
    scanf("%d", &select);
    switch (select) {
    case 1:
        Addcoffee();
        break;
    case 2:
        Addcoffee();
        break;
    case 3:
        Addcoffee();
        break;
    case 4:
        Addcoffee();
        break;
    case 5:
        Addcoffee();
        break;
    }
    readtoorder();

}

/* ----------------------------------------------------------------------------
 * main()
 *  Prints the welcome banner and routes the user into either the
 *  Admin panel or the Customer panel.
 * --------------------------------------------------------------------------*/
int main() {
    printf("        ======================================================================================================\n");
    printf("        ===============================          Coffee Shop Managment             ===========================\n");
    printf("                                                ----------------------\n");
    printf("                                                       WELCOME      \n ");
    printf("                                               =======================\n");
    printf("                                          <<<<<    Pretty's COFFEE SHOP   >>>>>\n");
    printf("                                          ___________________________________\n\n\n\n\n");




    printf("How can I help you??\n\n");

    int user;
    printf(" 1. Main Menu \n");
    printf(" 2. Exit\n\n");
    printf("Enter you choice: ");
    scanf("%d", &user);

    if (user == 1) {
        printf("\n1. Admin panel\t\t\t");
        printf("2. Customer panel\n\n");
    } else if (user == 2) {

        printf("You're exiting");

        return 0;
    }

    int enter;
    printf("Choose your panel: ");
    scanf("%d", &enter);
    if (enter == 1) {

        admin();

    } else if (enter == 2) {

        customer();

    }

    return 0;

}
