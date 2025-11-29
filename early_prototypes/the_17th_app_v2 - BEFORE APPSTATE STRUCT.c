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

bool warning_prompt() {
    char input[200];

    printf("\nWarning! You are about to change a critical part of The 17th App (C Rewrite)!\n");
    printf("\nOverride warning?\n");

    // Gets the answer.
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0';

    if (strcmp(input, "yes") == 0 || strcmp(input, "override") == 0) {
        return true;
    }

    else {
        return false;
    }

}

bool ends_with_txt(const char *str) {
    size_t len = strlen(str);
    if (len < 4) {
        return false; // Too short to end with ".txt".
    }

    return strcmp(str + (len - 4), ".txt") == 0;
}

char *name_of_item(int id) {
    for (int i = 0; i < menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].name;
        }
    }
    return "unknown";
}

void debug_mode(struct Order all_orders[], int *order_count, struct Menu *menu, struct Order *order, int *tax_pointer, bool *warning_pointer) {
    char input[200];
    char secondary_input[200];
    bool debugging = true;
    bool show_debug_commands = true;

    struct Order *order_pointer = order;

    if (show_debug_commands) {
        show_command();
    }

    while (debugging) {
        printf("\nEnter command (non-functional at the moment):\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/exit") == 0) {
            debugging = false;
            continue;
        }

        tokenize(input, order_pointer);

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == RESET_ORDER) {
            if (*warning_pointer) {
                if (warning_prompt()) {
                    *order_count = 0;
                    printf("\nThe order has been reset.\n");
                }
            }

            else {
                *order_count = 0;
                printf("\nThe order has been reset.\n");
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == SHOW_TAX) {
            printf("\nThe current tax rate is $%.2f.\n", *tax_pointer / 100.0);
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == CHANGE_TAX) {
            if (*warning_pointer) {
                if (warning_prompt()) {
                    printf("\nChange the current tax rate to?\n");
                    scanf("%d", tax_pointer);

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {
                        ; // Discards the character to fix a glitch.
                    }

                    printf("\nThe new tax rate is $%.2f.\n", *tax_pointer / 100.0);
                }
            }

            else {
                printf("\nChange the current tax rate to?\n");
                scanf("%d", tax_pointer);

                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                    ; // Discards the character to fix a glitch.
                }

                printf("\nThe new tax rate is $%.2f.\n", *tax_pointer / 100.0);
            }

        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == CHANGE_MENU) {
            if (*warning_pointer) {
                if (warning_prompt()) {
                    printf("\nChange the current menu to?\n");

                    fgets(secondary_input, sizeof(secondary_input), stdin);
                    secondary_input[strcspn(secondary_input, "\n")] = '\0';

                    if (ends_with_txt(secondary_input)) {
                        menu_count = 0;

                        loaded = load_menu_file(secondary_input);

                        printf("\nLoaded new dynamic items: %d\n", menu_count);
                        for (int i = 0; i < menu_count; i++) {
                            printf(" -> %s / id=%d / price=%d\n", dynamic_menu_items[i].name, dynamic_menu_items[i].id, dynamic_menu_items[i].price);
                        }
                    }

                    else {
                        printf("\n%s does not end with '.txt'.\n", secondary_input);
                    }
                }

                else {
                    printf("\nChange the current menu to?\n");

                    fgets(secondary_input, sizeof(secondary_input), stdin);
                    secondary_input[strcspn(secondary_input, "\n")] = '\0';

                    if (ends_with_txt(secondary_input)) {
                        menu_count = 0;

                        loaded = load_menu_file(secondary_input);

                        printf("\nLoaded new dynamic items: %d\n", menu_count);
                        for (int i = 0; i < menu_count; i++) {
                            printf(" -> %s / id=%d / price=%d\n", dynamic_menu_items[i].name, dynamic_menu_items[i].id, dynamic_menu_items[i].price);
                        }
                    }

                    else {
                        printf("\n%s does not end with '.txt'.\n", secondary_input);
                    }
                }
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == WARNING_MODE) {
            printf("\n0 = False, 1 = True.\n");
            printf("\nWarning Mode is set %d.", *warning_pointer);
            printf("\nYou are about to change warning to its opposite value.\n");
            printf("\nType 'true' or 'false' for your selection.\n");

            // Gets the answer.
            fgets(secondary_input, sizeof(secondary_input), stdin);
            secondary_input[strcspn(secondary_input, "\n")] = '\0';

            if (strcmp(secondary_input, "true") == 0) {
                *warning_pointer = true;
                printf("\nWarning Mode set to True.\n");
            }

            else {
                *warning_pointer = false;
                printf("\nWarning Mode set to False.\n");
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && (order->debug == SHOW_COMMANDS || order->debug == HELP )) {
            show_debug_commands = true;
            show_command();
        }
    }
}

