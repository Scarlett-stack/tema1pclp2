#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
struct Pixel
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
};
struct Quadtree
{
    int arie_patrat;
    unsigned long long int value_mean;
    unsigned char tip_nod;
    unsigned char value_red;
    unsigned char value_green;
    unsigned char value_blue;
    struct Quadtree *top_left;
    struct Quadtree *top_right;
    struct Quadtree *down_right;
    struct Quadtree *down_left;
};
void printNivCurent(struct Quadtree *root, int h, FILE *g);
void printLvl(struct Quadtree *root, int h, FILE *g);
int areamax(struct Quadtree *root, int *max);
int leaf(struct Quadtree *root);
int levels(struct Quadtree *root, int *max);
struct Quadtree *build_tree(struct Pixel **matrix, int factor, int *minsize, int *niv, int size, int x, int y, int *frunze);
int main(int argc, char *argv[])
{
    FILE *f = fopen(argv[argc - 2], "rb");
    char tip[10];
    unsigned int valmax;
    fgets(tip, 10, f);
    // fflush(f);
    printf("ce tip : %s", tip);
    unsigned int width, height;
    fscanf(f, "%u %u", &width, &height);
    printf("nr : %u %u\n", width, height);
    fscanf(f, "%u", &valmax);
    printf("cine ev val max: %d\n", valmax);
    // fseek(f,1,SEEK_CUR);
    /*--------------------CITIRE MATRCE---------------------------------*/
    // unsigned char *image = (unsigned char *)malloc(width * height * 3);
    // fread(image, sizeof(unsigned char), width * height * 3, f);
    struct Pixel **matrix = malloc(height * sizeof(struct Pixel *));
    unsigned int i;
    for (i = 0; i < width; i++)
        matrix[i] = malloc(width * sizeof(struct Pixel));
    unsigned j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width*3; j++)
        {
            fread(&matrix[i][j].r, sizeof(unsigned char), 1, f);
            fread(&matrix[i][j].g, sizeof(unsigned char), 1, f);
            fread(&matrix[i][j].b, sizeof(unsigned char), 1, f);
        }
    }

    if (strcmp(argv[1], "-c1") == 0)
    {
        int factor = atoi(argv[2]);
        printf("cine e factor %d", factor);
        FILE *g = fopen(argv[argc - 1], "w");
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
                fprintf(g, "%d %d %d * ", matrix[i][j].r, matrix[i][j].g, matrix[i][j].b);
            fprintf(g, "\n");
        }
        struct Quadtree *root = malloc(sizeof(struct Quadtree));
        int minsize = width;
        int niv = 1;
        int frunze = 0;
        root = build_tree(matrix, factor, &minsize, &niv, width, 0, 0, &frunze);
        printf("%p %d %llu %d\n ", root, root->arie_patrat, root->value_mean, root->top_left->arie_patrat);
        int max = 0;
        printf("ce inaltime am: %d %d\n", levels(root, &max), niv);
        printf("cate frunze am: %d %d\n", leaf(root), frunze);
        int m = 0;
        printf("ce areamxa am %d\n", (int)sqrt(areamax(root, &m)));
       // fprintf(g, "%d\n", levels(root, &max));
        fclose(g);
    }
    if (strcmp(argv[1], "-c2") == 0)
    {   FILE *g = fopen(argv[argc - 1],"wb");
        int factor = atoi(argv[2]);
        struct Quadtree *root = malloc(sizeof(struct Quadtree));
        int minsize = width;
        int niv = 1;
        int frunze = 0;
        root = build_tree(matrix, factor, &minsize, &niv, width, 0, 0, &frunze);
        printf("%p %d %llu %d\n ", root, root->arie_patrat, root->value_mean, root->top_left->arie_patrat);
        int max = 0;
        printf("ce inaltime am: %d %d\n", levels(root, &max), niv+1);
        printf("cate frunze am: %d %d\n", leaf(root), frunze);
        int m = 0;
        printf("ce areamxa am %d\n", (int)sqrt(areamax(root, &m)));
        printLvl(root,niv,g);
        fclose(g);
    }
    fclose(f);

    return 0;
}
void printNivCurent(struct Quadtree *root, int h, FILE *g)
{
    if (root == NULL)
        return;
    if (h == 1)
    {
        if (root->tip_nod == 0)
            fwrite(&root->tip_nod,sizeof(root->tip_nod),1,g);
        else
        {
            fwrite(&root->tip_nod,sizeof(root->tip_nod),1,g);
            fwrite(&root->value_red,sizeof(root->value_red),1,g);
            fwrite(&root->value_green,sizeof(root->value_green),1,g);
            fwrite(&root->value_blue,sizeof(root->value_blue),1,g);
        }
    }
    else if (h > 1)
    {
        printNivCurent(root->top_left, h - 1, g);
        printNivCurent(root->top_right, h - 1, g);
        printNivCurent(root->down_right, h - 1, g);
        printNivCurent(root->down_left, h - 1, g);
    }
}
void printLvl(struct Quadtree *root, int h, FILE *g)
{
    int i;
    for (i = 1; i <= h; i++)
        printNivCurent(root, i, g);
}
int leaf(struct Quadtree *root)
{
    if (root == NULL)
        return 0;
    if (root->down_left == NULL && root->down_right == NULL && root->top_left == NULL && root->top_right == NULL)
        return 1;
    return leaf(root->top_left) + leaf(root->top_right) + leaf(root->down_right) + leaf(root->down_left);
}
int levels(struct Quadtree *root, int *max)
{
    if (root == NULL)
    { // printf("xx\n");
        return *max;
    }
    else
    {
        // printf("aa\n");
        int tllevel = levels(root->top_left, max);
        int trlevel = levels(root->top_right, max);
        int drlevel = levels(root->down_right, max);
        int dllevel = levels(root->down_left, max);
        if ((*max) <= tllevel)
        {
            *max = tllevel;
            return (*max) + 1;
        }
        if ((*max) <= trlevel)
        {
            (*max) = trlevel;
            return (*max) + 1;
        }
        if ((*max) <= drlevel)
        {
            (*max) = drlevel;
            return (*max) + 1;
        }

        if ((*max) <= dllevel)
        {
            (*max) = dllevel;
            return (*max) + 1;
        }
    }
}
struct Quadtree *build_tree(struct Pixel **matrix, int factor, int *minsize, int *niv, int size, int x, int y, int *frunze)
{
    /*if (root == NULL)
    { printf("*\n");

        return root;
    }
    else{*/
    struct Quadtree *root = (struct Quadtree *)malloc(sizeof(struct Quadtree));
    // printf("+\n");
    unsigned long long int red = 0;
    unsigned long long int green = 0;
    unsigned long long int blue = 0;
    unsigned long long int mean = 0;
    root->arie_patrat = size * size;

