#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct pixel{

	unsigned char red;
	unsigned char green;
	unsigned char blue;

};
struct Quadtree
{
    int arie_patrat; //are val diferita la decompreseie
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
struct queue
{
   unsigned char tip;
   struct Quadtree *nod;
   struct queue *next;
};
//void inserttree(struct )
void addc(struct queue *sant,int elem, struct Quadtree *node);
void scot(struct queue *sant,int elem);
struct Quadtree *build_read_decompress(struct queue *q,FILE *f,int depp);
void printNivCurent(struct Quadtree *root, int h, FILE *g);
void printLvl(struct Quadtree *root, int h, FILE *g,int width);
int areamax(struct Quadtree *root, int *max);
struct Quadtree *build_tree(struct pixel **matrix, int factor, int *minsize, int *niv, int size, int x, int y, int *frunze);
int main(int argc, char *argv[])
{   /*FILE *f = fopen(argv[argc-2],"rb");
    char form[3];
	int colormax;
    int width, height;
	int i;
    fscanf(f, "%s"   ,form);
	fscanf(f, "%d "  ,&width);
	fscanf(f, "%d\n" ,&height);
	fscanf(f, "%d"   ,&colormax);
    printf("%s %d %d %d",form,width,height,colormax);
    char garbage;
	fread(&garbage,sizeof(char),1,f);

    struct pixel **matrix = malloc(height * sizeof(struct pixel*));
    for(i = 0; i < height; i++)
	{	
		matrix[i] = malloc(sizeof(struct pixel) * width);
		fread(matrix[i], sizeof(struct pixel), width, f);
	}
    fclose(f);*/
    //int j;
    /*FILE *g = fopen(argv[argc - 1], "w");
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
                fprintf(g, "%d %d %d * ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
            fprintf(g, "\n");
        }*/

/*----------SFARSIT CITIRE-----------------------------------------*/
 if (strcmp(argv[1], "-c1") == 0)
    {   
        FILE *f = fopen(argv[argc-2],"rb");
    char form[3];
	int colormax;
    int width, height;
	int i;
    fscanf(f, "%s"   ,form);
	fscanf(f, "%d "  ,&width);
	fscanf(f, "%d\n" ,&height);
	fscanf(f, "%d"   ,&colormax);
    printf("%s %d %d %d",form,width,height,colormax);
    char garbage;
	fread(&garbage,sizeof(char),1,f);

    struct pixel **matrix = malloc(height * sizeof(struct pixel*));
    for(i = 0; i < height; i++)
	{	
		matrix[i] = malloc(sizeof(struct pixel) * width);
		fread(matrix[i], sizeof(struct pixel), width, f);
	}
    fclose(f);

        int factor = atoi(argv[2]);
        printf("cine e factor %d", factor);
        FILE *g = fopen(argv[argc - 1], "wt");
       /* int j;
        for (i = 0; i < height; i++)
        {
            for (j = 0; j < width; j++)
                fprintf(g, "%d %d %d * ", matrix[i][j].red, matrix[i][j].green, matrix[i][j].blue);
            fprintf(g, "\n");
        }*/
        struct Quadtree *root;// = malloc(sizeof(struct Quadtree));
        int minsize = width;
        int niv = 1;
        int frunze = 0;
        root = build_tree(matrix, factor, &minsize, &niv, width, 0, 0, &frunze);
        printf("ce inaltime am: %d\n", niv);
        printf("cate frunze am: %d\n", frunze);
        int m = 0;
        int lmax = (int)sqrt(areamax(root, &m));
        printf("ce areamxa am %d\n", lmax);
        fprintf(g,"%d\n",niv);
        fprintf(g,"%d\n",frunze);
        fprintf(g,"%d\n",(int)sqrt(areamax(root, &m)));
       // fprintf(g, "%d\n", levels(root, &max));
        //fclose(g);
    }
    if (strcmp(argv[1],"-c2")==0)
    {   
        FILE *f = fopen(argv[argc-2],"rb");
    char form[3];
	int colormax;
    int width, height;
	int i;
    fscanf(f, "%s"   ,form);
	fscanf(f, "%d "  ,&width);
	fscanf(f, "%d\n" ,&height);
	fscanf(f, "%d"   ,&colormax);
    printf("%s %d %d %d",form,width,height,colormax);
    char garbage;
	fread(&garbage,sizeof(char),1,f);

    struct pixel **matrix = malloc(height * sizeof(struct pixel*));
    for(i = 0; i < height; i++)
	{	
		matrix[i] = malloc(sizeof(struct pixel) * width);
		fread(matrix[i], sizeof(struct pixel), width, f);
	}
    fclose(f);

         int factor = atoi(argv[2]);
        printf("cine e factor %d", factor);
        FILE *g = fopen(argv[argc - 1], "wb");
        struct Quadtree *root;// il pun in main sa nu ma complic cu void
        int minsize = width;
        int niv = 1;
        int frunze = 0;
        root = build_tree(matrix, factor, &minsize, &niv, width, 0, 0, &frunze);
        printf("ce inaltime am: %d\n", niv);
        printf("cate frunze am: %d\n", frunze);
        int m = 0;
        int lmax = (int)sqrt(areamax(root, &m));
        printf("ce areamxa am %d\n", lmax);
        printLvl(root,niv,g,width);
    }
    if (strcmp(argv[1],"-d") == 0){
       
        FILE *f = fopen(argv[argc - 2],"rb");
        unsigned int latura;
       
        struct Quadtree *root;
        struct queue *q = malloc(sizeof(struct queue));
        q->next = NULL;
        fread(&latura,sizeof(latura),1,f);
        root = build_read_decompress(q,f,0);
        
        printf("ce latura am: %d\n",latura);
        printf("ce adancime : %d si tip %hhu\n", root->top_left->arie_patrat, root->top_left->tip_nod);
        printf("ce culoare %hhu\n",root->top_left->value_red);
        printf("e null? %d",root->top_left->top_left->top_left->top_left->top_left->arie_patrat);
        fclose(f);
        
    }
    return 0;
}
void addc(struct queue *sant,int elem, struct Quadtree *node)
{
    struct queue *c = sant->next;
    if (sant->next == NULL){
       sant->next = malloc(sizeof(struct queue));
    sant->next->next = NULL;
    sant->next->tip = node->tip_nod;//trb sa fie doar 0 
    }
    else{
          while (c->next != NULL)
            c = c->next;
    c->next = malloc(sizeof(struct queue));
    c->next->tip = node->tip_nod;
    c->next->nod = node;
    c->next->next = NULL;
    }
    
}
void scot(struct queue *sant,int elem)
{
    if (sant->next == NULL)
    {
        perror("NAM");
        return;
    }
    else{
        struct queue *c = sant->next;
        sant->next = sant->next->next;
        free(c);
    }
}
struct Quadtree *build_read_decompress(struct queue *q,FILE *f,int depp)
{
    struct Quadtree *root = malloc(sizeof(struct Quadtree));
    
