#include<bits/stdc++.h>
#define ll long long int
#define MAX 10000

using namespace std;

//Struct para armazenar dados de cada nó da árvore
typedef struct {
  //Armazena os índices de começo e fim do nó
  int inicio, fim;
  //Armazena o tamanho da substring representada pelo nó
  int len;
  //Armazena as arestas de inserção do nó, neste caso para os 26 caracteres dos alfabeto
  int insAresta[26];

  //Armazena a aresta de sufixo do nó
  int sufAresta;

} no;

//Função para fazer a inserção na árvore
void inserir (string st, no arv[], int &ptr, int &noAtual, int ind) {
  //Procurar por determinado nó A, tal que A adicionado do caractere st[ind]
  //ao seu começo e final (st[ind] + A + st[ind]) seja o maior palíndromo com sufixo st[ind]
  //Isso é feito pelo percurso das arestas de sufixo até encontrar A
  
  //Variável para encontrar nó A
  int aux = noAtual;
  //Loop até encontrar o nó A, para se o caractere de ínicio condizer com o final e se o palíndromo não estar fora do alcance do índice
  while (ind - arv[aux].len < 1 || st[ind] != st[ind - arv[aux].len - 1]) {
    //Iterar pela aresta de sufixo
    aux = arv[aux].sufAresta;
  }
  //Checar se (st[ind] + A + st[ind]) já existe na árvore
  if (arv[aux].insAresta[st[ind] - 'a']) {
    //Nó já existe
    noAtual = arv[aux].insAresta[st[ind] - 'a'];
    return;
  }
  //Criar novo nó, aumentando o tamanho da árvore
  ptr++;
  //Ligar a aresta de inserção dos nós
  arv[aux].insAresta[st[ind] - 'a'] = ptr;
  //Calcular tamanho da substring
  arv[ptr].len = arv[aux].len + 2;
  //Novo nó tem final no índice atual
  arv[ptr].fim = ind;
  //Subtrair tamanho para determinar começo da substring do nó
  arv[ptr].inicio = ind - arv[ptr].len + 1;

  //Assim é criado o novo nó e atualizada a aresta de inserção que refere a ele
  //Mas ainda é necessário determinar a aresta de sufixo do nó
  //Para isso procura-se um nó A em que (st[ind] + A + st[ind]) é o maior sufixo palindrômico para o nó
  aux = arv[aux].sufAresta;
  //Novo nó vira o nó atual
  noAtual = ptr;
  //Caso especial se o palíndromo ter tamanho igual a 1
  if (arv[noAtual].len == 1) {
    //Caso tenha sua aresta de sufixo liga ao nó da raiz nula, na posição 2
    arv[noAtual].sufAresta = 2;
    return;
  }
  //Loop até encontrar A
  while (ind - arv[aux].len < 1 || st[ind] != st[ind - arv[aux].len - 1]) {
    //Iterar pela aresta de sufixo
    aux = arv[aux].sufAresta;
  }
  //Nó A encontrado, conectando a aresta de sufixo
  arv[noAtual].sufAresta = arv[aux].insAresta[st[ind] - 'a'];
  return;
}

int main () {
  ifstream in;
  ofstream out;
  in.open("input.txt");
  out.open("output.txt");
  string staux;
  while (getline(in, staux)) {

  //-------------------------------------------------

  //String a ser lida
  string st = staux;
  //Árvore Palindrômica
  no arv[MAX] = {};
  //Índice 1 = Raiz imaginária de tamanho -1
  arv[1].len = -1;
  //Índice 2 = Raiz nula de tamanho 0
  arv[2].len = 0;
  //Ambas possuem aresta de sufixo para a raiz imaginária
  arv[1].sufAresta = 1;
  arv[2].sufAresta = 1;
  //Armazena número final de nós
  int ptr = 2;
  //Armazena nó atual para inserção
  int noAtual = 1;

  for (int i = 0; i < st.length(); i++) {
    //Faz a inserção para todos os caracteres da string
    inserir(st, arv, ptr, noAtual, i);
  }

  //Escrever as substrings palindrômicas distintas de st
  out << "Substrings palindromicas distintas de " << st << endl;
  for (int i = 3; i <= ptr; i++) {
    for (int j = arv[i].inicio; j <= arv[i].fim; j++) {
      out << st[j];
    }
    out << endl;
  }
  out << endl;

  //-------------------------------------------------

  }
  in.close();
  out.close();
  return 0;
}