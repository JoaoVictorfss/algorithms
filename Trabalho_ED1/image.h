#define DIFFERENT -1
#define INVALID_FILE -2
#define INVALID_NULL_POINTER -3
#define ERRO -4
#define ERROR_OPENING_FILE -5
#define DIFFERENT_FORMAT -6
#define SUCCESS 0
#define TXT 1
#define IMM 2
#define CONTINUA_DIREITA 3
#define CONTINUA_ESQUERDA 4
#define CONTINUA_CIMA 5
#define CONTINUA_BAIXO 6

typedef struct Image Image;
int freeImage(Image *pIMAGE);
Image *imageCreate(int linhas, int colunas);
void showPicture(Image *pImage);
Image *openFileTxt(char *nomeArq);
int openTxt(char *nomeArq);
Image *openFileIMM(char *nomeArq);
int openIMM(char *nomeArq);
int convertTxtToImm(char *nomeArq, char *nomeArq2);
int extension(char *str);
int threshold(int thr, char *nomeArq, char *nomeArq2);
int relatedPoints(Image* image);
int search_begin(Image *image);
int maze(Image *image);