    fread(&root->tip_nod,sizeof(root->tip_nod),1,f); //primul sigur e 0
    

    if (root->tip_nod == 0){//nu e frunza mergem pe ramuri
    printf("din functie 0 d\n");
    addc(q,0,root);
    root->top_left = build_read_decompress(q,f,depp+1);
    root->top_right =build_read_decompress(q,f,depp+1);
    root->down_left = build_read_decompress(q,f,depp+1);
    root->down_right = build_read_decompress(q,f,depp+1);
     root->arie_patrat = depp;// e mai mult un raport de impartire a ariei mari
    return root;
    }
    else{
        printf("din functie 1 d\n");
        fread(&root->value_red,sizeof(root->value_red),1,f);
        fread(&root->value_green,sizeof(root->value_green),1,f);
        fread(&root->value_blue,sizeof(root->value_blue),1,f);
        root->top_right = NULL;
        root->top_left = NULL;
        root->down_right = NULL;
        root->down_left = NULL;
         root->arie_patrat = depp;// e mai mult un raport de impartire a ariei mari
    return root;
    }
   
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
void printLvl(struct Quadtree *root, int h, FILE *g,int width)
{
    int i;
    fwrite(&width,sizeof(unsigned int),1,g); //aici ai avut int dar nu a fost o problema
    for (i = 1; i <= h; i++)
        printNivCurent(root, i, g);
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
struct Quadtree *build_tree(struct pixel **matrix, int factor, int *minsize, int *niv, int size, int x, int y, int *frunze)
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
            red = red + matrix[i][j].red;
            green = green + matrix[i][j].green;
            blue = blue + matrix[i][j].blue;
        }
    red = red / (size * size);
    green = green / (size * size);
    blue = blue / (size * size);
    printf("valorile medii rosu %lld green %lld blue %lld\n",red,green,blue);
    root->value_red = red;
    root->value_green = green;
    root->value_blue = blue;
    for (i = x; i < x + size; i++)
        for (j = y; j < y + size; j++)
        {
            mean = mean + ((red - matrix[i][j].red) * (red - matrix[i][j].red)) + ((green - matrix[i][j].green) * (green - matrix[i][j].green)) + ((blue - matrix[i][j].blue) * (blue - matrix[i][j].blue));
        }
    mean = (unsigned long long int)mean / (3 * size * size);
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
