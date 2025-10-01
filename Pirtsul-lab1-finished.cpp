#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

struct Pipe {
    string name;
    float length = -1;
    int diameter = -1;
    bool repair;
};

struct Compress {
    string name;
    int count = -1;
    int count_working = -1;
    string classification;
    bool working;
};

void clearInputBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// проверяю создана ли труба
bool isPipeCreated(const Pipe& pipe) {
    return !pipe.name.empty() || pipe.length != -1 || pipe.diameter != -1;
}

// проверяю создана ли труба
bool isStationCreated(const Compress& compstation) {
    return !compstation.name.empty() || compstation.count != -1 ||
        compstation.count_working != -1 || !compstation.classification.empty();
}

// есть ли данные
bool hasData(const Pipe& pipe, const Compress& compstation) {
    return isPipeCreated(pipe) || isStationCreated(compstation);
}

// ввод данных трубы с консоли
void readPipeFromConsole(Pipe& pipe) {
    cout << "Введите название трубы: ";
    clearInputBuffer();
    getline(cin, pipe.name);

    cout << "Введите длину трубы (км): ";
    cin >> pipe.length;
    while (cin.fail() || pipe.length < 0) {
        cout << "Ошибка! Введите корректное положительное число: ";
        cin.clear();
        clearInputBuffer();
        cin >> pipe.length;
    }

    cout << "Введите диаметр трубы (мм): ";
    cin >> pipe.diameter;
    while (cin.fail() || pipe.diameter < 0) {
        cout << "Ошибка! Введите корректное положительное число: ";
        cin.clear();
        clearInputBuffer();
        cin >> pipe.diameter;
    }

    cout << "Труба в ремонте? (0 - нет, 1 - да): ";
    cin >> pipe.repair;
    while (cin.fail()) {
        cout << "Ошибка! Введите 0 или 1: ";
        cin.clear();
        clearInputBuffer();
        cin >> pipe.repair;
    }

    cout << "Труба '" << pipe.name << "' успешно создана!\n";
}

// вывод данных трубы
void printPipe(const Pipe& pipe) {
    cout << "\nПараметры трубы:\n";
    cout << "Название: " << (pipe.name.empty() ? "неизвестно" : pipe.name) << "\n";
    cout << "Длина: " << (pipe.length == -1 ? "неизвестно" : to_string(pipe.length) + " км") << "\n";
    cout << "Диаметр: " << (pipe.diameter == -1 ? "неизвестно" : to_string(pipe.diameter) + " мм") << "\n";
    cout << "В ремонте: " << (pipe.repair ? "да" : "нет") << "\n";
}

// редактирование статуса ремонта трубы
void editPipeRepair(Pipe& pipe) {
    if (!isPipeCreated(pipe)) {
        cout << "Ошибка! Сначала создайте трубу.\n";
        return;
    }

    cout << "Текущий статус ремонта трубы '" << pipe.name << "': "
        << (pipe.repair ? "в ремонте" : "работает") << "\n";
    cout << "Введите новый статус ремонта (0 - работает, 1 - в ремонте): ";
    cin >> pipe.repair;

    while (cin.fail()) {
        cout << "Ошибка! Введите 0 или 1: ";
        cin.clear();
        clearInputBuffer();
        cin >> pipe.repair;
    }

    cout << "Статус ремонта трубы '" << pipe.name << "' обновлен: "
        << (pipe.repair ? "в ремонте" : "работает") << "\n";
}

// увеличение работающих цехов
void startWorkshop(Compress& compstation) {
    if (!isStationCreated(compstation)) {
        cout << "Ошибка! Сначала создайте компрессорную станцию.\n";
        return;
    }

    if (compstation.count == -1) {
        cout << "Ошибка! Сначала установите общее количество цехов.\n";
        return;
    }

    if (compstation.count == 0) {
        cout << "Ошибка! Общее количество цехов равно нулю. Нельзя запустить цех.\n";
        return;
    }

    if (compstation.count_working < compstation.count) {
        compstation.count_working++;
        cout << "Цех запущен. Теперь " << compstation.count_working
            << " из " << compstation.count << " цехов работают.\n";
    }
    else {
        cout << "Все цехи уже работают!\n";
    }
}