void show_command() {
    printf("\nAvailable (Future) Commands:\n");
    printf("\n/add_item");
    printf("\n/sub_item");
    printf("\n/test_order");
    printf("\n/reset_order"); // Implemented.
    printf("\n/edit_order");
    printf("\n/edit_menu");
    printf("\n/edit_all");
    printf("\n/random_menu");
    printf("\n/random_order");
    printf("\n/restore_menu");
    printf("\n/show_command"); // Implemented.
    printf("\n/show_tax"); // Implemented.
    printf("\n/change_tax"); // Implemented.
    printf("\n/change_menu");
    printf("\n/warning_mode"); // Implemented.
    printf("\n/help"); // Implemented.
    printf("\n/exit\n"); // Implemented.
}

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
    if (order_count == 0) {
        printf("\nYour order is currently empty.\n");
        return;
    }

    printf("\nCurrent order:\n");

    for (int i = 0; i < order_count; i++) {
        struct Order o = all_orders[i];

        int price = get_item_price(o.item, menu);
        if (price < 0) {
            continue; // unknown item, skip
        }

        char printable[200];
        strcpy(printable, name_of_item(o.item));

        // Underscores turned into spaces.
        for (int j = 0; printable[j] != '\0'; j++) {
            if (printable[j] == '_') {
                printable[j] = ' ';
            }
        }

        pluralize(printable);

        if (o.size == SMALL) {
            printf("%d small %s - $%.2f\n", o.num, printable, (price * o.num) / 100.0);
        }

        else if (o.size == MEDIUM) {
            printf("%d medium %s - $%.2f\n", o.num, printable, (price * o.num) / 100.0);
        }

        else if (o.size == LARGE) {
            printf("%d large %s - $%.2f\n", o.num, printable, (price * o.num) / 100.0);
        }

        else if (o.size == PIECES) {
            printf("%d piece %s - $%.2f\n", o.num, printable, (price * o.num) / 100.0);
        }

        else if (o.size == 0) {
            printf("%d %s - $%.2f\n", o.num, printable, (price * o.num) / 100.0);
        }
    }
}

void pluralize(char phrase[200]) {
    int length = strlen(phrase);

    if (length == 0) {
        return;
    }

    // Finds the start of the last word.
    int last_space = -1;
    for (int i = 0; i < length; i++) {
        if (phrase[i] == ' ') {
            last_space = i;
        }
    }

    char *word = (last_space == -1) ? phrase : &phrase[last_space + 1];

    int word_len = strlen(word);

    // Special cases.
    if (strcmp(word, "fry") == 0) {
        strcpy(word, "fries");
        return;
    }

    if (strcmp(word, "sandwich") == 0) {
        strcpy(word, "sandwiches");
        return;
    }

    // Prevents double-plurals.
    if (word_len > 0 && word[word_len - 1] == 's') {
        return;
    }

    word[word_len] = 's';
    word[word_len + 1] = '\0';
}

void checkout(struct Order all_orders[], int order_count, struct Menu *menu, int *tax_pointer) {
    int price = 0;

    if (order_count == 0) {
        printf("\nYour order is currently empty.\n");
        return;
    }

    for (int i = 0; i < order_count; i++) {
        struct Order o = all_orders[i];

        int item_price = get_item_price(o.item, menu);
        int size_price = get_size_price(o.size);

        if (item_price < 0) {
            printf("Warning: Item ID %d not found.\n", o.item);
            continue;
        }

        // Price equals the item multiplied by quantity, size, and tax.
        int final_price = item_price + size_price;
        int base_cost = o.num * final_price;
        int tax_rate = *tax_pointer;

        int price_with_tax = base_cost * (100 + tax_rate) / 100;

        price += price_with_tax;

        // printf("\nDEBUG: item=%d size=%d num=%d\n", o.item, o.size, o.num);
    }

    printf("\nThe total will be $%.2f.\n", price / 100.0);
}

