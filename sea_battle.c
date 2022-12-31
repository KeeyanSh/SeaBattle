#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>
#include<conio.h>


int a[] = {5,3,3,2,2,2,1,1,1,1,
           0}, n = 10,v, l, max, z, f, i,emt, emtiaz,*score, score_a, score_b, *rocket, rocket_a, rocket_b, w, e, bx, by, x2, y2, count, mark, h = 0, m = 29, k = 0;
int rep[400];
char name1[50] = "1", name2[50] = "2", s[50], last[] = "last.c", hrf;

struct node {
    int x1, x2, y1, y2, adad, count;
    char c;
    struct node *next;
};

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void add_node(struct node *list, struct node *NEW) {
    while (list->next != NULL)
        list = list->next;
    list->next = NEW;
    list = list->next;
    list->next = NULL;
}

void front_node(struct node **list, struct node *NEW) {
    NEW->next = *list;
    *list = NEW;
}

void linked_deleter(struct node **list) {
    if ((*list)->next == NULL) {
        free(*list);
        *list = NULL;
        return;
    }
    struct node *p = *list;
    for (; p->next->next != NULL; p = p->next);
    free(p->next);
    p->next = NULL;
    linked_deleter(list);

}

void map_printer(char b[n][n]) {

    printf("  ");
    for (int i = 0; i < 10; i++)
        printf("%d ", i);
    printf("\n");

    for (int i = 0; i < 10; i++) {
        printf("%d ", i);
        for (int j = 0; j < 10; j++)
            printf("%c ", b[i][j]);
        printf("\n");
    }
}

void duo_map_printer(int j, char a[n][n], char b[n][n]) {
    printf("\n");
    printf("           [%s]                                               [%s]\n\n", name1, name2);
    printf("     ");
    for (int i = 0; i < 10; i++)
        printf("%d ", i);
    printf("                                 ");
    for (int i = 0; i < 10; i++)
        printf("%d ", i);
    printf("\n\n");

    for (int i = 0; i < 10; i++) {
        {
            printf("%d    ", i);
            for (int j = 0; j < 10; j++)
                printf("%c ", a[i][j]);
            printf("                            %d    ", i);
            for (int j = 0; j < 10; j++)
                printf("%c ", b[i][j]);
            printf("\n");
        }
    }
    if (j == 0)
        printf("\nscore = %d                                               score = %d\n", score_a, score_b);
    printf("\nrockets = %d                                             rockets = %d\n", rocket_a, rocket_b);
    printf("\n");
}

int checker(struct node *list, struct node *NEW) {
    while (list != NULL) {
        if (NEW->c == 'V') {
            if (list->c == 'V') {
                if (list->x1 == NEW->x1) {
                    if (!(list->y1 > NEW->y2 + 1 || list->y2 + 1 < NEW->y1))
                        return -1;
                } else if (list->x1 == NEW->x1 + 1 || list->x1 == NEW->x1 - 1)
                    return -1;
            } else if (NEW->x1 >= list->x1 - 1 && NEW->x1 <= list->x2 + 1)
                if (!(NEW->y1 > list->y1 + 1 || NEW->y2 < list->y1 - 1))
                    return -1;
        } else {
            if (list->c == 'H') {
                if (list->y1 == NEW->y1) {
                    if (!(list->x1 > NEW->x2 + 1 || list->x2 + 1 < NEW->x1))
                        return -1;
                } else if (list->y1 == NEW->y1 + 1 || list->y1 == NEW->y1 - 1)
                    return -1;
            } else if (list->x1 >= NEW->x1 - 1 && list->x1 <= NEW->x2 + 1)
                if (!(list->y1 > NEW->y1 + 1 || list->y2 < NEW->y1 - 1))
                    return -1;
        }
        list = list->next;
    }
    return 0;
}

void fixer(struct node *list, char b[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i][j] = 'O';

    while (list != NULL) {
        if (list->c == 'H') {
            int i = list->x1;
            while (i <= list->x2)
                b[list->y1][i++] = '.';
        } else {
            int i = list->y1;
            while (i <= list->y2)
                b[i++][list->x1] = '.';
        }
        list = list->next;
    }
}

