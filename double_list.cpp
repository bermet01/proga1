#include <iostream>
#include <stdio.h>
#include <cstring>
using namespace std;

struct Double_List //структура данных
{
    int Data; //информационное поле
    Double_List* Next, //адресное поле на следующий элемент
    * Prior; //адресное поле на предыдущий элемент
};
Double_List** Head; //указатель на первый элемент списка
Double_List* Current; //указатель на текущий элемент списка (при необходимости)

//создание двунаправленного списка (добавления в конец)
void Make_Double_List(int n, Double_List** Head, Double_List* Prior)
{
    if (n > 0)
    {
        (*Head) = new Double_List(); //выделяем память под новый элемент
        cout << "Введите значение ";
        cin >> (*Head)->Data; //вводим значение информационного поля
        (*Head)->Prior = Prior;
        (*Head)->Next = NULL;//обнуление адресного поля
        Make_Double_List(n - 1, &((*Head)->Next), (*Head));
    }
    else (*Head) = NULL;
}
//печать двунаправленного списка
void Print_Double_List(Double_List* Head)
{
    if (Head != NULL)
    {
        cout << Head->Data << "\t";
        Print_Double_List(Head->Next);    //переход к следующему элементу
    }
    else cout << "\n";
}
//вставка элемента с заданным номером в двунаправленный список
Double_List* Insert_Item_Double_List(Double_List* Head, int Number, int DataItem)
{
    Number--;
    Double_List* NewItem = new(Double_List); // выделяем память для нового элемента
    NewItem->Data = DataItem;
    NewItem->Prior = NULL;
    NewItem->Next = NULL;
    if (Head == NULL) //список пуст
    {
        Head = NewItem;
    }
    else //список не пуст
    {
        Double_List* Current = Head;
        for (int i = 1; i < Number && Current->Next != NULL; i++)
            Current = Current->Next;
        if (Number == 0) //вставляем новый элемент на первое место
        {
            NewItem->Next = Head;
            Head->Prior = NewItem;
            Head = NewItem;
        }
        else //вставляем новый элемент на не первое место
        {
            if (Current->Next != NULL) Current->Next->Prior = NewItem;
            NewItem->Next = Current->Next;
            Current->Next = NewItem;
            NewItem->Prior = Current;
            Current = NewItem;
        }
    }
    return Head;
}
/*удаление элемента с заданным номером из двунаправленного списка*/
Double_List* Delete_Item_Double_List(Double_List* Head, int Number)
{
    Double_List* ptr;//вспомогательный указатель
    Double_List* Current = Head;
    for (int i = 1; i < Number && Current != NULL; i++)
        Current = Current->Next;
    if (Current != NULL) //проверка на корректность
    {
        if (Current->Prior == NULL) //удаляем первый элемент
        {
            Head = Head->Next;
            delete(Current);
            Head->Prior = NULL;
            Current = Head;
        }
        else //удаляем непервый элемент
        {
            if (Current->Next == NULL) //удаляем последний элемент
            {
                Current->Prior->Next = NULL;
                delete(Current);
                Current = Head;
            }
            else //удаляем непервый и непоследний элемент
            {
                ptr = Current->Next;
                Current->Prior->Next = Current->Next;
                Current->Next->Prior = Current->Prior;
                delete(Current);
                Current = ptr;
            }
        }
    }
    return Head;
}
//поиск элемента в двунаправленном списке
bool Find_Item_Double_List(Double_List* Head, int DataItem)
{
    Double_List* ptr; //вспомогательный указатель
    ptr = Head;
    while (ptr != NULL) //пока не конец списка
    {
        if (DataItem == ptr->Data) return true;
        else ptr = ptr->Next;
    }
    return false;
}
//проверка пустоты двунаправленого списка
bool Empty_Double_List(Double_List* Head)
{
    if (Head != NULL)  return false;
    else  return true;
}
//освобождение памяти, выделенной под двунаправленный список
void Delete_Double_List(Double_List* Head)
{
    if (Head != NULL)
    {
        Delete_Double_List(Head->Next);
        delete Head;
    }
}
/*
int main() {
    Double_List** start;
    Double_List* start_previous;
   
    short n;
    cout << "1.Sozdat dvusvyaznui list" << endl << "2.Pechat'" << endl << "3.Vstavka" << endl << "4.Udalenie" << endl
        << "5.Poisk" << endl << "6.Proverka" << endl << "7.Osvobozhdenie" << endl;
    cout << "Vyberite function:" << endl;
    cin >> n;

    while (n) {
        switch (n) {
        case (1):
            int items;
            cout << " vvedite nods:";
            cin >> items;
            
            Make_Double_List(items,start,start_previous);
            break;
        case(2):
            Print_Double_List(*start);
            break;
        case(3):
            int item, prior;
            cout << " vvedite chislo: ";
            cin >> item;
            cout << " vvedite edo poryadok: ";
            cin >> prior;
            Insert_Item_Double_List(*start, item, prior);
            break;
        case(4):
            int item_delete;
            cout << " vvedite chislo dlya udalenia: ";
            cin >> item_delete;
            Delete_Item_Double_List(*start, item_delete);
            break;
        case(5):
            int item_find;
            cout << "vvedite chislo dlya poiska: ";
            cin >> item_find;
            if (Find_Item_Double_List(*start, item_find))
                cout << "chislo nashlos' )";
            else cout << "chislo ne nashlos' (";
            break;
        case(6):
            if (Empty_Double_List(*start)) cout << "spisok ne pustoi";
            else cout << "spisok pustoi";
            break;
        case(7):
            Delete_Double_List(*start);
            break;
        }
    }
}*/