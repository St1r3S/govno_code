#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 4096

typedef struct product product;

static product *head =NULL;

struct product
{
    char *name;
    char *category;
    int amount_in_storage;
    //expiration_date;
    int day_expiration, month_expiration, year_expiration; //day, month, year
    //date_of_deliver;
    int day_of_deliver, month_of_deliver, year_of_deliver; //day, month, year
    int amount_of_storage_space_for_category;
    product *next;
};

//Prototypes
int menu();
void add_node(); //ADDING PRODUCT
void delete_node(product **head); //DELETING PRODUCT
void update_data(); //UPDATE DATA OF PRODUCT
void print_list(); //PRINT ALL PRODUCTS
void print_data_with_current_date(); //PRINTF ALL PRODUCTS WITH EXPIRED DATE
void search_by_list_of_products(); //PRINT PRODUCTS BY LIST OF PRODUCTS
void empty_store_place(); //PRINT EMPTY STORE PLACE OF PRODUCT
void search_by_category(); //SEARCH PRODUCTS BY CATEGORY
void sorting(); //SORTING LIST OF PRODUCTS

//Secondary used functions
//void print_cat(product *tmp);
void add_product_to_list(product *ptr); //adding product to list
void write_data(product *ptr); //write data of product
int node_count(product *head, int count); //count of products
int position_for_deleting(); //entering position of product that you want to delete
void pauseConsole(); //just pause

//Check functions
void check_for_expiration_date(product *ptr);
void check_for_date_of_deliver(product *ptr);
void check_for_storage_place(product *ptr);
int check_for_amount_of_nodes(int number_of_node, int count);
int check_for_current_date(int day_cur, int month_cur, int year_cur);
int check_for_position_of_nodes(int position, int count);


int main() {
    printf("Welcome to the shop\n");
    int position = 0;

    while (1)
    {
        switch (menu())
        {
            case 1: add_node(); break;
            case 2:delete_node(&head); break;
            case 3:update_data(); break;
            case 4:print_list(); break;
            case 5: print_data_with_current_date(); break;
            case 6:search_by_list_of_products(); break;
            case 7:empty_store_place(); break;
            case 8: search_by_category(); break;
            case 9:sorting(); break;
            case 10: printf("Goodbye...");
                return 0;
            default:
                printf("Something went wrong -_-\nEnter correct number\n");
        }
    }
}

void add_node() {    //creating product
    printf("ADDING NEW PRODUCT\n");

    product *ptr = malloc(sizeof(product));
    ptr->next = NULL;

    write_data(ptr);

    add_product_to_list(ptr);

    pauseConsole();
    system("cls");
}

void add_product_to_list(product *ptr){ //adding product to list

    // if list is empty
    if (head == NULL) {
        head = ptr;
        return;
    }

    product *tmp = head;
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = ptr;


}

void print_list(){

    printf("\nLIST OF PRODUCTS: \n\n");

    if (head == NULL) {
        printf("LIST IS EMPTY! \n\n");
        return;
    }

    product *tmp = head;

    while (tmp != NULL) {
        printf("-----------------\n");
        printf("NAME: %s\n", tmp->name);
        printf("CATEGORY: %s\n", tmp->category);
        printf("AMOUNT IN STORAGE: %d\n", tmp->amount_in_storage);
        printf("EXPIRATION DATE: Day:%d, Month:%d, Year:%d\n", tmp->day_expiration, tmp->month_expiration, tmp->year_expiration);
        printf("DATE OF DELIVER: Day:%d, Month:%d, Year:%d\n", tmp->day_of_deliver, tmp->month_of_deliver, tmp->year_of_deliver);
        printf("AMOUNT OF STORAGE PLACE FOR CATEGORY: %d\n", tmp->amount_of_storage_space_for_category);
        printf("-----------------\n");

        tmp = tmp->next;
    }
    pauseConsole();
    system("cls");
}

int menu()
{
    int choice = 0;
    do
    {
        printf("Menu\n");
        printf("1. Add element\n");
        printf("2. Delete element\n");
        printf("3. Update element\n");
        printf("4. Print all data\n");
        printf("5. Print list with expired date on current date\n");
        printf("6.Find product and amount on storage\n");
        printf("7.Print empty storage places for products\n");
        printf("8.Find product by the category\n");
        printf("9.Sort by name and date\n");
        printf("10. Exit\n\n");
        printf("Enter your choice here-> ");
        scanf_s("%d", &choice);
        system("cls");
    }while (choice>10);
    return choice;
}