void ter_fix(struct node *list, char c[n][n]) {
    if (list->c == 'H') {
        for (int i = list->x1 - 1; i <= list->x2 + 1; i++) {
            if (i >= 0 && i < n) {
                if (i == list->x1 - 1 || i == list->x2 + 1)
                    c[list->y1][i] = '.';
                else
                    c[list->y1][i] = '#';
                if (list->y1 - 1 >= 0)
                    c[list->y1 - 1][i] = '.';

                if (list->y1 + 1 < n)
                    c[list->y1 + 1][i] = '.';


            }
        }
    } else {
        for (int i = list->y1 - 1; i <= list->y2 + 1; i++) {
            if (i >= 0 && i < n) {
                if (i == list->y1 - 1 || i == list->y2 + 1)
                    c[i][list->x1] = '.';
                else
                    c[i][list->x1] = '#';
                if (list->x1 - 1 >= 0)
                    c[i][list->x1 - 1] = '.';

                if (list->x1 + 1 < n)
                    c[i][list->x1 + 1] = '.';


            }
        }
    }
}

void map_builder(struct node **list, char b[n][n]) {
    int x1, y1, x2, y2;
    char c;
    i = 0;
    while (a[i] != 0) {
        map_printer(b);
        int h = 1;
        printf("enter your %d size ship place:", a[i]);
        scanf("%d,%d%d,%d", &x1, &y1, &x2, &y2);
        if (x1 == x2) {
            c = 'V';
            if (y1 > y2)
                swap(&y1, &y2);
            if (y2 - y1 != a[i] - 1) {
                h = -1;
            }
        } else if (y1 == y2) {
            c = 'H';
            if (x1 > x2)
                swap(&x1, &x2);
            if (x2 - x1 != a[i] - 1) {
                h = -1;
            }
        } else
            h = -1;
        system("cls");
        if (h == -1) {
            printf("\n<< Wrong length; try again >>\n\n");
            continue;
        } else {
            struct node *NEW = (struct node *) malloc(sizeof(struct node));
            NEW->x1 = x1;
            NEW->y1 = y1;
            NEW->x2 = x2;
            NEW->y2 = y2;
            NEW->c = c;
            NEW->count = 0;
            NEW->adad = a[i];

            if (checker(*list, NEW) == -1) {
                printf("\n<< interference; try again >>\n\n");
                continue;
            }
            if (*list == NULL)
                front_node(list, NEW);

            else
                add_node(*list, NEW);
            fixer(*list, b);

            i++;


        }
    }
}

void print_it(struct node *list) {
    for (struct node *p = list; p != NULL; p = p->next) {
        printf("%d,%d  %d,%d %c\n", p->x1, p->y1, p->x2, p->y2, p->c);
    }
}

void bot_place(int *x1, int *x2) {
    int r = rand() % 2;
    if (r == 1)
        r = a[i] - 1;
    else
        r = 1 - a[i];
    *x2 = *x1 + r;
    if (*x2 >= n || *x2 < 0)
        *x2 = *x1 - r;
    if (*x1 > *x2)
        swap(x1, x2);

}

int terminate(struct node **list, struct node *terr) {

    struct node *p = *list;
    if (terr == p) {
        if (p->next == NULL) {
            free(p);
            return 1;
        }
        free(p);
        *list = (*list)->next;
        return 0;
    } else
        while (terr != p->next)
            p = p->next;

    free(p->next);
    p->next = p->next->next;
    return 0;
}