// уменьшение работающих цехов
void stopWorkshop(Compress& compstation) {
    if (!isStationCreated(compstation)) {
        cout << "Ошибка! Сначала создайте компрессорную станцию.\n";
        return;
    }

    if (compstation.count_working == 0) {
        cout << "Ни один цех не работает! Нельзя остановить цех.\n";
        return;
    }

    if (compstation.count_working > 0) {
        compstation.count_working--;
        cout << "Цех остановлен. Теперь " << compstation.count_working
            << " из " << compstation.count << " цехов работают.\n";
    }
}

// добавление компрессорной станции
void addCompressorStation(Compress& compstation) {
    cout << "Введите название компрессорной станции: ";
    clearInputBuffer();
    getline(cin, compstation.name);

    cout << "Введите количество цехов: ";
    cin >> compstation.count;
    while (cin.fail() || compstation.count <= 0) {  // Изменено: <= 0 вместо < 0
        if (cin.fail()) {
            cout << "Ошибка! Введите корректное положительное число: ";
        } else if (compstation.count == 0) {
            cout << "Ошибка! На станции не может быть 0 цехов. Введите положительное число: ";
        } else {
            cout << "Ошибка! Введите корректное положительное число: ";
        }
        cin.clear();
        clearInputBuffer();
        cin >> compstation.count;
    }

    cout << "Введите количество работающих цехов: ";
    cin >> compstation.count_working;
    while (cin.fail() || compstation.count_working < 0 || compstation.count_working > compstation.count) {
        cout << "Ошибка! Введите корректное число (0-" << compstation.count << "): ";
        cin.clear();
        clearInputBuffer();
        cin >> compstation.count_working;
    }

    cout << "Введите классификацию: ";
    clearInputBuffer();
    getline(cin, compstation.classification);

    cout << "Компрессорная станция в ремонте? (0 - нет, 1 - да): ";
    cin >> compstation.working;
    while (cin.fail()) {
        cout << "Ошибка! Введите 0 или 1: ";
        cin.clear();
        clearInputBuffer();
        cin >> compstation.working;
    }

    cout << "Компрессорная станция '" << compstation.name << "' успешно создана!\n";
}

// показ всех объектов
void showAllObjects(const Pipe& pipe, const Compress& compstation) {
    if (!hasData(pipe, compstation)) {
        cout << "Данные отсутствуют. Пожалуйста, сначала добавьте трубы или компрессорные станции.\n";
    }
    else {
        printPipe(pipe);

        cout << "\nПараметры компрессорной станции:\n";
        cout << "Название: " << (compstation.name.empty() ? "неизвестно" : compstation.name) << "\n";
        cout << "Количество цехов: " << (compstation.count == -1 ? "неизвестно" : to_string(compstation.count)) << "\n";
        cout << "Количество работающих цехов: " << (compstation.count_working == -1 ? "неизвестно" : to_string(compstation.count_working)) << "\n";
        cout << "Классификация: " << (compstation.classification.empty() ? "неизвестно" : compstation.classification) << "\n";
        cout << "В ремонте: " << (compstation.working ? "да" : "нет") << "\n";
    }
}

// редактирование цехов компрессорной станции
void editCompressorStationWorkshops(Compress& compstation) {
    if (!isStationCreated(compstation)) {
        cout << "Ошибка! Сначала создайте компрессорную станцию.\n";
        return;
    }

    cout << "Текущие цехи: " << compstation.count_working << " работают из " << compstation.count << "\n";
    cout << "Выберите действие:\n 1. Запустить цех\n 2. Остановить цех\n";
    int action;
    cin >> action;
    if (action == 1) {
        startWorkshop(compstation);
    }
    else if (action == 2) {
        stopWorkshop(compstation);
    }
    else {
        cout << "Неверный выбор.\n";
    }
}