void add_item(struct Order all_orders[], int *order_count, struct Menu *menu, struct Order *order) {
    int price = get_item_price(order->item, menu);

    for (int i = 0; i < menu_count; i++) {
        if (order->item == dynamic_menu_items[i].id) {

            // Allocates a buffer to hold the name.
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

            // Tries to merge with existing orders.
            for (int k = 0; k < *order_count; k++) {
                if (all_orders[k].item == order->item &&
                    all_orders[k].size == order->size &&
                    all_orders[k].modifier == order->modifier) {

                    // Found a matching order, so it merges.
                    all_orders[k].num += order->num;

                if (order->size == SMALL) {
                    printf("\nAdded %d more small %s!\n", order->num, printable);
                }

                else if (order->size == MEDIUM) {
                    printf("\nAdded %d more medium %s!\n", order->num, printable);
                }

                else if (order->size == LARGE) {
                    printf("\nAdded %d more large %s!\n", order->num, printable);
                }

                else if (order->size == PIECES) {
                    printf("\nAdded even more %d piece %s!\n", order->num, printable);
                }

                else {
                    printf("\nAdded %d %s!\n", order->num, printable);
                }

                return;
                }
            }

            all_orders[*order_count] = *order;
            (*order_count)++;

            if (order->size == SMALL) {
                printf("\nAdded %d small %s!\n", order->num, printable);
            }

            else if (order->size == MEDIUM) {
                printf("\nAdded %d medium %s!\n", order->num, printable);
            }

            else if (order->size == LARGE) {
                printf("\nAdded %d large %s!\n", order->num, printable);
            }

            else if (order->size == PIECES) {
                printf("\nAdded %d piece %s!\n", order->num, printable);
            }

            else {
                printf("\nAdded %d %s!\n", order->num, printable);
            }
            return;
        }
    }
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
    int price = match_dynamic_item_id(id);

    if (price >= 0) {
        return price;  // It was found dynamically.
    }

    // Fallsback to the hardcoded menu.
    switch (id) {
        case FRIES:           return fallback_menu->fries;
        case BURGER:          return fallback_menu->burger;
        case CHEESEBURGER:    return fallback_menu->cheeseburger;
        case NUGGETS:         return fallback_menu->nuggets;
        case CHICKEN_SANDWICH:return fallback_menu->chicken_sandwich;
        case WINGS:           return fallback_menu->wings;
        case ONION_RINGS:     return fallback_menu->onion_rings;
        case HOTDOG:          return fallback_menu->hotdog;
        case HOUSE_SALAD:     return fallback_menu->house_salad;
        case CAESAR_SALAD:    return fallback_menu->caesar_salad;
        case SODA:            return fallback_menu->soda;
        case CHOCOLATE_MILK:  return fallback_menu->chocolate_milk;
        case WHITE_MILK:      return fallback_menu->white_milk;
        case JUICE:           return fallback_menu->juice;
        case WATER:           return fallback_menu->water;
    }

    return -1; // Not found at all.
}

int get_size_price(int size) {
    if (size == SMALL) {
        int size_price = -50;
        return size_price;
    }

    else if (size == MEDIUM || size == PIECES) {
        int size_price = 50;
        return size_price;
    }

    else if (size == LARGE) {
        int size_price = 100;
        return size_price;
    }

    else {
        // printf("\nError: Size does not exist!\n");
        return 0;
    }

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

    int *tax_pointer = &tax;

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
    bool warning = true;

    bool *warning_pointer = &warning;

    if (menu_question) {
        printf("Hello and welcome to The 17th App! Hot new place in town, yeah?\n");
        printf("Would you like to see the menu?\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Removes the newline.

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

        if (strcmp(input, "show menu") == 0) {
            show_menu(menu);
            continue;
        }

        if (strcmp(input, "checkout") == 0 || strcmp(input, "done") == 0) {
            checkout(all_orders, order_count, &menu, tax_pointer);
            continue;
        }

        tokenize(input, order_pointer);

        if (order.num == 0 && order.item > 0) {
            order.num = 1;
        }

        if ((order.num > 0 || order.size > 0 || order.item > 0 || order.modifier > 0) && order.debug == 0) {
            add_item(all_orders, &order_count, &menu, &order);
        }

        if ((order.num == 0 && order.size == 0 && order.item == 0 && order.modifier == 0) && order.debug == ENTER) {
            debug = true;
            printf("\nDebug mode enabled!\n");
            debug_mode(all_orders, &order_count, &menu, &order, tax_pointer, warning_pointer);
        }

    }

    return 0;
}
