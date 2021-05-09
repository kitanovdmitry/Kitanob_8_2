/*
Автор: Китанов Дмитрий
Группа: СБС-001, подгруппа 2
Задача №8, вариант 2
Цель: создать дерево объектов в соответствии с условиями задания
*/

#include <iostream>
#include <climits>

using namespace std;

struct our_struct
{
    int int_field;
    our_struct* left, * right;
};

class OurClass
{
public:
    int x;
};

void Add_Elem(our_struct*& address, int val1, int val2, int val3)
{
    static const size_t NumElems = 5;
    
    our_struct* ptrs[NumElems];
    for (size_t i = 0; i < NumElems; ++i)
    {
        ptrs[i] = new our_struct;
    }

    ptrs[0]->int_field = val1;
    ptrs[0]->left = ptrs[1];
    ptrs[0]->right = ptrs[2];

    ptrs[1]->int_field = val2;
    ptrs[1]->left = nullptr;
    ptrs[1]->right = ptrs[2];

    ptrs[2]->int_field = val3;
    ptrs[2]->left = ptrs[1];
    ptrs[2]->right = nullptr;

    if (address == nullptr)
    {
        address = ptrs[0];
    }
    else
    {
        our_struct* p = address;
        
        while (p->left->left != nullptr)
        {
            p = p->left->left;
        }

        p->left->left = p->right->right = ptrs[0];
    }
    return;
}

void Free_Memory(our_struct*& elem_address, int numbers_of_elements)

{
    if (!elem_address) return;
    our_struct* sup_address = elem_address;
    int numbers_of_cells = numbers_of_elements / 3;

    for (int i = 0; i < numbers_of_cells; i++)
    {
        if ((i == 0) && (numbers_of_cells > 1))
        {
            for (int j = 0; j < (numbers_of_cells - 1); j++)
            {
                sup_address = sup_address->left->left;
            }
        }

        delete sup_address->left;
        delete sup_address->right;
        delete sup_address;

        if (numbers_of_cells > 1)
        {
            sup_address = elem_address;
        }
    }
    return;
}

void Print_Cell(our_struct* address, int number_of_elemets)

{
    our_struct* sup_address = 0;
    int counter = 0;

    if (address == 0) return;

    for (int i = 0; i < number_of_elemets; i++)
    {
        if (counter > 1)
        {
            sup_address = address;
            sup_address = sup_address->right;
        }
        else if (counter == 0)
            {
                if (i == 0)
                {
                    sup_address = address;
                }
                else
                {
                    sup_address = sup_address->right;
                }
            }
            else sup_address = sup_address->left;

        if ((counter == 0) && (i != 0))
        {
            address = sup_address;
        }

        if ((i != (number_of_elemets - 1)) && (i != (number_of_elemets - 2)))
        {
            cout << " element = " << sup_address->int_field << "\n";
            cout << "and has point to " << sup_address->left->int_field << " and to " << sup_address->right->int_field << "\n";
        }
        else
        {
            if (i == (number_of_elemets - 2))
            {
                cout << " element = " << sup_address->int_field << "\n";
                cout << "and has point to 1-st elem of next cell and to " << sup_address->right->int_field << "\n";
            }
            else
            {
                cout << " element = " << sup_address->int_field << "\n";
                cout << "and has point to 1-st elem of next cell and to " << sup_address->left->int_field << "\n";
            }
        }

        if (counter < 2)
        {
            counter = counter + 1;
        }
        else counter = 0;
    }
    return;
}

int main()
{
    int number_of_obj = 0;
    bool typeFail;

    do
    {
        cout << "Enter a number of objects in the structure:(3 or 6)\n";
        cin >> number_of_obj;

        typeFail = cin.fail();
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }     while (((number_of_obj % 3) != 0) || (number_of_obj > 6) || (number_of_obj <= 0) || (typeFail));

    OurClass* obj = new OurClass[number_of_obj];

    for (int i = 0; i < number_of_obj; i++)
    {
        do
        {
            cout << "Enter an integer value of the " << i + 1 << " object\n";
            cin >> obj[i].x;

            typeFail = cin.fail();
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }         while (typeFail);
    }

    our_struct* start_elem = 0;

    for (int i = 0; i < number_of_obj; i++)
    {
        if (((i + 1) % 3) == 0)
        {
            Add_Elem(start_elem, obj[i - 2].x, obj[i - 1].x, obj[i].x);
        }
    }

    Print_Cell(start_elem, number_of_obj);
    Free_Memory(start_elem, number_of_obj);
    return 0;
}