int check_save(int j, char sm[]) {
    char esm[50];
    FILE *fp = fopen(sm, "r+");
    fgets(esm, 50, fp);

    while (1) {
        fscanf(fp, "%s", esm);
        if (feof(fp))
            break;

        if (strcmp(s, esm) == 0) {
            if (j == 0)
                printf("\n< Name already exists; choose another >\n\n");
            else if (j == 1) {
                fseek(fp, 2, SEEK_CUR);
                fprintf(fp, "%3d", *score);

            }

            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

int hamle_res(struct node **list, int x, int y, char b[n][n], char c[n][n]) {
    rep[l++] = x;
    rep[l++] = y;

    int j = 0;
    struct node *p = *list;
    while (p != NULL) {
        if (p->c == 'H') {
            if (y == p->y1)
                if (x >= p->x1 && x <= p->x2) {
                    j = 1;
                    break;
                }
        } else if (x == p->x1)
            if (y >= p->y1 && y <= p->y2) {
                j = 1;
                break;
            }
        p = p->next;
    }
    if (j == 1) {
        (*score)++;
        p->count++;
        if (p->count == p->adad) {
            (*score) += 5 * a[0] / p->adad;
            ter_fix(p, c);
            if(v==1)
             return 1;

            if (terminate(list, p) == 1) {
                strcpy(s, name1);
                score = &score_a;
                check_save(1, "users.txt");
                if (strcmp(name2, "player") != 0) {
                    score = &score_b;
                    strcpy(s, name2);
                    check_save(1, "users.txt");
                }
                return 3;
            }
            return 2;

        } else {
            c[y][x] = 'X';
            return 1;
        }

    }
    c[y][x] = '.';
    return 0;
}

void bot_map(struct node **list, char b[n][n]) {
    i = 0;
    int r, x1, y1, x2, y2;
    char c;

    while (a[i] != 0) {
        x1 = rand() % n;
        y1 = rand() % n;
        r = rand() % 2;

        if (r == 1) {
            bot_place(&x1, &x2);
            y2 = y1;
            c = 'H';
        } else {
            bot_place(&y1, &y2);
            x2 = x1;
            c = 'V';
        }
        struct node *NEW = (struct node *) malloc(sizeof(struct node));
        NEW->x1 = x1;
        NEW->y1 = y1;
        NEW->x2 = x2;
        NEW->y2 = y2;
        NEW->c = c;
        NEW->count = 0;
        NEW->adad = a[i];
        if (checker(*list, NEW) == -1)
            continue;

        if (*list == NULL)
            front_node(list, NEW);
        else
            add_node(*list, NEW);

        fixer(*list, b);
        i++;
    }
}

int bot(int j, struct node **list, char b[n][n], char c[n][n]) {

    for (long long r = -99999999; r < 139999999; r++);
    if (j == -1) {
        bx = rep[max++];
        by = rep[max++];
    } else {
        int ax = 0, ay = 0;
        while (1) {
            if (hrf == 'V') {
                if (ay > n - 1)
                    return 0;
                bx = j;
                by = ay++;
            } else {
                if (ax > n - 1)
                    return 0;
                bx = ax++;
                by = j;
            }
            k = hamle_res(list, bx, by, b, c);
            if (k == 1)
                return 0;

        }
    }
    k = hamle_res(list, bx, by, b, c);
    system("cls");

    if (k == 0)
        return 0;

    else if (k == 2 || k == 1)
        return 1;


    else if (k == 3)
        return 2;
}

void rocket_buy() {
    system("cls");
    if (*score < 100) {
        printf("\n   << Not enough points :( >>\n");
        return;
    }
    if (*rocket == -1) {
        printf("\n   << You can only have a rocket each game >>\n");
        return;
    }
    (*score) -= 100;
    printf("\n   Congratulations!!\n   Now you have a rocket :D\nyou score is (%d) now\n\n<<You can activate the rocket by entering (-2)>>\n",
           *score);
    (*rocket)++;
}

int rocket_attack() {
    if (*rocket == 0) {
        printf("<<< NO rockets available >>>\n");
        return -1;
    }

    int j;
    (*rocket)=-1;
    getchar();
    printf("> Horizental or Vertical?\n    1) H\n    2) V\n    ");
    scanf("%d", &j);
    if (j == 1)
        hrf = 'H';
    else
        hrf = 'V';

    printf("> which row?\n     ");
    scanf("%d", &j);
    system("cls");
    v=1;
    return j;
}

int hamle(struct node **list, char b[n][n], char c[n][n]) {
    int x, y;
    printf("                            Which place to attack ??  \n\n                                        ");


    scanf("%d", &x);
    if (x == -1) {
        return 5;
    } else if (x == 100) {
        rocket_buy();
        return 1;
    } else if (x == -2) {
        int j = rocket_attack();
        if (j == -1)
            return 1;
        bot(j, list, b, c);
        return 0;
    }


    scanf(",%d", &y);
    system("cls");

    if (c[y][x] != 'O') {
        printf("\n---------------------------CHOSEN BEFORE; try once more-------------------------------\n\n");
        return 1;
    }
    int k = hamle_res(list, x, y, b, c);

    printf("\n\n");

    if (k == 0) {
        printf("\n------------------------------- Maybe next time :(----------------------------------\n\n");
        return 0;
    } else if (k == 1) {
        printf("\n--------------------------------- What a hit !!! ------------------------------------\n\n");
        return 1;
    } else if (k == 2) {
        printf("\n------------------------------- TERMINATED XD--------------------------------------\n\n");
        return 1;
    } else if (k == 3) {
        return 2;
    }
}

void bot_decision(int *x, int *y, int h) {
    if (h == 0 || h == -2) {
        *x = x2;
        *y = y2;
        w = rand() % 2;
        e = rand() % 2;
    } else if (h == -1) {
        *x = x2;
        *y = y2;

        if (e == 1)
            e = 0;
        else
            e = 1;
    }
    int x1 = *x;
    int y1 = *y;

    if (count == 5) {
        count = 0;
        if (w == 1)
            w = 0;
        else if (w == 0)
            w = 1;
    }

    while (*x == x1 && *y == y1) {
        if (w == 1) {
            if (e == 1 && *x < n - 1)
                (*x)++;
            else if (e == 0 && *x > 0)
                (*x)--;
            else {
                w = rand() % 2;
                e = rand() % 2;
            }
        } else {
            if (e == 1 && *y < n - 1)
                (*y)++;
            else if (e == 0 && *y > 0)
                (*y)--;
            else {
                w = rand() % 2;
                e = rand() % 2;
            }
        }
    }
    count++;
}

int bot_attack(int j, struct node **list, char b[n][n], char c[n][n], char d[n][n]) {
    while (1) {
        for (long long j = -99999999; j < 99999999; j++);

        if (k == 1) {
            bot_decision(&bx, &by, h);
        } else {
            bx = x2 = rand() % n;
            by = y2 = rand() % n;
        }
        if (c[by][bx] != 'O') {
            if (m == 1 && k == 1)
                h = -1;
            continue;
        }
        m = k;
        count = 0;
        k = hamle_res(list, bx, by, b, c);

        system("cls");
        duo_map_printer(0, d, c);

        if (k == 1) {
            if (m == 1) {
                if (((bx == n - 1 || bx == 0) && bx != x2) || ((by == n - 1 || by == 0) && by != y2)) {
                    h = -1;
                } else
                    h = 1;

            }
        } else if (k == 0) {
            if (m == 1) {
                if (h == 1)
                    h = -1;
                else
                    h = -2;
                k = 1;
            } else
                h = 0;

            return 0;

        } else if (k == 2) {
            h = 0;

        } else if (k == 3) {
            printf("---------------- GAME OVER ----------------\n");
            return 2;
        }

    }
}

void save_name(int j, char esm[]) {
    FILE *fp = fopen(esm, "a");
    fputs(s, fp);
    fputc('\n', fp);
    if (j == 1) {
        fprintf(fp, "%3d\n", emtiaz);
    }
    fclose(fp);
}

void save(struct node *fisrt, struct node *second, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {
    system("cls");
    printf("Do you wanna save the game ?\n    1) Yes\n    2) No\n");
    int j;
    scanf("%d", &j);
    if (j == 2)
        return;
    system("cls");
    while (1) {
        printf(">> Enter a name for the saving file : ");
        scanf("%s", s);
        if (check_save(0, "files.txt") == 0)
            break;
    }
    save_name(0, "files.txt");
    char c[] = ".c";
    strcat(s, c);
    char *p = s;
    for (int i = 0; i < 2; i++) {
        FILE *fd = fopen(p, "wb");
        fwrite(&bx, sizeof(int), 1, fd);
        fwrite(&by, sizeof(int), 1, fd);
        fwrite(&x2, sizeof(int), 1, fd);
        fwrite(&y2, sizeof(int), 1, fd);
        fwrite(&k, sizeof(int), 1, fd);
        fwrite(&m, sizeof(int), 1, fd);
        fwrite(&h, sizeof(int), 1, fd);
        fwrite(&mark, sizeof(int), 1, fd);
        fwrite(&score_a, sizeof(int), 1, fd);
        fwrite(&score_b, sizeof(int), 1, fd);
        fwrite(&rocket_a, sizeof(int), 1, fd);
        fwrite(&rocket_b, sizeof(int), 1, fd);
        fwrite(name1, sizeof(char), strlen(name1) + 1, fd);
        fwrite(name2, sizeof(char), strlen(name2) + 1, fd);
        fwrite(one, sizeof(char), 100, fd);
        fwrite(yek, sizeof(char), 100, fd);
        fwrite(two, sizeof(char), 100, fd);
        fwrite(dow, sizeof(char), 100, fd);

        for (struct node *p = fisrt; p != NULL; p = p->next)
            fwrite(p, sizeof(struct node), 1, fd);

        struct node *NEW = (struct node *) malloc(sizeof(struct node));
        NEW->next = NULL;
        NEW->x1 = 100;
        fwrite(NEW, sizeof(struct node), 1, fd);

        for (struct node *p = second; p != NULL; p = p->next)
            fwrite(p, sizeof(struct node), 1, fd);

        system("cls");
        fclose(fd);

        p = last;
    }
    printf("----SAVED----");
}

void replay_save(struct node *fisrt, struct node *second, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {
    FILE *fd = fopen("replay.c", "wb");

    fwrite(one, sizeof(char), 100, fd);
    fwrite(yek, sizeof(char), 100, fd);
    fwrite(two, sizeof(char), 100, fd);
    fwrite(dow, sizeof(char), 100, fd);

    for (struct node *p = fisrt; p != NULL; p = p->next)
        fwrite(p, sizeof(struct node), 1, fd);

    struct node *NEW = (struct node *) malloc(sizeof(struct node));
    NEW->next = NULL;
    NEW->x1 = 100;
    fwrite(NEW, sizeof(struct node), 1, fd);

    for (struct node *p = second; p != NULL; p = p->next)
        fwrite(p, sizeof(struct node), 1, fd);

    fclose(fd);
}

void replay_load(struct node **kian, struct node **sam, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {

    FILE *fd = fopen("replay.c", "rb");

    fread(one, sizeof(char), 100, fd);
    fread(yek, sizeof(char), 100, fd);
    fread(two, sizeof(char), 100, fd);
    fread(dow, sizeof(char), 100, fd);

    while (1) {
        struct node *NEW = (struct node *) malloc(sizeof(struct node));
        fread(NEW, sizeof(struct node), 1, fd);

        if (NEW->x1 == 100)
            break;

        if (*kian == NULL)
            front_node(kian, NEW);
        else
            add_node(*kian, NEW);
    }
    while (1) {
        struct node *NEW = (struct node *) malloc(sizeof(struct node));
        fread(NEW, sizeof(struct node), 1, fd);

        if (feof(fd))
            break;

        if (*sam == NULL)
            front_node(sam, NEW);
        else
            add_node(*sam, NEW);
    }

    fclose(fd);

}

void sort_scores(char p[][50], int num){
    for(int i=1; i<=num; i+=2)
     for(int j=i+2; j<=num; j+=2){
        int z1,z2;

        z1=atoi(p[j]);
        z2=atoi(p[i]);
         if(z2<z1){


         char esm[50];

          strcpy(esm,p[i]);
         strcpy(p[i],p[j]);
         strcpy(p[j],esm);


         strcpy(esm,p[i-1]);
         strcpy(p[i-1],p[j-1]);
         strcpy(p[j-1],esm);

    }}

    int j=1,l=1;;
    while(j<=num){
     if (j % 2 == 1)
                printf("       %d > %s ", l++, p[j - 1]);
            else
                printf("-------------- %s\n", p[j - 1]);
                j++;
} }

void saved_list(int j, char sm[]) {
    int k = 0;
    char tm[50];
    FILE *fp = fopen(sm, "r");
    if (j == 0) {
        fscanf(fp, "%s", s);
    }
    while (!feof(fp)) {
        fgets(tm, 50, fp);
        k++;
    }k-=2;
    if(k<=0){
        emt=-1;
         fclose(fp);
        return;
    }
    if(j==0){
          fclose(fp);
        return;
    }
    rewind(fp);
    fgets(s, 50, fp);

    char esm[k][50];
    int tedad=k;
    k = 0;
    if (j == 3)
        printf("\n----- Score Board -----\n\n");
    else
        printf("\n------- Saves -------\n\n");
    int l = 1;

    while (1) {
        fscanf(fp, "%s", esm[k++]);
        if (feof(fp))
            break;
        if (j == 1)
            printf("       %d > %s\n", k, esm[k - 1]);
        else if (j == 2 && k % 2 == 1)
            printf("       %d > %s\n", l++, esm[k - 1]);
    }
    if (j == 3){
        sort_scores(esm,tedad);
        return;
    }
        while (1) {

            printf("\n\nChoose one :  ");
            scanf("%d", &l);
            if (l > k - 1)
                printf("\n              < Wrong number;try again >\n\n");
            else
                break;
        }
    if (j == 2) {
        strcpy(s, esm[l + l - 2]);
    } else
        strcpy(s, esm[l - 1]);

    if (j == 2)
        *score = atoi(esm[l]);


    fclose(fp);
}

void users() {
    printf("> Choose one:\n\n    1) New user\n    2) Choose from available users\n");
    int j;
    scanf("%d", &j);
    system("cls");
    if (j == 1)
        while (1) {
            printf("\n >> Enter your name :  ");
            scanf("%s", s);
            if (check_save(0, "users.txt") == 0) {
                save_name(1, "users.txt");
                break;
            }
        }
    else
        saved_list(2, "users.txt");

    system("cls");
}

void load(struct node **first, struct node **second, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {
    system("cls");
    char c[] = ".c";
    strcat(s, c);
    FILE *fd = fopen(s, "rb");
    fread(&bx, sizeof(int), 1, fd);
    fread(&by, sizeof(int), 1, fd);
    fread(&x2, sizeof(int), 1, fd);
    fread(&y2, sizeof(int), 1, fd);
    fread(&k, sizeof(int), 1, fd);
    fread(&m, sizeof(int), 1, fd);
    fread(&h, sizeof(int), 1, fd);
    fread(&mark, sizeof(int), 1, fd);
    fread(&score_a, sizeof(int), 1, fd);
    fread(&score_b, sizeof(int), 1, fd);
    fread(&rocket_a, sizeof(int), 1, fd);
    fread(&rocket_b, sizeof(int), 1, fd);

    char *p = name1;
    while (1) {
        fread(p++, sizeof(char), 1, fd);
        if (*(p - 1) == '\0')
            break;
    }
    p = name2;
    while (1) {
        fread(p++, sizeof(char), 1, fd);
        if (*(p - 1) == '\0')
            break;
    }
    fread(one, sizeof(char), 100, fd);
    fread(yek, sizeof(char), 100, fd);
    fread(two, sizeof(char), 100, fd);
    fread(dow, sizeof(char), 100, fd);
    while (1) {
        struct node *NEW = (struct node *) malloc(sizeof(struct node));
        fread(NEW, sizeof(struct node), 1, fd);

        if (NEW->x1 == 100)
            break;

        if (*first == NULL)
            front_node(first, NEW);
        else
            add_node(*first, NEW);
    }
    while (1) {
        struct node *NEW = (struct node *) malloc(sizeof(struct node));
        fread(NEW, sizeof(struct node), 1, fd);

        if (feof(fd))
            break;

        if (*second == NULL)
            front_node(second, NEW);
        else
            add_node(*second, NEW);
    }
    fclose(fd);
    system("cls");
    printf("\n\n\n\n---------------------------------- Please Wait ------------------------------------\n\n");
    printf("                                     LOADING... \n");
    for (long long j = -61999999; j < 319999997; j++);
    system("cls");
    printf("\n\n\n\n                                 LET'S GOOO :D\n");
    for (long long j = -9999999; j < 299999990; j++);
    system("cls");
}

void player_map(struct node **first, char one[n][n], char name[]) {
    system("cls");
    strcpy(name, s);
    int choice;
    printf("How do you want to build your map %s ?\n  1) Auto\n  2) Manually\n", name);
    scanf("%d", &choice);
    system("cls");

    if (choice == 1) {
        while (1) {
            bot_map(first, one);
            map_printer(one);

            printf("\n1) That's it :D\n2) Build another\n");

            scanf("%d", &choice);
            system("cls");

            if (choice == 1)
                break;
            else {
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        one[i][j] = 'O';

                linked_deleter(first);
            }
        }
    } else {
        map_builder(first, one);
    }
}

void results(struct node *first, struct node *second, char one[n][n], char two[n][n], char name[]) {
    system("cls");
    printf("\n\n\n                          >>>>> %s WOOON!!!! <<<<<\n", name);
    for (long long j = -61999999; j < 719999997; j++);
    system("cls");

    fixer(first, one);
    fixer(second, two);
    printf("\n\n\n<< Remained ships >> :\n\n");

    duo_map_printer(0, two, one);
}

int menu(struct node **first, struct node **second, char one[n][n], char two[n][n]) {
    printf("-------Main Menu-------\n\n1) New game\n2) Resume last game\n3) Saved games\n4) Score Board\n5) Quit\n");
    int choice;
    scanf("%d", &choice);
    system("cls");

    if (choice == 1) {
        printf("Choose one :\n    1) Play with bot\n    2) Play with a friend\n");
        scanf("%d", &choice);
        system("cls");
        if (choice == 1) {
            score = &score_a;
            users();
            player_map(first, one, name1);
            bot_map(second, two);
            return 1;
        } else {
            printf("------  player 1 ------\n\n");
            score = &score_a;
            users();
            player_map(first, one, name1);

            printf("------  player 2 ------\n\n");
            score = &score_b;
            while (1) {
                users();
                if (strcmp(name1, s) == 0)
                    printf("\n     << User is chosen by the other player: try once more >>\n\n");

                else
                    break;
            }
            player_map(second, two, name2);

            return 2;
        }
    } else if (choice == 2)
        return -1;

    else if (choice == 3)
        return -2;

    else if (choice == 4) {
        getchar();
        saved_list(3, "users.txt");
        printf("\n\n\n  < Press any key to continue >\n");
        getch();
        return 4;
    }
    else if(choice==5)
    exit(0);

}

void duo_game(struct node **first, struct node **second, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {
    replay_save(*first, *second, one, two, yek, dow);
    duo_map_printer(0, dow, yek);
    int o = 9, p = 9;
    if (mark == 2) {
        p = 0;
    }
    while (1) {
        while (p != 0 && p != 5) {
            score = &score_a;
            rocket = &rocket_a;
            printf("\n                           << It's your turn %s >>\n\n", name1);
            p = hamle(second, two, dow);
            if (p == 2) {
                score_b /= 2;
                results(*first, *second, one, two, name1);
                return;
            }
            duo_map_printer(0, dow, yek);
        }
        if (p == 5) {
            mark = 1;
            save(*first, *second, one, two, yek, dow);
            break;
        }

        p = 1;

        while (o != 0 && o != 5) {
            score = &score_b;
            rocket = &rocket_b;
            printf("\n                           << It's your turn %s >>\n\n", name2);
            o = hamle(first, one, yek);


            if (o == 2) {
                score_a /= 2;
                results(*first, *second, one, two, name2);
                return;
            }
            duo_map_printer(0, dow, yek);
        }
        if (o == 5) {
            mark = 2;
            save(*first, *second, one, two, yek, dow);
            break;
        }
        o = 1;
    }
}

void bot_game(struct node **first, struct node **second, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {
    replay_save(*first, *second, one, two, yek, dow);
    duo_map_printer(0, dow, yek);
    strcpy(name2, "player");
    int o = 9, p = 9;

    while (1) {
        while (p != 0 && p != 5 && p != 2) {
            score = &score_a;
            rocket = &rocket_a;
            printf("\n\n                           << It's your turn %s >>\n\n", name1);
            p = hamle(second, two, dow);
            duo_map_printer(0, dow, yek);
        }
        if (p == 5) {
            save(*first, *second, one, two, yek, dow);
            return;
        } else if (p == 2) {
            score_b /= 2;
            results(*first, *second, one, two, "You");
            return;
        }

        p = 1;
        while (o != 0 && o != 2) {
            score = &score_b;
            o = bot_attack(0, first, one, yek, dow);
        }
        if (o == 2) {
            score_a /= 2;
            results(*first, *second, one, two, "Bot");
            return;
        }
        o = 1;
    }
}

void replay(int j, struct node **first, struct node **second, char one[n][n], char two[n][n], char yek[n][n], char dow[n][n]) {
    strcpy(name2, "player");
    int o = 9, p = 9;
    score = &z;
    while (1) {
        while (p != 0 && p != 2) {
            p = bot(-1, second, two, dow);
            duo_map_printer(1, dow, yek);
            if (max >= j - 1)
                return;
        }
        if (p == 2)
            return;
        p = 1;

        while (o != 0 && o != 2) {
            o = bot(-1, first, one, yek);

            duo_map_printer(1, dow, yek);
            if (max >= j - 1)
                return;
        }
        if (o == 2)
            return;
        o = 1;
    }
}

int saved_directory(int j, struct node **first, struct node **second, char one[n][n], char two[n][n], char yek[n][n],char dow[n][n]) {
    saved_list(j, "files.txt");
    if(emt==-1)
      return 0;

    load(first, second, one, two, yek, dow);
    if (mark != 0)
        return 2;
    else
        return 1;
}

int main() {
    srand(time(NULL));
    struct node *first, *second;
    first = second = NULL;

    char one[n][n], two[n][n], yek[n][n], dow[n][n];

    fixer(first, yek);
    fixer(first, dow);

    int g;
    g = menu(&first, &second, one, two);
    while (1) {
        system("cls");
        if (g == 1) {
            bot_game(&first, &second, one, two, yek, dow);

        } else if (g == 2) {
            duo_game(&first, &second, one, two, yek, dow);

        } else if (g == -1) {
            g = saved_directory(0, &first, &second, one, two, yek, dow);
            if(g!=0)
            continue;

        } else if (g == -2) {
            g = saved_directory(1, &first, &second, one, two, yek, dow);
            if(g!=0)
            continue;
        }
        if (g == 1 || g == 2) {
            linked_deleter(&first);
            linked_deleter(&second);
            fixer(first, one);
            fixer(first, yek);
            fixer(first, dow);
            fixer(first, two);

            printf(">> Do you wanna watch the replay of the game ? \n    1) Yes\n    2) No\n");
            int j;
            scanf("%d", &j);
            if (j == 1) {
                replay_load(&first, &second, one, two, yek, dow);
                replay(l, &first, &second, one, two, yek, dow);

                printf("\n\n\n  < Press any key to continue >\n");
                getch();
                   linked_deleter(&first);
            linked_deleter(&second);

                fixer(first, one);
                fixer(first, yek);
                fixer(first, dow);
                fixer(first, two);

            }
            system("cls");
            emt=0;

        } g = menu(&first, &second, one, two);
    }
    return 0;
}