// загрузка данных из файла
void loadFromFile(Pipe& pipe, Compress& compstation) {
    ifstream file("mydata.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл 'mydata.txt'. Файл может не существовать.\n";
        return;
    }

    string line;
    string currentSection;

    // Сброс текущих данных
    pipe = Pipe();
    compstation = Compress();

    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line == "Параметры трубы:") {
            currentSection = "pipe";
        }
        else if (line == "Параметры компрессорной станции:") {
            currentSection = "station";
        }
        else if (line.find("Название: ") != string::npos) {
            string name = line.substr(10);
            if (name != "неизвестно") {
                if (currentSection == "pipe") pipe.name = name;
                else compstation.name = name;
            }
        }
        else if (line.find("Длина: ") != string::npos) {
            string lengthStr = line.substr(7);
            if (lengthStr != "неизвестно") {
                pipe.length = stof(lengthStr.substr(0, lengthStr.find(" км")));
            }
        }
        else if (line.find("Диаметр: ") != string::npos) {
            string diameterStr = line.substr(9);
            if (diameterStr != "неизвестно") {
                pipe.diameter = stoi(diameterStr.substr(0, diameterStr.find(" мм")));
            }
        }
        else if (line.find("В ремонте: ") != string::npos) {
            string status = line.substr(11);
            if (currentSection == "pipe") {
                pipe.repair = (status == "да");
            }
            else {
                compstation.working = (status == "да");
            }
        }
        else if (line.find("Количество цехов: ") != string::npos) {
            string countStr = line.substr(18);
            if (countStr != "неизвестно") {
                compstation.count = stoi(countStr);
            }
        }
        else if (line.find("Количество работающих цехов: ") != string::npos) {
            string countStr = line.substr(29);
            if (countStr != "неизвестно") {
                compstation.count_working = stoi(countStr);
            }
        }
        else if (line.find("Классификация: ") != string::npos) {
            string classification = line.substr(15);
            if (classification != "неизвестно") {
                compstation.classification = classification;
            }
        }
    }

    file.close();
    cout << "Данные успешно загружены из файла 'mydata.txt'\n";
}

// сохранение данных в файл
void saveToFile(const Pipe& pipe, const Compress& compstation) {
    ofstream file("mydata.txt");
    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл в текущей директории.\n";
        return;
    }

    if (file.is_open()) {
        if (!hasData(pipe, compstation)) {
            file << "Данные еще не были добавлены.\n";
            cout << "Файл создан, но данные еще не добавлены.\n";
        }
        else {
            file << "Параметры трубы:\n";
            file << "Название: " << (pipe.name.empty() ? "неизвестно" : pipe.name) << "\n";
            file << "Длина: " << (pipe.length == -1 ? "неизвестно" : to_string(pipe.length) + " км") << "\n";
            file << "Диаметр: " << (pipe.diameter == -1 ? "неизвестно" : to_string(pipe.diameter) + " мм") << "\n";
            file << "В ремонте: " << (pipe.repair ? "да" : "нет") << "\n";

            file << "\nПараметры компрессорной станции:\n";
            file << "Название: " << (compstation.name.empty() ? "неизвестно" : compstation.name) << "\n";
            file << "Количество цехов: " << (compstation.count == -1 ? "неизвестно" : to_string(compstation.count)) << "\n";
            file << "Количество работающих цехов: " << (compstation.count_working == -1 ? "неизвестно" : to_string(compstation.count_working)) << "\n";
            file << "Классификация: " << (compstation.classification.empty() ? "неизвестно" : compstation.classification) << "\n";
            file << "В ремонте: " << (compstation.working ? "да" : "нет") << "\n";

            cout << "Данные успешно сохранены в файл 'mydata.txt'\n";
        }
        file.close();
    }
    else {
        cout << "Ошибка: не удалось открыть файл для записи.\n";
    }
}

void Menu(Pipe& pipe, Compress& compstation) {
    while (true)
    {
        cout << "\nВыберите опцию:\n 1. Добавить трубу \n 2. Добавить компрессорную станцию\n 3. Показать все объекты\n 4. Редактировать статус ремонта трубы\n 5. Редактировать цехи компрессорной станции\n 6. Сохранить в файл\n 7. Загрузить из файла\n 0. Выход\n";
        int type;
        cin >> type;
        if (cin.fail()) {
            cout << "Ошибка!" << endl;
            cout << "Введите корректное число (0-7)" << endl;
            cin.clear();
            clearInputBuffer();
            continue;
        }

        if (type == 0) {
            cout << "Выход из программы." << endl;
            break;
        }

        switch (type)
        {
        case 1:
            readPipeFromConsole(pipe);
            break;
        case 2:
            addCompressorStation(compstation);
            break;
        case 3:
            showAllObjects(pipe, compstation);
            break;
        case 4:
            editPipeRepair(pipe);
            break;
        case 5:
            editCompressorStationWorkshops(compstation);
            break;
        case 6:
            saveToFile(pipe, compstation);
            break;
        case 7:
            loadFromFile(pipe, compstation);
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
            break;
        }
    }
}

int main()
{
    Pipe pipe;
    Compress compstation;
    Menu(pipe, compstation);

    return 0;
}