void write_data(product *ptr){ //product info

    //add name
    ptr->name = malloc(64 * sizeof(char));
    printf("Enter name:");
    scanf("%s", ptr->name);

    //add category
    ptr->category = malloc(64 * sizeof(char));
    printf("\nEnter category (1-Import, 2-No import): ");
    scanf_s("%s", ptr->category);

    //add amount in storage
    printf("\nEnter amount in storage: ");
    scanf_s("%d", &ptr->amount_in_storage);
    if(ptr->amount_in_storage < 0){
        printf("\nWrong data. ");

        do {
            printf("Write correct amount in storage:");
            scanf_s("%d", &ptr->amount_in_storage);
        } while (ptr->amount_in_storage < 0 );

        if(ptr->amount_in_storage > 0){
            printf("New data saved\n");
        }
    }

    //add expiration date
    //ptr->expiration_date = malloc(64 * sizeof(char));
    printf("\nEnter expiration date:\n");
    printf("Enter day:");
    scanf_s("%d", &ptr->day_expiration);
    printf("Enter month:");
    scanf_s("%d", &ptr->month_expiration);
    printf("Enter year:");
    scanf_s("%d", &ptr->year_expiration);
    check_for_expiration_date(ptr);

    //add date of deliver
    //ptr->date_of_deliver = malloc(64 * sizeof(char));
    printf("\nEnter date of deliver:\n");
    printf("Enter day:");
    scanf_s("%d", &ptr->day_of_deliver);
    printf("Enter month:");
    scanf_s("%d", &ptr->month_of_deliver);
    printf("Enter year:");
    scanf_s("%d", &ptr->year_of_deliver);
    check_for_date_of_deliver(ptr);

    //add amount of storage place for category
    printf("\nEnter storage place for category:");
    scanf_s("%d", &ptr->amount_of_storage_space_for_category);
    check_for_storage_place(ptr);

}

void check_for_expiration_date(product *ptr){

    if(ptr->day_expiration <= 0 || ptr->day_expiration > 31){
        printf("\nWrong data. ");

        do {
            printf("Write correct day:");
            scanf_s("%d", &ptr->day_expiration);
        } while (ptr->day_expiration <= 0 || ptr->day_expiration > 31);

        if(ptr->day_expiration > 0 && ptr->day_expiration < 31){
            printf("New data saved\n");
        }
    }
    if(ptr->month_expiration <= 0 || ptr->month_expiration > 12){
        printf("\nWrong data. ");

        do {
            printf("Write correct month:");
            scanf_s("%d", &ptr->month_expiration);
        } while (ptr->month_expiration <= 0 || ptr->month_expiration > 12);

        if(ptr->month_expiration > 0 && ptr->month_expiration < 12){
            printf("New data saved\n");
        }
    }
    if(ptr->year_expiration <= 0){
        printf("\nWrong data. ");

        do {
            printf("Write correct year:");
            scanf_s("%d", &ptr->year_expiration);
        } while (ptr->year_expiration <= 0);

        if(ptr->year_expiration > 0){
            printf("New data saved\n");
        }
    }

}

void check_for_date_of_deliver(product *ptr){

    if(ptr->day_of_deliver <= 0 || ptr->day_of_deliver > 31){
        printf("\nWrong data. ");

        do {
            printf("Write correct day:");
            scanf_s("%d", &ptr->day_of_deliver);
        } while (ptr->day_of_deliver <= 0 || ptr->day_of_deliver > 31);

        if(ptr->day_of_deliver > 0 && ptr->day_of_deliver < 31){
            printf("New data saved\n");
        }
    }
    if(ptr->month_of_deliver <= 0 || ptr->month_of_deliver > 12){
        printf("\nWrong data. ");

        do {
            printf("Write correct month:");
            scanf_s("%d", &ptr->month_of_deliver);
        } while (ptr->month_of_deliver <= 0 || ptr->month_of_deliver > 12);

        if(ptr->month_of_deliver > 0 && ptr->month_of_deliver < 12){
            printf("New data saved\n");
        }
    }
    if(ptr->year_of_deliver <= 0){
        printf("\nWrong data. ");

        do {
            printf("Write correct year:");
            scanf_s("%d", &ptr->year_of_deliver);
        } while (ptr->year_of_deliver <= 0);

        if(ptr->year_of_deliver > 0){
            printf("New data saved\n");
        }
    }
}

