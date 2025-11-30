#include "c-ya_tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <time.h> // Added to include the new "/time" command.
#include "the17th.h"

struct Dynamic_Menu dynamic_menu_items[50];

struct Menu make_menu();
struct AppState make_app_state();

struct AppState make_app_state() {
    struct AppState app;

    app.menu_question = false;
    app.debug = true;
    app.debugging = true;
    app.show_debug_commands = true;
    app.running = true;
    app.warning = false;
    app.hard_coded_menu = false;
    app.safe_mode = false;
    app.tax = 7;
    app.menu_count = 0;
    app.order_count = 0;
    app.loaded_menu = 0;
    app.start_time = 0.0;
    app.elapsed_seconds = 0.0;

    return app;
}

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

bool warning_prompt(struct AppState *app) {
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

char *name_of_item(int id, struct AppState *app) {
    for (int i = 0; i < app->menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].name;
        }
    }
    return "unknown";
}

void *decode_modifier(char *decoded_mod_pointer_1, char *decoded_mod_pointer_2, char *decoded_mod_pointer_3, struct Order order) {
    // Uses a single switch statement on the combined enum values.
    switch (order.modifier) {
        case DELUXE:
            strcpy(decoded_mod_pointer_1, "deluxe");
            break;

        case MEAL:
            strcpy(decoded_mod_pointer_1, "meal");
            break;

        case SPICY:
            strcpy(decoded_mod_pointer_1, "spicy");
            break;

        case EXTRA:
            strcpy(decoded_mod_pointer_1, "extra");
            break;

        case DOUBLE:
            strcpy(decoded_mod_pointer_1, "double");
            break;

        case TRIPLE:
            strcpy(decoded_mod_pointer_1, "triple");
            break;

            // (Two) Combined modifiers.
        case DELUXE_MEAL:
            strcpy(decoded_mod_pointer_1, "deluxe");
            strcpy(decoded_mod_pointer_2, "meal");
            break;

        case SPICY_MEAL:
            strcpy(decoded_mod_pointer_1, "spicy");
            strcpy(decoded_mod_pointer_2, "meal");
            break;

            // (Three) Combined modifiers.
        case DELUXE_SPICY_MEAL:
            strcpy(decoded_mod_pointer_1, "deluxe");
            strcpy(decoded_mod_pointer_2, "spicy");
            strcpy(decoded_mod_pointer_3, "meal");
            break;

        default:
            // Handles the cases where the modifier is none of the defined values.
            strcpy(decoded_mod_pointer_1, "unknown");
            break;
    }
    return 0;
}

