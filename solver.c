#include <stdio.h>
#include <stdlib.h>

void le_arquivo(char *nome, int mat[][9]){
    FILE *arq = fopen(nome,"r");
    if(arq == NULL){
        printf("Erro de leitura\n");
        system("pause");
        exit(1);
    }

    int i,j;
    for(i=0; i< 9; i++)
        for(j=0; j< 9; j++)
            fscanf(arq,"%d",&mat[i][j]);

    fclose(arq);
}
void mostra_sudoku(int m[9][9])
{
    printf(" -----------------\n");
    printf("|%d %d %d|%d %d %d|%d %d %d|\n|%d %d %d|%d %d %d|%d %d %d|\n|%d %d %d|%d %d %d|%d %d %d|\n|-----------------|\n|%d %d %d|%d %d %d|%d %d %d|\n|%d %d %d|%d %d %d|%d %d %d|\n|%d %d %d|%d %d %d|%d %d %d|\n|-----------------|\n|%d %d %d|%d %d %d|%d %d %d|\n|%d %d %d|%d %d %d|%d %d %d|\n|%d %d %d|%d %d %d|%d %d %d|\n -----------------"
           ,m[0][0],m[0][1],m[0][2],m[0][3],m[0][4],m[0][5],m[0][6],m[0][7],m[0][8]
           ,m[1][0],m[1][1],m[1][2],m[1][3],m[1][4],m[1][5],m[1][6],m[1][7],m[1][8]
           ,m[2][0],m[2][1],m[2][2],m[2][3],m[2][4],m[2][5],m[2][6],m[2][7],m[2][8]
           ,m[3][0],m[3][1],m[3][2],m[3][3],m[3][4],m[3][5],m[3][6],m[3][7],m[3][8]
           ,m[4][0],m[4][1],m[4][2],m[4][3],m[4][4],m[4][5],m[4][6],m[4][7],m[4][8]
           ,m[5][0],m[5][1],m[5][2],m[5][3],m[5][4],m[5][5],m[5][6],m[5][7],m[5][8]
           ,m[6][0],m[6][1],m[6][2],m[6][3],m[6][4],m[6][5],m[6][6],m[6][7],m[6][8]
           ,m[7][0],m[7][1],m[7][2],m[7][3],m[7][4],m[7][5],m[7][6],m[7][7],m[7][8]
           ,m[8][0],m[8][1],m[8][2],m[8][3],m[8][4],m[8][5],m[8][6],m[8][7],m[8][8]);
            return;
}
int sudoku_confere(int m[9][9])//Confere se ainda há espaços em branco no sudoku
{
    int soma=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0; j<9; j++)
        {
            if(m[i][j]==0)//Se haver espaço em branco , retorna 0 , se nao retorna 1
                return 0;
        }
    }
    return 1;
}
void sudoku_uma_possibilidade(int m[][9])//Completa as casas do sudoku que possuem apenas
                                        //uma possibilidade.(resolve alguns sudokus mais simples apenas assim).
{
    int soma=0,num=0;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(m[i][j]==0){
                num=0;
                soma=0;
                for(int k=1;k<10;k++)
                {
                    if(sudoku_nmr_confere(m,i,j,k)==1){
                    num=k;
                    soma=soma+1;}
                    if(k==9 && soma==1)//Se a soma de possibilidades for 1 e nao houver mais opçoes , entao substitui o numero.
                        m[i][j]=num;
                }
            }
        }
    }
    return;
}

int sudoku_linha(int v[][9],int x,int linha)//Confere se existe um numero "x" na linha desejada.
{
    for(int i=0;i<9;i++)
    {
        if(v[linha][i]==x)
            return 0;//Se o numero exixtir na linha retorna 0;
    }
    return 1;
}
int sudoku_coluna(int v[][9],int x , int coluna)//Confere se existe um numero "x" na coluna desejada.
{
    for(int i=0;i<9;i++)
    {
        if(v[i][coluna]==x)
            return 0;//Se o numero exixtir na coluna retorna 0;
    }
    return 1;
}
int sudoku_bloco(int v[][9], int l, int c, int x)//Confere se existe um numero "x" no bloco sendo analisado.
{
    int l1 = (l/3)*3;//Determina a linha inicial do bloco.
    int c1 = (c/3)*3;//Determina a coluna inicial do bloco.
    for(int i=l1;i<l1+3;i++)
    {
        for(int j=c1;j<c1+3;j++)
        {
            if(v[i][j]==x)//Se o numero exixtir no bloco retorna 0;
                return 0;
        }
    }
    return 1;
}
int sudoku_nmr_confere(int m[][9],int l,int c,int k)//Basicamente confere se o numero analisado pode ser colocado na posição.
{
    if(sudoku_bloco(m,l,c,k)==1 && sudoku_coluna(m,k,c)==1 && sudoku_linha(m,k,l)==1)
        return 1;//Se o numero for elegivel , retorna 1.
    else
        return 0;//Se nao for elegivel , retorna 0;
}
int sudoku_resolve(int m[9][9],int l,int c)
{
    int k,qtd_colunas=9,qtd_linhas=9;
    if(m[l][c]!=0){  //Se a posicao ja esta preenchida.
        if(c+1==qtd_colunas){ //Se ja percorreu toda a linha, entao deve pular para proxima linha.
            if(l+1==qtd_linhas)
                return 1; //Se nao existe proxima linha, entao tudo ja foi preenchido com sucesso.
            return sudoku_resolve(m,l+1,0); //Se existe proxima linha entao vai para ela.
        }
        else //A linha ainda nao acabou, continua percorrendo ela.
            return sudoku_resolve(m,l,c+1);
    }
    for(k=1;k<10;k++){ //K eh o valor que vai tentar inserir.
        if(sudoku_nmr_confere(m,l,c,k)==1){ //Se o valor k pode ser colocado na posicao (i,j) da matriz.
            m[l][c]=k;
            if(c+1==qtd_colunas){ //Se chegou no fim da linha.
                if(l+1==qtd_linhas)return 1; //Se esta eh a ultima posicao a ser preechida.
                if(sudoku_resolve(m,l+1,0)==1)return 1;
                else m[l][c]=0; //Volta o valor da posicao para 0, ja que o k anteriormente atribuido nao serve.
            }
            else  //Nao chegou no fim da linha.
                if(sudoku_resolve(m,l,c+1)==1)return 1;
                else m[l][c]=0;
        }
    }
    return 0;
}

int main()
{
    int mat[9][9],q=0,i,j,a=0;
    le_arquivo("sudoku.txt", mat);
    while(q<81)//Preeche todos os valores com apenas uma possibilidade,pode resolver o sudoku em alguns casos.
    {          //Vai ate 81 para ter certeza que nao há mas numeros para serem colocados.
        sudoku_uma_possibilidade(mat);
        q++;
    }
    if(sudoku_confere(mat)!=1)//Se o sudoku ainda estiver espaços em branco , inicia o metodo de substuição dos valores .
        sudoku_resolve(mat,0,0);
    mostra_sudoku(mat);//Mostra a matriz pronta.
    return 0;

}