void check_for_storage_place(product *ptr){

    if(ptr->amount_of_storage_space_for_category < ptr->amount_in_storage){
        printf("Amount of storage place can't be less than amount in storage\n");
        printf("Write more than or equal to %d amount in storage: ", ptr->amount_in_storage);
        do {
            scanf_s("%d", &ptr->amount_of_storage_space_for_category);
        }while(ptr->amount_of_storage_space_for_category < ptr->amount_in_storage);
        if(ptr->amount_of_storage_space_for_category > ptr->amount_in_storage){
            printf("New data saved\n");
        }
    }

    if(ptr->amount_of_storage_space_for_category < 0){
        printf("\nWrong data. ");

        do {
            printf("Write correct storage place for category:");
            scanf_s("%d", &ptr->amount_of_storage_space_for_category);
        } while (ptr->amount_of_storage_space_for_category < 0 );

        if(ptr->amount_of_storage_space_for_category > 0){
            printf("New data saved\n");
        }
    }

}

void update_data(){

    if (head == NULL)
    {
        printf ("List is empty\n");
        return;
    }

    int count = 0;
    count = node_count(head, count);
    int number_of_node;

    //count =node_count(count);
    printf("COUNT %d", count);
    printf ("\nData of which product you want to edit: ");
    scanf_s ("%d", &number_of_node);

    //check
    number_of_node = check_for_amount_of_nodes(number_of_node, count);
    printf("\nN = %d", number_of_node);

    //printf("\nIt's data now:\n");
    product *tmp = head;
    product *temp = head;
    int i = 1;
    while (tmp != NULL)
    {
        if (i == number_of_node)
        {
            temp = tmp;
        }
        i++;
        tmp = tmp->next;
    }

    printf("\nEnter new data:");
    product *ptr = temp;
    write_data(ptr);
    printf ("\nData is successfully saved");

    pauseConsole();
    system("cls");
}

void delete_node(product **head){
    int position;

    position = position_for_deleting();

    product *current = *head;
    product *previous = *head;

    if(*head == NULL){
        printf("\nList is empty\n");
    }
    else if (position == 1){
        *head = current->next;
        free(current);
        current = NULL;
    }
    else{
        while (position != 1){
            previous = current;
            current = current->next;
            position--;
        }
        previous->next = current->next;
        free(current);
        current = NULL;
    }
    printf("\nProduct has been deleted\n");
    pauseConsole();
    system("cls");
}

int check_for_amount_of_nodes(int number_of_node, int count){
    if(number_of_node > count || number_of_node < 0 ){
        printf("\nWrong number of node\n");
        printf("Enter right number of node:");
        scanf_s("%d", &number_of_node);

        if(number_of_node < count && number_of_node != 0 ){
            printf("\nData saved");
             //return number_of_node;
        }

        //making pointer on function to involve her again in case if number is still wrong
        else{
            int (*ptr_check_for_amount_of_nodes) (int, int);
            ptr_check_for_amount_of_nodes = check_for_amount_of_nodes;
            ptr_check_for_amount_of_nodes(number_of_node,count);
        }
    }
    return number_of_node;
}

int position_for_deleting(){
    int count = 0;
    count = node_count(head, count);
    int number_of_node;

    printf("COUNT %d", count);
    printf ("\nEnter position of node:\n ");
    scanf_s ("%d", &number_of_node);

    //check
    number_of_node = check_for_amount_of_nodes(number_of_node, count);
    int position = number_of_node;
    return position;
}

int check_for_position_of_nodes(int position, int count){
    if(position > count || position < 0 ){
        printf("\nWrong number of node\n");
        printf("Enter right number of node:");
        scanf_s("%d", &position);

        if(position < count && position != 0 ){
            printf("\nData saved");
            return position;
        }

            //making pointer on function to involve her again in case if number is still wrong
        else{
            int (*ptr_check_for_position_of_nodes) (int, int);
            ptr_check_for_position_of_nodes = check_for_position_of_nodes;
            ptr_check_for_position_of_nodes(position,count);
        }
    }
    return 0;
}

int node_count(product *head, int count){
    //int count = 0 ;
    if(head == NULL){
        printf("\nList is empty\n");
    }
    product *ptr = NULL;
    ptr = head;
    while(ptr != NULL){
        count++;
        ptr = ptr->next;
    }
    printf("Amount of products: %d", count);
    return count;
}

