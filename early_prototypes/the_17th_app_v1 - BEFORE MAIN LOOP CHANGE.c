#include "c-ya_tokenizer.h"
#include <stdio.h>
#include <string.h>
#include "the17th.h"

struct Dynamic_Menu dynamic_menu_items[50];
int menu_count = 0;

struct Menu make_menu();

struct Menu make_menu() {
    struct Menu menu;

    menu.burger = 399;
    menu.cheeseburger = 429;
    menu.nuggets = 299;
    menu.tenders = 429;
    menu.chicken_sandwich = 399;
    menu.wings = 499;
    menu.onion_rings = 299;
    menu.hotdog = 199;
    menu.fries = 299;
    menu.house_salad = 900;
    menu.caesar_salad = 900;
    menu.soda = 129;
    menu.chocolate_milk = 99;
    menu.white_milk = 99;
    menu.juice = 129;
    menu.water = 99;

    return menu;
}

char *name_of_item(int id) {
    for (int i = 0; i < menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].name;
        }
    }
    return "unknown";
}

/*

char *size_of_item(int id) {
    for (int i = 0; i < menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].name;
        }
    }
    return "unknown";
}

*/

void show_menu(struct Menu menu) {
    printf("\nBurger: $%.2f\n", menu.burger / 100.0);
    printf("\nCheeseburger: $%.2f\n", menu.cheeseburger / 100.0);
    printf("\nNuggets: $%.2f\n", menu.nuggets / 100.0);
    printf("\nTenders: $%.2f\n", menu.tenders / 100.0);
    printf("\nChicken Sandwich: $%.2f\n", menu.chicken_sandwich / 100.0);
    printf("\nWings: $%.2f\n", menu.wings / 100.0);
    printf("\nOnion Rings: $%.2f\n", menu.onion_rings / 100.0);
    printf("\nHotdog: $%.2f\n", menu.hotdog / 100.0);
    printf("\nFries: $%.2f\n", menu.fries / 100.0);
    printf("\nHouse Salad: $%.2f\n", menu.house_salad / 100.0);
    printf("\nCaesar Salad: $%.2f\n", menu.caesar_salad / 100.0);
    printf("\nSoda: $%.2f\n", menu.soda / 100.0);
    printf("\nChocolate Milk: $%.2f\n", menu.chocolate_milk / 100.0);
    printf("\nWhite Milk: $%.2f\n", menu.white_milk / 100.0);
    printf("\nJuice: $%.2f\n", menu.juice / 100.0);
    printf("\nWater: $%.2f\n", menu.water / 100.0);
}

void show_order(struct Order all_orders[], int order_count, struct Menu *menu) {
    for (int i = 0; i < order_count; i++) {
        struct Order o = all_orders[i];

        int price = get_item_price(o.item, menu);

        printf("%d x %s - %.2f\n",
               o.num,
               name_of_item(o.item),
               price / 100.0);
    }
}

void pluralize(char word[200]) {
    int length = strlen(word);

    if (strcmp(word, "fry") == 0) {
        strcpy(word, "fries");
        return;
    }

    if (strcmp(word, "sandwich") == 0) {
        strcpy(word, "sandwiches");
        return;
    }

    // Prevents double-plurals.
    if (length > 0 && word[length - 1] == 's') {
        return;
    }

    word[length] = 's'; // Add 's' at the end.
    word[length + 1] = '\0'; // Null-terminates properly.
}

int load_menu_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 0; // The file is missing.
    }

    char name[200];
    int price;

    while (fscanf(file, "%199[^=]=%d\n", name, &price) == 2) {

        // Singularizes the name to be correct.
        char *pointer = name;
        singularize(pointer);

        //
        char name_copy[200];
        strcpy(name_copy, name);

        // split on '_' into words[]
        char *words[10];
        int count = 0;

        char *token = strtok(name_copy, "_");
        while (token && count < 10) {
            words[count++] = token;
            token = strtok(NULL, "_");
        }

        int id = parse_item_words(words, count);

        // Generates a unique ID based on the ASCII hashing method.
        // int id = ascii_word(name) + ITEM_CONST;

        // Stores it into the runtime table.
        strcpy(dynamic_menu_items[menu_count].name, name);
        dynamic_menu_items[menu_count].id = id;
        dynamic_menu_items[menu_count].price = price;
        menu_count++;
    }

    fclose(file);
    return 1; // Shows it was successful.
}

