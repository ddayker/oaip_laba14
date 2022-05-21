#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <stdexcept>
#include <memory>

using namespace std;


#define LN { std::cout << __LINE__ << std::endl; }
#define DEB(x) { std::cout << #x << "=(" << (x) << ") "; }

static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "┏", ch_rddia = "┓", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";


struct Tree
{
  int key;
  string text;
  Tree* Left, * Right;
};

Tree* makeTree(Tree* Root);       //Создание дерева
Tree* list(int i, string s);       //Создание нового элемента
Tree* insertElem(Tree* Root, int key, char* s);  //Добавление нового элемента
Tree* search(Tree* n, int key);   //Поиск элемента по ключу
Tree* delet(Tree* Root, int key); //Удаление элемента по ключу
void view(Tree* t, int level);    //Вывод дерева
void delAll(Tree* t);             //Очистка дерева
void kolichNodesWithEvenValues(Tree* t);
int check(Tree* t);
int getMaxDepth(Tree* t, int depth);


int c = 0;         //количество слов
Tree* Root = NULL;   //указатель корня
int sum = 0;
int countK = 0;
int leaves = 0;
int evenValues = 0;


void print(Tree const * node, bool high = true, vector<string> const & lpref = vector<string>(), vector<string> const & cpref = vector<string>(), vector<string> const & rpref = vector<string>(), bool root = true, bool left = true, shared_ptr<vector<vector<string>>> lines = nullptr) {
    if (!node) return;
    typedef vector<string> VS;
    auto VSCat = [](VS const & a, VS const & b){ auto r = a; r.insert(r.end(), b.begin(), b.end()); return r; };
    if (root) lines = make_shared<std::vector<VS>>();
    if (node->Left)
        print(node->Left, high, VSCat(lpref, high ? VS({" ", " "}) : VS({" "})), VSCat(lpref, high ? VS({ch_ddia, ch_ver}) : VS({ch_ddia})), VSCat(lpref, high ? VS({ch_hor, " "}) : VS({ch_hor})), false, true, lines);
    string probel=" ";
    string sk1 ="[";
    string sk2 ="]";
    auto sval = sk1+to_string(node->key)+probel+node->text+sk2;
    
    size_t sm = left || sval.empty() ? sval.size() / 2 : ((sval.size() + 1) / 2 - 1);
    for (size_t i = 0; i < sval.size(); ++i)
        lines->push_back(VSCat(i < sm ? lpref : i == sm ? cpref : rpref, {std::string(1, sval[i])}));
    if (node->Right)
        print(node->Right, high, VSCat(rpref, high ? VS({ch_hor, " "}) : VS({ch_hor})), VSCat(rpref, high ? VS({ch_rddia, ch_ver}) : VS({ch_rddia})), VSCat(rpref, high ? VS({" ", " "}) : VS({" "})), false, false, lines);
    if (root) {
        VS out;
        for (size_t l = 0;;++l) {
            bool last = true;
            std::string line;
            for (size_t i = 0; i < lines->size(); ++i)
                if (l < (*lines).at(i).size()) {
                    line += lines->at(i)[l];
                    last = false;
                } else line += " ";
            if (last) break;
            out.push_back(line);
        }
        for (size_t i = 0; i < out.size(); ++i)
            std::cout << out[i] << std::endl;
    }
}

int input(int a, int b){
    int input;
    
    while(true){
        cout << "--> ";
        cin >> input;
        if (cin.fail())
        {
            cout << "\nОшибка, повторите ввод:" << endl;
            cin.clear();
            while(cin.get()!='\n');
            
        }
        else if ( input<a || input>b) cout << "\nОшибка, повторите ввод:" << endl;
        else break;
    }
    
    return input;
}

int menu(){
    int choice;
    printf( "---------------------------------------------------------\n");
    printf( "|                    ВЫБОР ДЕЙСТВИЯ                     |\n");
    printf( "---------------------------------------------------------\n");
    printf( "| 1) Создание дерева                                    |\n");
    printf( "| 2) Добавление элемента                                |\n");
    printf( "| 3) Поиск по ключу                                     |\n");
    printf( "| 4) Удаление элемента                                  |\n");
    printf( "| 5) Вывод дерева                                       |\n");
    printf( "| 6) Определить глубину дерева                          |\n");
    printf( "| 7) Определить количество узлов с четными ключами      |\n");
    printf( "| 8) Удаление дерева                                    |\n");
    printf( "| 0) Выход из программы                                 |\n");
    printf( "---------------------------------------------------------\n");
    
    
    choice = input(0,8);
    return choice;
}