void print_data_with_current_date(){

    int day_cur, month_cur, year_cur; //current date
    printf("\nEnter current date: \n");
    printf("Day:");
    scanf_s("%d", &day_cur);
    printf("Month:");
    scanf_s("%d", &month_cur);
    printf("Year:");
    scanf_s("%d", &year_cur);

    //check for mistakes
    day_cur = check_for_current_date(day_cur, month_cur, year_cur);
    month_cur = check_for_current_date(day_cur, month_cur, year_cur);
    year_cur = check_for_current_date(day_cur, month_cur, year_cur);

    //printf current date
    printf("Current date: Day:%d, Month:%d, Year:%d", day_cur, month_cur, year_cur);

    if (head == NULL) {
        printf("LIST IS EMPTY! \n\n");
        return;
    }

    product *tmp = head;

    while (tmp != NULL) {
        if(tmp->day_expiration < day_cur || tmp->month_expiration < month_cur || tmp->year_expiration < year_cur) {

            printf("\nList of product with EXPIRED DATE\n");
            printf("-----------------\n");
            printf("NAME: %s\n", tmp->name);
            printf("CATEGORY: %s\n", tmp->category);
            printf("AMOUNT IN STORAGE: %d\n", tmp->amount_in_storage);
            printf("EXPIRATION DATE: Day:%d, Month:%d, Year:%d\n", tmp->day_expiration, tmp->month_expiration,
                   tmp->year_expiration);
            printf("DATE OF DELIVER: Day:%d, Month:%d, Year:%d\n", tmp->day_of_deliver, tmp->month_of_deliver,
                   tmp->year_of_deliver);
            printf("AMOUNT OF STORAGE PLACE FOR CATEGORY: %d\n", tmp->amount_of_storage_space_for_category);
            printf("-----------------\n");
        }
        tmp = tmp->next;
    }
    pauseConsole();
    system("cls");
}

void search_by_category(){
    char search_category[80];
    product *tmp = head;

    if (head == NULL) {
        printf("LIST IS EMPTY! \n\n");
        return;
    }

    printf("SEARCH PRODUCTS BY CATEGORY\n");
    //printf("Printing categories:\n");
    //print_cat(tmp);
    printf("\nEnter category:");
    scanf("%s", search_category);

    while (tmp != NULL) {
        if(strcmp(search_category, tmp->category) == 0) {

            printf("-----------------\n");
            printf("List of product with %s category\n", search_category);
            printf("NAME: %s\n", tmp->name);
            printf("CATEGORY: %s\n", tmp->category);
            printf("AMOUNT IN STORAGE: %d\n", tmp->amount_in_storage);
            printf("EXPIRATION DATE: Day:%d, Month:%d, Year:%d\n", tmp->day_expiration, tmp->month_expiration, tmp->year_expiration);
            printf("DATE OF DELIVER: Day:%d, Month:%d, Year:%d\n", tmp->day_of_deliver, tmp->month_of_deliver, tmp->year_of_deliver);
            printf("AMOUNT OF STORAGE PLACE FOR CATEGORY: %d\n", tmp->amount_of_storage_space_for_category);
            printf("-----------------\n");
        }
        else{
            int choice;
            printf("\nWrong category\n");
            printf("Do you want to try again?(1-yes, 2-no)");
            scanf_s("%d", &choice);
            if(choice == 1){
                void (*func) ();
                func = search_by_category;
                func();
                return;
            }
        }
            tmp = tmp->next;
    }
    pauseConsole();
    system("cls");
}

void print_cat(product *tmp){
    tmp = head;
   while(tmp != NULL){
       if(strcmp(tmp->category, tmp->category) == 0){
           strcpy(tmp->category, tmp->category);
           printf("CATEGORY: %s\n", tmp->category);
       }

       tmp = tmp->next;
   }
}

