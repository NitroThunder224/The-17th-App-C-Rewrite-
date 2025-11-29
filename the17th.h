#ifndef THE_17TH_H
#define THE_17TH_H

struct AppState {
    bool menu_question;
    bool debug;
    bool debugging;
    bool show_debug_commands;
    bool running;
    bool warning;
    int tax;
    int menu_count;
    int order_count;
    int loaded_menu;

};

struct Menu {
    int burger;
    int cheeseburger;
    int tenders;
    int nuggets;
    int chicken_sandwich;
    int wings;
    int onion_rings;
    int hotdog;
    int house_salad;
    int caesar_salad;
    int fries;
    int soda;
    int chocolate_milk;
    int white_milk;
    int juice;
    int water;
};

struct Dynamic_Menu {
    char name[200];
    int id;
    int price;
};

enum Item {
    BURGER = 5647,
    CHEESEBURGER = 6268,
    NUGGETS = 5650,
    CHICKEN_NUGGETS = 11375,
    CHICKEN_TENDERS = 11367,
    CHICKEN_SANDWICH = 11574,
    WINGS = 5437,
    ONION_RINGS = 10979,
    HOTDOG = 5645,
    FRIES = 5337,
    HOUSE_SALAD = 11065,
    CAESAR_SALAD = 11140,
    SODA = 5423,
    CHOCOLATE_MILK = 11375,
    WHITE_MILK = 10974,
    JUICE = 5528,
    WATER = 5547,
};

enum Size {
    SMALL = 1537,
    MEDIUM = 1641,
    LARGE = 1523,
    PIECES = 1518,
};

enum MODIFIER {
    DELUXE = 20647,
    MEAL = 20415,
    SPICY = 20552,
    EXTRA = 20548,
    DOUBLE = 20635,
    TRIPLE = 20656,
    DELUXE_MEAL = 41062,
    SPICY_MEAL = 40967,
    DELUXE_SPICY_MEAL = 61614,
    DELUXE_EXTRA_SPICY_MEAL = 82162,
};

enum DEBUG {
    ENTER = 100519,
    ADD_ITEM = 100823,
    SUB_ITEM = 100856,
    TEST_ORDER = 101083,
    RESET_ORDER = 101182,
    EDIT_ORDER = 101057,
    EDIT_MENU = 100954,
    EDIT_ALL = 100830,
    RANDOM_MENU = 101173,
    RANDOM_ORDER = 101276,
    RESTORE_MENU = 101304,
    SHOW_COMMANDS = 101279,
    SHOW_TAX = 100877,
    CHANGE_TAX = 101042,
    CHANGE_MENU = 101146,
    WARNING_MODE = 101274,
    HELP = 100425,
};

extern struct Dynamic_Menu dynamic_menu_items[50];
extern int menu_count;

struct Menu make_menu(void);

char *name_of_item(int id, struct AppState *app);

void *decode_modifier(char *decoded_mod_pointer_1, char *decoded_mod_pointer_2, char *decoded_mod_pointer_3, struct Order order);
void debug_mode(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app);
void show_menu(struct Menu menu);
void show_order(struct Order all_orders[], struct Menu *menu, struct AppState *app);
void show_command();
void checkout(struct Order all_orders[], struct Menu *menu, struct AppState *app);
void pluralize(char word[200]);
void add_item(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app);
void sub_item(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app);

bool warning_prompt(struct AppState *app);
bool ends_with_txt(const char *str);

int load_menu_file(const char *filename, struct AppState *app);
int get_item_price(int id, struct Menu *fallback_menu, struct AppState *app);
int get_size_price(int size);
int match_dynamic_item_id(int id, struct AppState *app);
int main();

#endif

/*
 * chicken = 5725
 * sandwich = 5849
 * tender = 5642
 * wing = 5437
 * onion = 5547
 * ring = 5432
 * hotdog = 5645
 * house = 5548
 * caesar = 5623
 * salad = 5517
 * milk = 5429
 * chocolate = 5946
 * white = 5545
 * juice = 5528
 */
