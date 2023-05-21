#include <iostream>
#include <vector>
#include <string>
#include <regex>

using namespace std;

// Klasa Room (Sala)
class Room {
public:
    string name;
    int capacity;

    Room(string name, int capacity) {
        this->name = name;
        this->capacity = capacity;
    }
};

// Klasa Reservation (Rezerwacja)
class Reservation {
public:
    Room* room;
    string date;
    int hour;
    string user;

    Reservation(Room* room, string date, int hour, string user) {
        this->room = room;
        this->date = date;
        this->hour = hour;
        this->user = user;
    }
};

// Klasa Reservations (Rezerwacje)
class Reservations {
public:
    vector<Reservation*> reservationList;

    void addReservation(Room* room, string date, int hour, string user) {
        Reservation* r = new Reservation(room, date, hour, user);
        reservationList.push_back(r);
    }

    void displayReservations() {
        for (Reservation* r : reservationList) {
            cout << r->room->name << " | " << r->date << " | " << r->hour << " | " << r->user << endl;
        }
    }

    bool canReserve(Room* room, string date, int hour) {
        for (Reservation* r : reservationList) {
            if (r->room == room && r->date == date && r->hour == hour) {
                return false;
            }
        }
        return true;
    }
};

// Funkcja pomocnicza do pobierania danych od użytkownika
string getInput(string prompt) {
    string input;
    cout << prompt;
    cin >> input;
    return input;
}

// Funkcja pomocnicza do sprawdzania błędów w odpowiedziach użytkownika
template<typename T>
T getValidInput(string prompt, string errorMsg, function<bool(T)> validator) {
    T input;
    bool valid = false;
    while (!valid) {
        try {
            input = stoi(getInput(prompt));
            if (validator(input)) {
                valid = true;
            } else {
                cout << errorMsg << endl;
            }
        } catch (const exception&) {
            cout << errorMsg << endl;
        }
    }
    return input;
}

// Sprawdzenie poprawności numeru sali
bool isValidRoomNumber(int roomNumber) {
    // Sprawdzanie, czy numer sali jest większy od zera
    return roomNumber > 0;
}

// Funkcja main
int main() {
    // Inicjalizacja danych testowych
    Room* sala1 = new Room("Sala 1", 20);
    Room* sala2 = new Room("Sala 2", 30);
    Room* sala3 = new Room("Sala 3", 50);

    Reservations* reservations = new Reservations();

    // Dodanie przykładowych rezerwacji
    reservations->addReservation(sala1, "2023-05-16", 10, "Jan");
    reservations->addReservation(sala2, "2023-05-17", 14, "Anna");
    reservations->addReservation(sala3, "2023-05-18", 16, "Tomasz");

    // Wyświetlenie wszystkich rezerwacji
    cout << "Lista wszystkich rezerwacji:" << endl;
    reservations->displayReservations();
    cout << endl;

    // Dodawanie nowej rezerwacji przez użytkownika
    cout << "Dodawanie nowej rezerwacji:" << endl;
    int roomNumber = getValidInput<int>("Podaj numer sali (1, 2 lub 3): ",
                                        "Błędna wartość. Podaj numer sali 1, 2 lub 3.",
                                        [](int value) { return value >= 1 && value <= 3; });

    Room* newRoom;
    switch (roomNumber) {
        case 1:
            newRoom = sala1;
            break;
        case 2:
            newRoom = sala2;
            break;
        case 3:
            newRoom = sala3;
            break;
    }

    string date = getInput("Podaj datę rezerwacji (RRRR-MM-DD): ");
    int hour = getValidInput<int>("Podaj godzinę rezerwacji: ",
                                  "Błędna wartość. Podaj liczbę między 0 a 23.",
                                  [](int value) { return value >= 0 && value <= 23; });
    string user = getInput("Podaj imię: ");

    bool canAddReservation = reservations->canReserve(newRoom, date, hour);
    if (canAddReservation) {
        reservations->addReservation(newRoom, date, hour, user);
        cout << "Rezerwacja została dodana." << endl;
    } else {
        cout << "Nie można dodać rezerwacji. Sala jest już zarezerwowana w tym terminie." << endl;
    }
    cout << endl;

    // Wyświetlenie wszystkich rezerwacji po dodaniu nowej
    cout << "Lista wszystkich rezerwacji po dodaniu nowej:" << endl;
    reservations->displayReservations();

    return 0;
}