int get_item_price(int id, struct Menu *fallback_menu) {
    // Searches the dynamic menu first.
    for (int i = 0; i < menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].price;
        }
    }

    // Fallsback to the hardcoded menu if the dynamic menu file didn't contain the item.
    switch (id) {
        case FRIES: return fallback_menu->fries;
        case BURGER: return fallback_menu->burger;
        case CHEESEBURGER: return fallback_menu->cheeseburger;
        case NUGGETS: return fallback_menu->nuggets;
        case CHICKEN_SANDWICH: return fallback_menu->chicken_sandwich;
        case WINGS: return fallback_menu->wings;
        case ONION_RINGS: return fallback_menu->onion_rings;
        case HOTDOG: return fallback_menu->hotdog;
        case HOUSE_SALAD: return fallback_menu->house_salad;
        case CAESAR_SALAD: return fallback_menu->caesar_salad;
        case SODA: return fallback_menu->soda;
        case CHOCOLATE_MILK: return fallback_menu->chocolate_milk;
        case WHITE_MILK: return fallback_menu->white_milk;
        case JUICE: return fallback_menu->juice;
        case WATER: return fallback_menu->water;
    }

    // Error: The item wasn't found anywhere.
    return -1;
}

// Returns price if the ID exists dynamically, otherwise returns -1.
int match_dynamic_item_id(int id) {
    for (int i = 0; i < menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].price;
        }
    }
    return -1;
}

int main() {
    int total = 0, tax = 7;

    char input[200];
    struct Order order;

    struct Order *order_pointer = &order;

    struct Order all_orders[100];
    int order_count = 0;

    struct Menu menu = make_menu();  // ALWAYS initialize fallback
    int loaded = load_menu_file("menu.txt");

    printf("\nLoaded dynamic items: %d\n", menu_count);
    for (int i = 0; i < menu_count; i++) {
        printf(" -> %s / id=%d / price=%d\n",
               dynamic_menu_items[i].name,
               dynamic_menu_items[i].id,
               dynamic_menu_items[i].price
        );
    }

    bool menu_question = false;
    bool debug = true;
    bool running = true;

    if (menu_question) {
        printf("Hello and welcome to The 17th App! Hot new place in town, yeah?\n");
        printf("Would you like to see the menu?\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // remove newline

        if (strcmp(input, "yes") == 0) {
            show_menu(menu);
        }

        else if (strcmp(input, "no") == 0) {
            ;
        }

        memset(input, 0, sizeof(input)); // Resets the array.
    }

    while (running) {
        printf("\nWhat would you like to order?\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "quit") == 0) {
            running = false;
            continue;
        }

        if (strcmp(input, "show order") == 0) {
            show_order(all_orders, order_count, &menu);
            continue;
        }

        tokenize(input, order_pointer);

        if (order.debug == ENTER) {
            debug = true;
            printf("\nDebug mode enabled!\n");
        }

        if (debug) {
            if (order.debug == CHANGE_MENU) {

                // Flushes the old menu.
                menu_count = 0;

                loaded = load_menu_file("mexican_menu.txt");

                printf("\nLoaded dynamic items: %d\n", menu_count);
                for (int i = 0; i < menu_count; i++) {
                    printf(" -> %s / id=%d / price=%d\n",
                           dynamic_menu_items[i].name,
                           dynamic_menu_items[i].id,
                           dynamic_menu_items[i].price
                    );
                }
            }
        }

        printf("\nFinal numeric tokens:\n");
        printf("num = %d\n", order.num);
        printf("size = %d\n", order.size);
        printf("item = %d\n", order.item);
        printf("modifier = %d\n", order.modifier);
        printf("debug = %d\n", order.debug);

        int price = get_item_price(order.item, &menu);

        for (int i = 0; i < menu_count; i++) {
            if (order.item == dynamic_menu_items[i].id) {

                // Allocate a buffer to hold the name.
                char printable[200];
                strcpy(printable, dynamic_menu_items[i].name);

                // Replaces the underscores with spaces.
                for (int j = 0; printable[j] != '\0'; j++) {
                    if (printable[j] == '_') {
                        printable[j] = ' ';
                    }
                }

                // Pluralizes the final word only.
                pluralize(printable);

                all_orders[order_count++] = order;

                printf("\nFakely added %d %s!\n", order.num, printable);
            }
        }

        if (price != -1) {
            total += order.num * price;
            printf("\nAdded %d x item (ID %d). Price each: %.2f\n",
                   order.num, order.item, price / 100.0);
        }

        else {
            printf("\nUnknown item! Try again.\n");
        }

    }

    return 0;
}