int check_for_current_date(int day_cur, int month_cur, int year_cur){
    //check for current date

    if(day_cur <= 0 || day_cur > 31){
        printf("\nWrong data. ");

        do {
            printf("Write correct day:");
            scanf_s("%d", &day_cur);
        } while (day_cur <= 0 || day_cur > 31);

        if(day_cur> 0 && day_cur < 31){
            printf("New data saved\n");
        }
        return day_cur;
    }
    if(month_cur <= 0 || month_cur > 12){
        printf("\nWrong data. ");

        do {
            printf("Write correct month:");
            scanf_s("%d", &month_cur);
        } while (month_cur <= 0 || month_cur > 12);

        if(month_cur > 0 && month_cur < 12){
            printf("New data saved\n");
        }
        return month_cur;
    }
    if(year_cur <= 0){
        printf("\nWrong data. ");

        do {
            printf("Write correct year:");
            scanf_s("%d", &year_cur);
        } while (year_cur <= 0);

        if(year_cur > 0){
            printf("New data saved\n");
        }
        return year_cur;
    }
    return 0;
}

void empty_store_place() {
    char name_of_product[80];

    product *tmp = head;

    if (head == NULL) {
        printf("LIST IS EMPTY! \n\n");
        return;
    }

    //printf("Printing categories:\n");
    //print_cat(tmp);
    printf("\nEnter name of product:");
    scanf("%s", name_of_product);

    while (tmp != NULL) {
        if (strcmp(name_of_product, tmp->name) == 0) {
            int empty_space;
            empty_space = tmp->amount_of_storage_space_for_category - tmp->amount_in_storage;

            printf("-----------------\n");
            printf("List of product with %s category\n", name_of_product);
            printf("NAME: %s\n", tmp->name);
            printf("EMPTY STORAGE PLACE: %d", empty_space);
        } else {
            int choice;
            printf("\nWrong category\n");
            printf("Do you want to try again?(1-yes, 2-no)");
            scanf_s("%d", &choice);
            if (choice == 1) {
                void (*empty_sp_ptr)();
                empty_sp_ptr = empty_store_place;
                empty_sp_ptr();
                return;
            }
        }
        tmp = tmp->next;
    }
    pauseConsole();
    system("cls");
}

void search_by_list_of_products() {

    char **strings;
    int amount;//amount of products

    printf("Enter amount of products in list:");
    scanf_s("%d", &amount);

    strings = malloc(amount * sizeof(char *));

    char buffer[BUFFER_SIZE];
    int length = 0;

    while (getchar() != '\n');

    printf("\n");
    for (int i = 0; i < amount; ++i) {
        printf("Enter product %d (products that not in list won't be printed):", i + 1);
        fgets(buffer, BUFFER_SIZE, stdin);
        length = strlen(buffer);
        buffer[length - 1] = '\0';
        strings[i] = malloc(length * sizeof(char));
        strcpy(strings[i], buffer);
    }
    printf("Result:");
    for (int i = 0; i < amount; i++) {
        printf("Product %d: %s\n", i + 1, strings[i]);
    }
    printf("\n");

    product *tmp = head;

    if (head == NULL) {
        printf("LIST IS EMPTY! \n\n");
        return;
    }

    while (tmp != NULL) {
        for (int i = 0; i < amount; ++i) {
            if (strcmp(strings[i], tmp->name) == 0) {

                printf("-----------------\n");
                printf("NAME: %s\n", tmp->name);
                printf("AMOUNT IN STORAGE: %d\n", tmp->amount_in_storage);
                printf("-----------------\n");
            }
        }
        tmp = tmp->next;
    }

    free(strings);
    pauseConsole();
    system("cls");
}

void sorting() {

   product *tmp = head, *index = NULL;
   int temp1, temp2, temp3;


   if(head == NULL){
       printf("\nList is empty\n");
       return;
   }

    while (tmp != NULL) {
        index = tmp->next;

        while (index != NULL) {
            if (tmp->day_of_deliver > index->day_of_deliver) {
  
                temp1 = tmp->day_of_deliver;
                tmp->day_of_deliver = index->day_of_deliver;
                index->day_of_deliver = temp1;

            }
            if(tmp->month_of_deliver > index->month_of_deliver){
                temp2 = tmp->month_of_deliver;
                tmp->month_of_deliver = index->month_of_deliver;
                index->month_of_deliver = temp2;
            }
            if(tmp->year_of_deliver > index->year_of_deliver){
                temp3 = tmp->year_of_deliver;
                tmp->year_of_deliver = index->year_of_deliver;
                index->year_of_deliver = temp3;
            }

            index = index->next;
        }
        tmp = tmp->next;
    }


    printf("List has been sorted\n");
    pauseConsole();
    system("cls");
}

void pauseConsole() {
    printf("\n\nPress any key to continue...");
    while (getchar() != '\n');
    getchar();
}
