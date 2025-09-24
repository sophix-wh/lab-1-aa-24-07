#include <iostream>
#include <string>
#include <limits>

using namespace std; 

struct Pipe {
    string name;
    float length = -1; // -1 значит что пользователь не вводил ничего 
    int diametr = -1;  
    bool repair;
};

struct Compress {
    string name;
    int count = -1;          
    int count_working = -1;  
    string classification;
    bool working;
};

void Menu(Pipe& truba, Compress& compstation) {
    while (true)
    {
        cout << "\nВыберите тип:\n 1. Труба \n 2. Компрессорная станция\n 3. Показать все\n 4. Выход\n";
        int type;
        cin >> type;
        if (cin.fail()) {
            cout << "Ошибка!" << endl;
            cout << "Введите корректное число (1-4)" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        
        if (type == 4) {
            cout << "Выход из программы." << endl;
            break;
        }
        
        switch (type)
        {
        case 1:
            cout << "Выберите опцию:\n 1. Добавить трубу \n 2. Длина трубы\n 3. Диаметр трубы\n 4. Ремонт\n";
            int option;
            cin >> option;
            if (cin.fail()) {
                cout << "Ошибка!" << endl;
                cout << "Введите корректное число (1-4)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (option)
            {
            case 1:
                cout << "Введите название трубы: ";
                cin >> truba.name;
                break;
            case 2:
                cout << "Введите длину трубы (км): ";
                cin >> truba.length;
                if (cin.fail() || truba.length < 0) {
                    cout << "Ошибка!" << endl;
                    cout << "Введите корректное положительное число" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    truba.length = -1;
                }
                break;
            case 3:
                cout << "Введите диаметр трубы (мм): ";
                cin >> truba.diametr;
                if (cin.fail() || truba.diametr < 0) {
                    cout << "Ошибка!" << endl;
                    cout << "Введите корректное положительное число" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    truba.diametr = -1;
                }
                break;
            case 4:
                cout << "Труба в ремонте? (0 - нет, 1 - да): ";
                cin >> truba.repair;
                if (cin.fail()) {
                    cout << "Ошибка!" << endl;
                    cout << "Введите 0 или 1" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            break;
        case 2:
            cout << "Выберите опцию:\n 1. Добавить КС \n 2. Количество цехов \n 3. Количество работающих предприятий\n 4. Классификация\n 5. Ремонт\n";
            int option2;
            cin >> option2;
            if (cin.fail()) {
                cout << "Ошибка!" << endl;
                cout << "Введите корректное число (1-5)" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            switch (option2)
            {
            case 1:
                cout << "Введите название КС: ";
                cin >> compstation.name;
                break;
            case 2:
                cout << "Введите количество предприятий: ";
                cin >> compstation.count;
                if (cin.fail() || compstation.count < 0) {
                    cout << "Ошибка!" << endl;
                    cout << "Введите корректное положительное число" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    compstation.count = -1;
                }
                break;
            case 3:
                cout << "Введите количество работающих предприятий: ";
                cin >> compstation.count_working;
                if (cin.fail() || compstation.count_working < 0) {
                    cout << "Ошибка!" << endl;
                    cout << "Введите корректное положительное число" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    compstation.count_working = -1;
                }
                break;
            case 4:
                cout << "Введите классификацию: ";
                cin >> compstation.classification;
                break;
            case 5:
                cout << "КС на ремонте? (0 - нет, 1 - да): ";
                cin >> compstation.working;
                if (cin.fail()) {
                    cout << "Ошибка!" << endl;
                    cout << "Введите 0 или 1" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                break;
            }
            break;
        case 3:
            cout << "\nПараметры трубы: \n" << "Название: " << (truba.name.empty() ? "неизвестно" : truba.name) 
                 << "\nДлина: " << (truba.length == -1 ? "неизвестно" : to_string(truba.length) + " км")
                 << "\nДиаметр: " << (truba.diametr == -1 ? "неизвестно" : to_string(truba.diametr) + " мм")
                 << "\nВ ремонте: " << (truba.repair ? "да" : "нет");
            
            cout << "\n\nПараметры КС: \n" << "Название: " << (compstation.name.empty() ? "неизвестно" : compstation.name)
                 << "\nКоличество предприятий: " << (compstation.count == -1 ? "неизвестно" : to_string(compstation.count))
                 << "\nКоличество работающих предприятий: " << (compstation.count_working == -1 ? "неизвестно" : to_string(compstation.count_working))
                 << "\nКлассификация: " << (compstation.classification.empty() ? "неизвестно" : compstation.classification)
                 << "\nВ ремонте: " << (compstation.working ? "да" : "нет");
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
            break;
        }
    }
}

int main()
{
    Pipe truba;
    Compress compstation;
    Menu(truba, compstation);
    
    return 0;
}