    int i, j;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            red = red + matrix[i][j].r;
            green = green + matrix[i][j].g;
            blue = blue + matrix[i][j].b;
        }
    red = red / (size * size*3);
    green = green / (size * size*3);
    blue = blue / (size * size*3);
    root->value_red = red;
    root->value_green = green;
    root->value_blue = blue;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            mean = mean + ((red - matrix[i][j].r) * (red - matrix[i][j].r)) + ((green - matrix[i][j].g) * (green - matrix[i][j].g)) + ((blue - matrix[i][j].b) * (blue - matrix[i][j].b));
        }
    mean = (unsigned long long int)mean / (3 * size * size*3);
    root->value_mean = mean;
    printf("din functie mean: %lld si size %d si red %lld green %lld blu %lld \n", root->value_mean, size, red,green,blue);
    if (mean <= factor)
    { // printf("\nFRUNZA\n"); // a adaugi si tipul de nod
        (*frunze) = (*frunze) + 1;
        root->tip_nod = 1;
        root->down_left = NULL;
        root->down_right = NULL;
        root->top_left = NULL;
        root->top_right = NULL;
        return root;
    }
    else
    {
        // printf("\nNU E FRUNZA\n");
        root->tip_nod = 0; // eventual daca va fi frunza se facw 1 in if acela
        if (size / 2 < (*minsize))
        {
            (*niv) = (*niv) + 1;
            (*minsize) = size / 2;
        }
        root->top_left = build_tree(matrix, factor, minsize, niv, size / 2, x, y, frunze);
        root->top_right = build_tree(matrix, factor, minsize, niv, size / 2, x, y + size / 2, frunze);
        root->down_right = build_tree(matrix, factor, minsize, niv, size / 2, x + size / 2, y + size / 2, frunze);
        root->down_left = build_tree(matrix, factor, minsize, niv, size / 2, x + size / 2, y, frunze);
        return root;
    }
}
int areamax(struct Quadtree *root, int *max)
{
    if (root == NULL)
        return *max;

    if (root->down_left == NULL && root->down_right == NULL && root->top_left == NULL && root->top_right == NULL)
        return root->arie_patrat;
    int m0 = areamax(root->top_left, max);
    int m1 = areamax(root->top_right, max);
    int m2 = areamax(root->down_right, max);
    int m3 = areamax(root->down_left, max);

    if (m0 >= *max)
        *max = m0;
    if (m1 >= *max)
        *max = m1;
    if (m2 >= *max)
        *max = m2;
    if (m3 >= *max)
        *max = m3;
    return *max;
}
