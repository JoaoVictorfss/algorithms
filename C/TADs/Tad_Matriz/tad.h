typedef struct MATRIZES MATRIZES;

MATRIZES *criaMatriz(int linhas, int colunas);

int destroiMatriz(MATRIZES *pMatriz);

int escreveElemento(MATRIZES *pMATRIZ, int linhas, int colunas, double valor);

int acessaElemento(MATRIZES *pMATRIZ, int linhas, int colunas, double *valor);

int preencheMatriz(MATRIZES *pMATRIZ);

void printaMatriz(MATRIZES *pMATRIZ);

int somaMatriz(MATRIZES *pMATRIZone, MATRIZES *pMATRIZtwo, MATRIZES *pMATRIZsoma);

double tracoMATRIZ(MATRIZES *pmat);

int multPorEscalar(MATRIZES *pmat, int escalar);

double* somaLinhas(MATRIZES *pmat, int*resultado);

double* somaColunas(MATRIZES *pmat,int *resultado);

MATRIZES* multMatriz(MATRIZES *pMATRIZ, MATRIZES *pMATRIZ2);

