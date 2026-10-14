#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char model[16];
    int amount;
}Item;

static Item inventory[100];


static int find_item(const char model[16]) {
    for (int idx = 0; idx < 100; idx++) {
        if (strcmp(inventory[idx].model, model) == 0) {
            return idx;
        }
    }
    return -1;
}

static int import_item(char model[16], const int amount) {
    const int idx = find_item(model);
    if (idx == -1) {
        for (int i = 0; i < 100; i++) {
            if (inventory[i].amount == 0) {
                strcpy(inventory[i].model, model);
                inventory[i].amount = amount;
                return i;
            }
        }
        return -1;  // 达到最大物品储存上限
    }
    inventory[idx].amount += amount;
    return idx;
}

static int export_item(char model[16], const int amount) {
    const int idx = find_item(model);
    if (idx == -1) {
        return -1;  // 物品不存在
    }
    const Item item = inventory[idx];
    if (item.amount < amount) {
        return -1;  // 物品不够
    }
    inventory[idx].amount -= amount;
    return idx;
}

static void list_item() {
    for (int i = 0; i < 100; i++) {
        if (inventory[i].amount > 0) {
            printf("型号: %s, 数目: %d\n", inventory[i].model, inventory[i].amount);
        }
    }
}

static int save_to_file() {
    FILE *fp = fopen("inventory", "w");
    if (fp == NULL) {
        return -1;
    }
    for (int i = 0; i < 100; i++) {
        if (inventory[i].amount > 0) {
            fputs(inventory[i].model, fp);
            fputs("\n", fp);
            char amount[16];
            snprintf(amount, sizeof(amount), "%d", inventory[i].amount);
            fputs(amount, fp);
            fputs("\n", fp);
        }
    }
    fclose(fp);
    return 0;
}

static int load_from_file() {
    FILE *fp = fopen("inventory", "r");
    if (fp == NULL) {
        return -1;
    }
    char line[16];
    int count = 0;
    int line_count = 0;
    char model[16];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        if (count == 100) {
            break;
        }
        if (line_count % 2 == 0) {  // 型号
            strcpy(model, line);
        }else {
            const int amount = atoi(line);
            inventory[count].amount = amount;
            strcpy(inventory[count].model, model);
            count++;
        }
        line_count++;
    }
    fclose(fp);
    return 0;
}

int main() {
    load_from_file();
    int quit = 0;
    while (quit == 0) {
        printf("欢迎使用仓储管理系统!!!输入数字选择功能:\n");
        printf("0=列出库存\n");
        printf("1=入库\n");
        printf("2=出库\n");
        printf("3=保存并退出\n");
        printf("请输入:");
        char input[16];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = '\0';
        const int action_num = atoi(input);
        switch (action_num) {
            case 0:
                list_item();
                break;
            case 1:
                char model[16];
                printf("请输入型号:");
                fgets(model, sizeof(model), stdin);
                model[strcspn(model, "\n")] = '\0';
                printf("请输入数目:");
                char input2[16];
                fgets(input2, sizeof(input2), stdin);
                input2[strcspn(input2, "\n")] = '\0';
                const int amount = atoi(input2);
                if (strcmp(model, "") == 0) {
                    printf("抱歉!型号不能为空!\n");
                    break;
                }
                if (amount <= 0) {
                    printf("抱歉!数目必须大于0!\n");
                    break;
                }
                const int rsp = import_item(model, amount);
                if (rsp == -1) {
                    printf("抱歉!已达到最大存储容量!\n");
                    break;
                }
                printf("入库成功!\n");
                break;
            case 2:
                char model2[16];
                printf("请输入型号:");
                fgets(model2, sizeof(model2), stdin);
                model2[strcspn(model2, "\n")] = '\0';
                printf("请输入数目:");
                char input3[16];
                fgets(input3, sizeof(input3), stdin);
                input3[strcspn(input3, "\n")] = '\0';
                const int amount2 = atoi(input3);
                if (strcmp(model2, "") == 0) {
                    printf("抱歉!型号不能为空!\n");
                    break;
                }
                if (amount2 <= 0) {
                    printf("抱歉!数目必须大于0!\n");
                    break;
                }
                const int rsp2 = export_item(model2, amount2);
                if (rsp2 == -1) {
                    printf("抱歉!库存不够!\n");
                    break;
                }
                printf("出库成功!\n");
                break;
            case 3:
                printf("程序即将退出!\n");
                quit = 1;
                break;
        }
    }
    save_to_file();
    return 0;
}