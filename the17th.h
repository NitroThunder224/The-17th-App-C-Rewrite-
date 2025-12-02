#ifndef THE_17TH_H
#define THE_17TH_H

#include <time.h>
#include <stdlib.h>

struct AppState {
    char history[1000][50];
    bool menu_question;
    bool debug;
    bool debugging;
    bool show_debug_commands;
    bool show_debug_message;
    bool running;
    bool warning;
    bool hard_coded_menu;
    bool random_menu;
    bool safe_mode;
    bool stress_test;
    int history_index;
    int tax;
    int menu_count;
    int order_count;
    int loaded_menu;
    clock_t start_time;
    double elapsed_seconds;
    double before_action;
    double after_action;
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
    BURGER = -1377755139,
    CHEESEBURGER = -1921865836,
    NUGGETS = -1034533026,
    CHICKEN_NUGGETS = -1702416088,
    CHICKEN_TENDERS = -1545211866,
    CHICKEN_SANDWICH = 107954189,
    WINGS = 3654547,
    ONION_RINGS = -309058962,
    HOTDOG = -1211464361,
    FRIES = 106677,
    HOUSE_SALAD = 1570942506,
    CAESAR_SALAD = -209104889,
    SODA = 3540833,
    CHOCOLATE_MILK = -1483041850,
    WHITE_MILK = 258364921,
    JUICE = 101487848,
    WATER = 112908447,
};

enum Size {
    SMALL = 109549807,
    MEDIUM = -1078029475,
    LARGE = 102743843,
    PIECES = 106663638,
};

enum MODIFIER {
    DELUXE = -1335422889,
    MEAL = 3367395,
    SPICY = 109665602,
    EXTRA = 96985648,
    DOUBLE = -1325938191,
    TRIPLE = -865445250,
    DELUXE_MEAL = -1332055494,
    SPICY_MEAL = 113032997,
    DELUXE_SPICY_MEAL = -1222389892,
    DELUXE_EXTRA_SPICY_MEAL = -1125404244,
};

enum DEBUG {
    ENTER = 95558899,
    ADD_ITEM = -1236042095,
    SUB_ITEM = -2079792046,
    TEST_ORDER = 2066776065,
    RESET_ORDER = -433580290,
    EDIT_ORDER = -2016235655,
    EDIT_MENU = -1866130156,
    EDIT_ALL = 1602455692,
    RANDOM_MENU = -699665925,
    RANDOM_ORDER = -215582862,
    RESTORE_MENU = 1648880400,
    SHOW_COMMANDS = -1902863703,
    SHOW_TAX = -338392567,
    CHANGE_TAX = -2131480260,
    CHANGE_MENU = -1654583506,
    COMBINE_MENU = 1449510655,
    DELETE_MENU = -1121934829,
    CALCULATOR = -1138429534,
    WARNING_MODE = -2016204026,
    TIME = 3660141,
    HYPERBOLIC_TIME = -187618753,
    HELP = 3298785,
};

extern struct Dynamic_Menu dynamic_menu_items[200];
extern int menu_count;

struct Menu make_menu(void);

char *name_of_item(int id, struct AppState *app);
char *title_case_converter(char *string);

void *decode_modifier(char *decoded_mod_pointer_1, char *decoded_mod_pointer_2, char *decoded_mod_pointer_3, struct Order order);
void debug_mode(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app);
void hyperbolic_chamber(struct Order *order, struct AppState *app);
void calculator_mode(struct Order *order, struct AppState *app);
void show_hardcoded_menu(struct Menu menu);
void show_dynamic_menu(struct AppState *app);
void show_order(struct Order all_orders[], struct Menu *menu, struct AppState *app);
void show_command();
void show_upkeep_time(struct AppState *app);
void checkout(struct Order all_orders[], struct Menu *menu, struct AppState *app);
void pluralize(char word[200]);
void add_item(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app);
void sub_item(struct Order all_orders[], struct Menu *menu, struct Order *order, struct AppState *app);
void load_fallback_into_dynamic(struct Menu *menu, struct AppState *app);
void make_random_menu(struct Order all_orders[], struct Menu *menu, struct AppState *app);

bool warning_prompt(struct AppState *app);
bool ends_with_txt(const char *str);

int load_menu_file(const char *filename, struct AppState *app);
int make_log_file(struct Order all_orders[], struct Menu *menu, struct AppState *app);
int get_item_price(int id, struct Menu *fallback_menu, struct AppState *app);
int get_size_price(int size, struct AppState *app);
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