void debug_mode(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app) {
    char input[200];
    char secondary_input[200];

    struct Order *order_pointer = order;
    struct AppState *app_pointer = app;

    if (app->show_debug_commands) {
        show_command();
    }

    while (app->debugging) {
        printf("\nEnter command (getting more functional by the moment):\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/exit") == 0) {
            app->debugging = false;
            continue;
        }

        tokenize(input, order_pointer, app_pointer);

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == ADD_ITEM) {
            printf("\n(DEBUG) What would you like to add?\n");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            tokenize(input, order_pointer, app_pointer);

            if (order->num == 0 && order->item > 0) {
                order->num = 1;
            }

            if ((order->num > 0 || order->size > 0 || order->item > 0 || order->modifier > 0) && order->debug == 0) {
                add_item(all_orders, menu, order, app);
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == SUB_ITEM) {
            printf("\n(DEBUG) What would you like to remove?\n");
            printf("\n(Be as specific as possible, please.)\n");
            fgets(input, sizeof(input), stdin);
            input[strcspn(input, "\n")] = '\0';

            tokenize(input, order_pointer, app_pointer);

            if (order->num == 0 && order->item > 0) {
                order->num = 1;
            }

            if ((order->num > 0 || order->size > 0 || order->item > 0 || order->modifier > 0) && order->debug == 0) {
                sub_item(all_orders, menu, order, app);
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == RESET_ORDER) {
            if (app->warning) {
                if (warning_prompt(app)) {
                    app->order_count = 0;
                    printf("\nThe order has been reset.\n");
                }
            }

            else {
                app->order_count = 0;
                printf("\nThe order has been reset.\n");
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == SHOW_TAX) {
            printf("\nThe current tax rate is $%.2f.\n", app->tax / 100.0);
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == CHANGE_TAX) {
            if (app->warning) {
                if (warning_prompt(app)) {
                    printf("\nChange the current tax rate to?\n");
                    scanf("%d", &app->tax);

                    int c;
                    while ((c = getchar()) != '\n' && c != EOF) {
                        ; // Discards the character to fix a glitch.
                    }

                    printf("\nThe new tax rate is $%.2f.\n", app->tax / 100.0);
                }
            }

            else {
                printf("\nChange the current tax rate to?\n");
                scanf("%d", &app->tax);

                int c;
                while ((c = getchar()) != '\n' && c != EOF) {
                    ; // Discards the character to fix a glitch.
                }

                printf("\nThe new tax rate is $%.2f.\n", app->tax / 100.0);
            }

        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == CHANGE_MENU) {
            if (app->warning) {
                if (warning_prompt(app)) {
                    printf("\nChange the current menu to?\n");

                    fgets(secondary_input, sizeof(secondary_input), stdin);
                    secondary_input[strcspn(secondary_input, "\n")] = '\0';

                    if (ends_with_txt(secondary_input)) {
                        app->menu_count = 0;

                        app->loaded_menu = load_menu_file(secondary_input, app);

                        printf("\nLoaded new dynamic items: %d\n", app->menu_count);
                        for (int i = 0; i < app->menu_count; i++) {
                            printf(" -> %s / id=%d / price=%d\n", dynamic_menu_items[i].name, dynamic_menu_items[i].id, dynamic_menu_items[i].price);
                        }
                    }

                    else {
                        printf("\n%s does not end with '.txt'.\n", secondary_input);
                    }
                }
            }

            else {
                printf("\nChange the current menu to?\n");

                fgets(secondary_input, sizeof(secondary_input), stdin);
                secondary_input[strcspn(secondary_input, "\n")] = '\0';

                if (ends_with_txt(secondary_input)) {
                    app->menu_count = 0;

                    app->loaded_menu = load_menu_file(secondary_input, app);

                    printf("\nLoaded new dynamic items: %d\n", app->menu_count);
                    for (int i = 0; i < app->menu_count; i++) {
                        printf(" -> %s / id=%d / price=%d\n", dynamic_menu_items[i].name, dynamic_menu_items[i].id, dynamic_menu_items[i].price);
                    }
                }

                else {
                    printf("\n%s does not end with '.txt'.\n", secondary_input);
                }
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == CALCULATOR) {
            calculator_mode(order, app);
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == WARNING_MODE) {
            printf("\n0 = False, 1 = True.\n");
            printf("\nWarning Mode is set %d.", app->warning);
            printf("\nYou are about to change warning to its opposite value.\n");
            printf("\nType 'true' or 'false' for your selection.\n");

            // Gets the answer.
            fgets(secondary_input, sizeof(secondary_input), stdin);
            secondary_input[strcspn(secondary_input, "\n")] = '\0';

            if (strcmp(secondary_input, "true") == 0) {
                app->warning = true;
                printf("\nWarning Mode set to True.\n");
            }

            else {
                app->warning = false;
                printf("\nWarning Mode set to False.\n");
            }
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && order->debug == TIME) {
            show_upkeep_time(app);
        }

        if ((order->num == 0 && order->size == 0 && order->item == 0 && order->modifier == 0) && (order->debug == SHOW_COMMANDS || order->debug == HELP)) {
            app->show_debug_commands = true;
            show_command();
        }
    }
}

// Enters a while loop for infinite testing until told otherwise.
void calculator_mode(struct Order *order, struct AppState *app) {
    bool calc_running = true;

    char input[200];

    while (calc_running) {
        printf("\nPlease input the words you want calculated:\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "/exit") == 0) {
            break;
        }

        tokenize(input, order, app);

        printf("\nFinal numeric tokens:\n");

        printf("\nnum = %d\n", order->num);

        printf("\nsize(%d) + SIZE_CONST(%d) = %d\n", (SIZE_CONST - order->size), SIZE_CONST, order->size);

        printf("\nitem(%d) + ITEM_CONST(%d) = %d\n", (ITEM_CONST - order->item), ITEM_CONST, order->item);

        printf("\nmodifier(%d) + MODIFIER_CONST(%d) = %d\n", (MODIFIER_CONST - order->modifier),  MODIFIER_CONST, order->modifier);

        if (order->debug > 0) {
            printf("\ndebug(%d) + DEBUG_CONST(%d) = %d\n", (DEBUG_CONST - order->debug), DEBUG_CONST, order->debug);
        }

        else {
            printf("\ndebug(%d) + DEBUG_CONST(%d) = %d\n", 0, DEBUG_CONST, order->debug);
        }
    }
}

void show_upkeep_time(struct AppState *app) {
    clock_t current_time = clock();

    app->elapsed_seconds = ((double)clock() / CLOCKS_PER_SEC) - app->start_time;

    printf("\nThe System has been running for: %.2f seconds.\n", app->elapsed_seconds);
}

void show_command() {
    printf("\nAvailable (Future) Commands:\n");
    printf("\n/add_item"); // Implemented.
    printf("\n/sub_item"); // Implemented.
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
    printf("\n/change_menu"); // Implemented.
    printf("\n/calculator"); // Implemented.
    printf("\n/warning_mode"); // Implemented.
    printf("\n/time"); // Implemented.
    printf("\n/help"); // Implemented.
    printf("\n/exit\n"); // Implemented.
}

// Shows a hardcoded menu.
void show_hardcoded_menu(struct Menu menu) {
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

void show_order(struct Order all_orders[], struct Menu *menu, struct AppState *app) {
    if (app->order_count == 0) {
        printf("\nYour order is currently empty.\n");
        return;
    }

    printf("\nCurrent order:\n");

    for (int i = 0; i < app->order_count; i++) {
        struct Order o = all_orders[i];

        int price = get_item_price(o.item, menu, app);
        if (price < 0) {
            continue; // unknown item, skip
        }

        char printable[200];
        strcpy(printable, name_of_item(o.item, app));

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

void checkout(struct Order all_orders[], struct Menu *menu, struct AppState *app) {
    int price = 0;

    if (app->order_count == 0) {
        printf("\nYour order is currently empty.\n");
        return;
    }

    for (int i = 0; i < app->order_count; i++) {
        struct Order o = all_orders[i];

        int item_price = get_item_price(o.item, menu, app);
        int size_price = get_size_price(o.size);

        if (item_price < 0) {
            printf("Warning: Item ID %d not found.\n", o.item);
            continue;
        }

        // Price equals the item multiplied by quantity, size, and tax.
        int final_price = item_price + size_price;
        int base_cost = o.num * final_price;
        int tax_rate = app->tax;

        int price_with_tax = base_cost * (100 + tax_rate) / 100;

        price += price_with_tax;

        // printf("\nDEBUG: item=%d size=%d num=%d\n", o.item, o.size, o.num);
    }

    printf("\nThe total will be $%.2f.\n", price / 100.0);
}

void add_item(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app) {
    for (int i = 0; i < app->menu_count; i++) {
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
            for (int k = 0; k < app->order_count; k++) {
                if (all_orders[k].item == order->item && all_orders[k].size == order->size && all_orders[k].modifier == order->modifier) {
                    // Found a matching order, so it merges.
                    all_orders[k].num += order->num;

                    // If no modifier.
                    if (order->modifier == 0) {
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
                    }

                    else {
                        char decoded_modifier_1[20];
                        char decoded_modifier_2[20];
                        char decoded_modifier_3[20];

                        // Initializes to empty strings.
                        strcpy(decoded_modifier_1, "");
                        strcpy(decoded_modifier_2, "");
                        strcpy(decoded_modifier_3, "");

                        char *decoded_mod_pointer_1 = decoded_modifier_1;
                        char *decoded_mod_pointer_2 = decoded_modifier_2;
                        char *decoded_mod_pointer_3 = decoded_modifier_3;

                        decode_modifier(decoded_mod_pointer_1, decoded_mod_pointer_2, decoded_mod_pointer_3, *order);

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
                    }

                    return;
                }
            }

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

            else if (order->size == 0 && order->item == 0) {
                return;
            }

            else if (order->size == 0 && order->item != 0) {
                printf("\nAdded %d %s!\n", order->num, printable);
            }

            all_orders[app->order_count] = *order;
            (app->order_count)++;

            return;
        }
    }
}

void sub_item(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app) {
    for (int i = 0; i < app->menu_count; i++) {
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

            pluralize(printable);

            // Tries to find existing orders.
            for (int k = 0; k < app->order_count; k++) {
                if (all_orders[k].item == order->item && all_orders[k].size == order->size && all_orders[k].modifier == order->modifier) {

                    // Found a matching order, so it merges.
                    all_orders[k].num -= order->num;

                    if (all_orders[k].num <= 0) {

                        // Shifts everything left.
                        for (int i = k; i < app->order_count - 1; i++) {
                            all_orders[i] = all_orders[i + 1];
                        }

                        app->order_count--;
                    }

                if (order->size == SMALL) {
                    printf("\nRemoved %d more small %s!\n", order->num, printable);
                }

                else if (order->size == MEDIUM) {
                    printf("\nRemoved %d more medium %s!\n", order->num, printable);
                }

                else if (order->size == LARGE) {
                    printf("\nRemoved %d more large %s!\n", order->num, printable);
                }

                else if (order->size == PIECES) {
                    printf("\nRemoved even more %d piece %s!\n", order->num, printable);
                }

                else {
                    printf("\nRemoved %d %s!\n", order->num, printable);
                }

                return;
                    }
            }

            printf("\nYou don't have any %s to remove!\n", printable);
            return;
        }
    }
}

int load_menu_file(const char *filename, struct AppState *app) {
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

        // Generates a unique ID based on the ASCII hashing method.
        int id = parse_item_words(words, count);

        // Stores it into the runtime table (if applicable).
        if (app->menu_count < 50) {
            strcpy(dynamic_menu_items[app->menu_count].name, name);
            dynamic_menu_items[app->menu_count].id = id;
            dynamic_menu_items[app->menu_count].price = price;
            app->menu_count++;
        }

        else {
            fprintf(stderr, "Too many menu items, ignoring '%s'.\n", name);
        }
    }

    fclose(file);
    return 1; // Shows it was successful.
}

// Fixes a glitch I discovered with dynamic menus not loading.
void load_fallback_into_dynamic(struct Menu *menu, struct AppState *app) {
    app->menu_count = 0;

    strcpy(dynamic_menu_items[app->menu_count].name, "burger");
    dynamic_menu_items[app->menu_count].id = BURGER;
    dynamic_menu_items[app->menu_count].price = menu->burger;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "cheeseburger");
    dynamic_menu_items[app->menu_count].id = CHEESEBURGER;
    dynamic_menu_items[app->menu_count].price = menu->cheeseburger;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "nugget");
    dynamic_menu_items[app->menu_count].id = NUGGETS;
    dynamic_menu_items[app->menu_count].price = menu->nuggets;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "chicken_nugget");
    dynamic_menu_items[app->menu_count].id = CHICKEN_NUGGETS;
    dynamic_menu_items[app->menu_count].price = menu->nuggets;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "chicken_tender");
    dynamic_menu_items[app->menu_count].id = CHICKEN_TENDERS;
    dynamic_menu_items[app->menu_count].price = menu->tenders;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "chicken_sandwich");
    dynamic_menu_items[app->menu_count].id = CHICKEN_SANDWICH;
    dynamic_menu_items[app->menu_count].price = menu->chicken_sandwich;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "wing");
    dynamic_menu_items[app->menu_count].id = WINGS;
    dynamic_menu_items[app->menu_count].price = menu->wings;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "onion_ring");
    dynamic_menu_items[app->menu_count].id = ONION_RINGS;
    dynamic_menu_items[app->menu_count].price = menu->onion_rings;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "hotdog");
    dynamic_menu_items[app->menu_count].id = HOTDOG;
    dynamic_menu_items[app->menu_count].price = menu->hotdog;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "fry");
    dynamic_menu_items[app->menu_count].id = FRIES;
    dynamic_menu_items[app->menu_count].price = menu->fries;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "house_salad");
    dynamic_menu_items[app->menu_count].id = HOUSE_SALAD;
    dynamic_menu_items[app->menu_count].price = menu->house_salad;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "caesar_salad");
    dynamic_menu_items[app->menu_count].id = CAESAR_SALAD;
    dynamic_menu_items[app->menu_count].price = menu->caesar_salad;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "soda");
    dynamic_menu_items[app->menu_count].id = SODA;
    dynamic_menu_items[app->menu_count].price = menu->soda;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "chocolate_milk");
    dynamic_menu_items[app->menu_count].id = CHOCOLATE_MILK;
    dynamic_menu_items[app->menu_count].price = menu->chocolate_milk;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "white_milk");
    dynamic_menu_items[app->menu_count].id = WHITE_MILK;
    dynamic_menu_items[app->menu_count].price = menu->white_milk;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "juice");
    dynamic_menu_items[app->menu_count].id = JUICE;
    dynamic_menu_items[app->menu_count].price = menu->juice;
    app->menu_count++;

    strcpy(dynamic_menu_items[app->menu_count].name, "water");
    dynamic_menu_items[app->menu_count].id = WATER;
    dynamic_menu_items[app->menu_count].price = menu->water;
    app->menu_count++;
}

