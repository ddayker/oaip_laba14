#include "functions.h"



/*
 Создание и обработка структур типа «дерево»
 Разработать проект для обработки дерева поиска, каждый элемент которого содержит целочисленный ключ и строку текста,как показано в примере 2 (ввод исходной информации рекомендуется записать в файл). В программе должны быть реализованы следующие возможности:
 –    создание дерева;
 –    добавление новой записи;
 –    поиск информации по заданному ключу;
 –    удаление информации с заданным ключом;
 –    вывод информации;
 –    решение индивидуального задания;(см. ниже для оценки 9 –выбрать 2 задания, первое - свой вариант, второе –по выбору)
 –    освобождение памяти при выходе из программы.
 */


int main()
{
    int key = 0;
    string s;
  Tree* rc;
  while(1)
  {
      
    switch (menu())
    {
    case 1:
      Root = makeTree(Root);
      break;
    case 2:
      insertElem(Root);
      break;
    case 3:
            if (check(Root))  {
                break;
            }
      cout << "\nВведите ключ ";
      key = input(0,1410065407);
      rc = search(Root, key);
            if(rc !=NULL)
      cout << "Элемент найден. Содержание элемента --> "<<(rc->text)<<".\n\n";
            else cout <<"Элемент не найден!\n\n";
      break;
    case 4:
            if (check(Root))  {
                break;
            }
      cout << "\nВведите удаляемый ключ ";
        key = input(0,1410065407);
      Root = delet(Root, key);
      break;
    case 5:
            if (check(Root))  {
                break;
            }
      else
      {
          cout<<"\nБинарное дерево ▶\n"<<endl;
          print(Root, true);
          cout<<"\n\n";
      }
      break;
        case 6:
            if (check(Root))  {
                break;
            }
           cout<<"Глубина бинарного дерева = "<< getMaxDepth(Root, 0)<<" .\n\n";
            break;
    case 7:
            if (check(Root))  {
                break;
            }
            kolichNodesWithEvenValues(Root);
            printf("Количество узлов с четными значениями: %d\n", evenValues);
            evenValues = 0;
      break;
    case 8:
            if (check(Root))  {
                break;
            }
            delAll(Root);
            Root = NULL;
            cout<<"Бинарное дерево удалено!\n\n";
      break;
 
    case 0:
            cout<<"ПРОГРАММА ЗАВЕРШЕНА...\n";
      exit(0);
    }
  }
}