Tree* makeTree(Tree* Root)    //Создание дерева
{
  int key;
  string s;
  if (Root == NULL)
  {
    cout << "\n------------СОЗДАНИЕ ДЕРЕВА------------";
    cout << "\nВведите ключ корня: ";
      key = input(0,1410065407);
    cout << "Введите слово корня --> "; cin >> s;
    Root = list(key, s);  // установка указателя на корень
  }
  else cout<<"Дерево уже было создано.\n";
  return Root;
}

Tree* list(int i, string s)     //Создание нового элемента
{
  Tree* t = new Tree;
  t->key = i;
  t->text = s;
  t->Left = t->Right = NULL;
  return t;
}

Tree* insertElem(Tree* t)  //Добавление нового элемента
{
    if (t==NULL){
        cout << "Бинарное дерево еще не было создано!\n\n";
    return t;}
  Tree* Prev;       // Prev - элемент перед текущим
  int find = 0;        // признак поиска
  Prev = t;
    
    int key;
    string s;
    
    cout << "\nВведите ключ ";
    key = input(0,1410065407);
    cout << "Введите слово --> ";
    cin >> s;
    
  while (t && !find)
  {
    Prev = t;
      if (key == t->key){
      find = 1;
          cout<<"Элемент с таким ключем уже существует!\n";}
    else
      if (key < t->key) t = t->Left;
      else t = t->Right;
  }
    
  if (!find)
  {
    t = list(key, s);
    if (key < Prev->key)
      Prev->Left = t;
    else
      Prev->Right = t;   
  }
  return t;
}

Tree* delet(Tree* Root, int key)  //Удаление элемента по ключу
{  // Del, Prev_Del - удаляемый элемент и его предыдущий ;
  // R, Prev_R - элемент, на который заменяется удаленный, и его родитель;
  Tree* Del, * Prev_Del, * R, * Prev_R;
  Del = Root;
  Prev_Del = NULL;
  while (Del != NULL && Del->key != key)//поиск элемента и его родителя
  {
    Prev_Del = Del;
    if (Del->key > key)
      Del = Del->Left;
    else
      Del = Del->Right;
  }
  if (Del == NULL)              // элемент не найден
  {
    puts("\nЭлемент с таким ключем не найден!\n");
    return Root;
  }
  if (Del->Right == NULL) // поиск элемента R для замены
    R = Del->Left;
  else
    if (Del->Left == NULL)
      R = Del->Right;
    else
    {
      Prev_R = Del; //поиск самого правого элемента в левом поддереве
      R = Del->Left;
      while (R->Right != NULL)
      {
        Prev_R = R;
        R = R->Right;
      }
      if (Prev_R == Del) // найден элемент для замены R и его родителя Prev_R
        R->Right = Del->Right;
      else
      {
        R->Right = Del->Right;
        Prev_R->Right = R->Left;
        R->Left = Prev_R;
      }
    }
  if (Del == Root) Root = R;  //удаление корня и замена его на R
  else
    // поддерево R присоединяется к родителю удаляемого узла
    if (Del->key < Prev_Del->key)
      Prev_Del->Left = R; // на левую ветвь
    else
      Prev_Del->Right = R;  // на правую ветвь
  int tmp = Del->key;
  cout << "\nУдален элемент с ключом " << tmp <<".\n"<< endl;
  delete Del;
  return Root;
}



Tree* search(Tree *Root, int key) //поиск по дереву
{
    
    if (Root == NULL){
        return NULL;
    
    }
    if (Root->key == key)
        return Root;
    if (key < Root->key)
    {
        if (Root->Left != NULL)
            return search(Root->Left, key);
        else return NULL;
    }
    else
    {
        if (Root->Right != NULL)
            return search(Root->Right, key);
        else return NULL;
    }
}



void view(Tree* t, int level) //Вывод дерева
{
  if (t)
  {
    view(t->Right, level + 1);  //вывод правого поддерева
    for (int i = 0; i < level; i++)
      cout << "   ";
    int tm = t->key;
    cout << tm << ' ';
    cout<<(t->text);
    view(t->Left, level + 1);  //вывод левого поддерева
  }
}

void delAll(Tree* t) //Очистка дерева
{
  if (t != NULL)
  {
    delAll(t->Left);
    delAll(t->Right);
    delete t;
  }
}


void kolichNodesWithEvenValues(Tree* t) {
  if (t) {
    kolichNodesWithEvenValues(t->Right);
    if (t->key % 2 == 0)
      ++evenValues;
    kolichNodesWithEvenValues(t->Left);
  }
}

int check(Tree* t){
    if (t==NULL){
        cout << "Бинарное дерево пустое.\n\n";
    return 1;}
    else return 0;
}

int getMaxDepth(Tree* t, int depth)
    {
        if (t == NULL)
    return depth;
        else
    return max(getMaxDepth(t->Left, depth + 1), getMaxDepth(t->Right, depth + 1));
    }