int get_item_price(int id, struct Menu *fallback_menu, struct AppState *app) {
    int price = match_dynamic_item_id(id, app);

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
int match_dynamic_item_id(int id, struct AppState *app) {
    for (int i = 0; i < app->menu_count; i++) {
        if (dynamic_menu_items[i].id == id) {
            return dynamic_menu_items[i].price;
        }
    }
    return -1;
}

int main() {
    struct AppState app = make_app_state();

    char input[200];
    struct Order order;

    struct Order *order_pointer = &order;
    struct AppState *app_pointer = &app;

    struct Order all_orders[100];

    struct Menu menu = make_menu(); // Initializes fallback.

    // Addded on 11-30-2025 at 11:25 AM to incorporate the "/time" command.
    app.start_time = (double)clock() / CLOCKS_PER_SEC;

    printf("\n(DEBUG) System online. Counting forevermore till shutdown.\n");

    // Tries to dynamically load the menu file.
    if (load_menu_file("default_menu.txt", &app) == 0 ||
        app.menu_count == 0) {

        printf("\nWARNING! Could not load default menu file. Falling back to hardcoded menu.\n");

        // Clear dynamic list
        app.menu_count = 0;

        // Changes the hard_coded_menu flag to true for the static menu.
        app.hard_coded_menu = true;

        load_fallback_into_dynamic(&menu, &app);
    }

    printf("\nLoaded dynamic items: %d\n", app.menu_count);
    for (int i = 0; i < app.menu_count; i++) {
        printf(" -> %s / id=%d / price=%d\n",
               dynamic_menu_items[i].name,
               dynamic_menu_items[i].id,
               dynamic_menu_items[i].price
        );
    }

    if (app.menu_question) {
        printf("Hello and welcome to The 17th App! Hot new place in town, yeah?\n");
        printf("Would you like to see the menu?\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';  // Removes the newline.

        if (strcmp(input, "yes") == 0) {
            if (app.hard_coded_menu) {
                show_hardcoded_menu(menu);
            }
        }

        else {
            ;
        }

        memset(input, 0, sizeof(input)); // Resets the array.
    }

    // /* Beginning of the main loop blockout section.

    // The main loop.
    while (app.running == true && app.safe_mode == false) {
        printf("\nWhat would you like to order?\n");
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "quit") == 0) {
            app.running = false;
            continue;
        }

        if (strcmp(input, "show order") == 0) {
            show_order(all_orders, &menu, &app);
            continue;
        }

        if (strcmp(input, "show menu") == 0) {
            if (app.hard_coded_menu) {
                show_hardcoded_menu(menu);
                continue;
            }

            else {
                printf("\nFeature not implemented yet, sorry.\n");
                continue;
            }
        }

        if (strcmp(input, "checkout") == 0 || strcmp(input, "done") == 0) {
            checkout(all_orders, &menu, &app);
            continue;
        }

        tokenize(input, order_pointer, app_pointer);

        if (order.num == 0 && (order.item > 0 || order.item < 0)) {
            order.num = 1;
        }

        if ((order.num > 0 || order.size != 0 || order.item != 0 || order.modifier != 0) && order.debug == 0) {
            add_item(all_orders, &menu, &order, &app);
            continue;
        }

        if ((order.num == 0 && order.size == 0 && order.item == 0 && order.modifier == 0) && order.debug == ENTER) {
            if (app.debug){
                app.debugging = true;
                printf("\nDebug mode enabled!\n");
                debug_mode(all_orders, &menu, &order, &app);
                continue;
            }

            else {
                printf("\nDebug mode is hard-coded to be disabled, sorry.\n");
                continue;
            }
        }

        continue;

    }

    // Safe Mode.
    while (app.running == false && app.safe_mode == true) {
        printf("\nSafe Mode is Enabled.\n");
        calculator_mode(&order, &app);
        break;
    }

    if (app.running == true && app.safe_mode == true) {
        printf("\nError! AppState's app.running AND app.safe_mode are both set to true!\nPlease make one false to use the System!\n");
    }

    show_upkeep_time(&app);

    return 0;
}
