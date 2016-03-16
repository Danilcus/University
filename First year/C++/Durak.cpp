#include <iostream>
#include <ctime>
#include <string>
#include <deque>
#include <algorithm>
#include <iterator>
#include <random>

//chcp 65001 
using namespace std;

deque<string> first_player;
deque<string> second_player;

deque<string> deck(36);
deque<string> desk;

int ultimate;

int steps;

int our_random (int i) { return rand()%i;} //

//вывод рубашки
string get_suit(int suit){
    switch (suit) {
        case 0: return "♥"; break;
        case 1: return "♠"; break;
        case 2: return "♦"; break;
        case 3: return "♣"; break;
    }
    return "";
}

//вывод значения
string get_value(int value){
    switch (value) {
        case 0: return "6 ";break;
        case 1: return "7 ";break;
        case 2: return "8 ";break;
        case 3: return "9 ";break;
        case 4: return "10";break;
        case 5: return "J ";break;
        case 6: return "Q ";break;
        case 7: return "K ";break;
        case 8: return "A ";break;
    }
    return "";
}
//вывод одной карты
string print_card(string card){
    int suit = (int)card[0] - 48;
    int value = (int)card[1] - 48;
    return get_suit(suit) + get_value(value) + " ";
}
//вывод всей деки
string print_cards(deque<string> cards){
    string result = "";
    for (int i=0; i<cards.size(); i++) {
        result += print_card(cards[i]);
    }
    return result;
}
//инициализация колоды
void init_deck(){

    for (int i = 0; i <= 35; i++) {
        int suit = i % 4;
        int value = i % 9;
        deck[i] = to_string(suit)+to_string(value);
    }

    srand (unsigned(time(0)));
    random_shuffle(deck.begin(), deck.end(), our_random);
    ultimate = rand() % 4;

    cout << "Initial deck: " << print_cards(deck) << endl;
    cout << "Ultimate suit is: " << get_suit(ultimate) << endl;
}
//выдача карт
deque<string> give_cards_form_deck(int count) {
    deque<string> result;
    
    if (count < 0) { count = 0; }

    if (count > deck.size()) {
        count = deck.size();
    }

    while(count > 0) {
        result.push_back(deck.back());
        deck.pop_back();
        count--;
    }

    return result;
}

//сортировка
struct CardSorter
{
    bool operator() (const string &a, const string &b) {
        int suit_a = (int)a[0] - 48;
        int value_a = (int)a[1] - 48;
        int suit_b = (int)b[0] - 48;
        int value_b = (int)b[1] - 48;

        bool result1 = (suit_a == ultimate && suit_b != ultimate); //приоритет 1 a>b
        bool result2 = (suit_a == ultimate && suit_b == ultimate && value_a > value_b);  //приоритет 2 a>b
        bool result3 = (value_a > value_b && suit_b != ultimate); //приоритет 3 a>b

        return result1 || result2 || result3;
    }
};
//сортировка обоих
void sort_both(){
    CardSorter cs;  //создание структуры с оператором сравнения
    sort(first_player.begin(), first_player.end(), cs); //cs - функция сортировки
    sort(second_player.begin(), second_player.end(), cs);
}
//Ход первого пользователя?
bool is_first_player_turn(){
    CardSorter cs; //создание структуры с оператором сравнения
    return cs(first_player.front(), second_player.front()); //использование сравнения
}
//процесс защиты
int try_defence(string attack_card, deque<string> player_hand){
    player_hand.push_back(attack_card);
    CardSorter cs;
    sort(player_hand.begin(), player_hand.end(), cs);
    bool check = false;
    for (int i = player_hand.size()-1; i>=0; i--) { // поиск индекса нападающей карты в руке защиты справа налево
        bool same_suit = attack_card[0] == player_hand[i][0]; 
        bool ultimate_suit = ultimate == (int)player_hand[i][0]-48;
        if (check && (same_suit || ultimate_suit)){ // карта которая кроет найдена
            return i;
        }
        if (player_hand[i] == attack_card) { check = true; }  //поиск первоначальной карты // когда ее нашли, то меняем флаг
    }
    return -1; // нет карты которая кроет ->берем
}
//объединение дек
void merge_cards(deque<string> &to, deque<string> from) {
    to.insert(to.end(), from.begin(), from.end());
}

// ищем карту чтобы подкинуть защищаемуся, ищем подобное value
int find_some_card(deque<string> offensive){
    for (int i=0; i<desk.size(); i++) { // пробег по картам на столе (слева на право)
        int value = desk[i][1];         // value выбранной карты со стола
        for (int j=offensive.size()-1; j>=0; j--) { // пробег по картам на руке, с маленьких на большие и козыри
            if (value == offensive[j][1]) { // если находим такую же value, то возвращаем и подкидываем
                return j;
            }
        }
    }
    return -1; // если ничего не нашли, то возвращаем -1
}
//проверка победителя
bool winner_check(){
    if (deck.size() == 0 && first_player.size() == 0) {
        cout << "first_player wins" << endl;
        return true;
    }
    if (deck.size() == 0 && second_player.size() == 0) {
        cout << "second_player wins" << endl;
        return true;
    }
    return false;
}
//логика игры
void turn(int attack_card_index, deque<string> &offensive, deque<string> &defensive){  //как вынести повторы в отдельную функцию? пытались, не получилось.

    steps++;
    cout << "---- step "<< steps << " ----" << endl; 
    cout << "Offensive hand: " << print_cards(offensive) << endl;
    cout << "Defensive hand: " << print_cards(defensive) << endl;
    cout << "Desk: " << print_cards(desk) << endl;

    desk.push_back(offensive[attack_card_index]); // нападающий кидает карту
    cout << "A:" << print_card(offensive[attack_card_index]) << endl;
    offensive.erase(offensive.begin()+attack_card_index);

    int defence_card_index = try_defence(desk.back(), defensive);
    if (defence_card_index == -1) { // защищающийся взял карты со стола
        cout << "T:" << print_cards(desk) << endl;
        merge_cards(defensive, desk); // забрал карты
        desk.clear();
        if (winner_check()) {return;}
        merge_cards(offensive, give_cards_form_deck(6-offensive.size())); // атакующий забрал карты из колоды
        sort_both();                                // они сортирнули карты в руках
        turn(offensive.size()-1, offensive, defensive); // атакующий снова делает ход
    } else { // есть карта, которой можно покрыть
        desk.push_back(defensive[defence_card_index]); // карта, которой можно покрыть, кладется на стол
        cout << "D:" << print_card(defensive[defence_card_index]) << endl;
        defensive.erase(defensive.begin()+defence_card_index); //подобрал по примерам xD
        
        if (defensive.size() > 0) { //у защищающегося еще есть карты на руках
            int some_card_index = find_some_card(offensive); // нападающий ищет карту которую можно подкинуть
            if (some_card_index == -1){ //не нашли карту
                desk.clear();
                if (deck.size() == 0 && first_player.size() == 0 && second_player.size() == 0) {
                    cout << "no body wins" << endl;
                    return;
                }
                if (winner_check()) {return;}
                merge_cards(offensive, give_cards_form_deck(6-offensive.size())); // атакующий забрал карты из колоды
                merge_cards(defensive, give_cards_form_deck(6-defensive.size())); // защищающийся забрал карты из колоды
                sort_both();                                // они сортирнули карты в руках
                turn(defensive.size()-1, defensive, offensive); // защищающийся начинает атаковать
            } else { //нашли карту
                turn(some_card_index, offensive, defensive); // нападающий нашел что подкинуть и начал следующую атаку (рекурсия)
            }
        } else {
            desk.clear();
            if (deck.size() == 0 && first_player.size() == 0 && second_player.size() == 0) {		//ничья
                cout << "no body wins" << endl;
                return;
            }
            if (winner_check()) {return;}
            merge_cards(offensive, give_cards_form_deck(6-offensive.size())); // атакующий забрал карты из колоды
            merge_cards(defensive, give_cards_form_deck(6-defensive.size())); // защищающийся забрал карты из колоды
            sort_both();                                // они сортирнули карты в руках
            turn(defensive.size()-1, defensive, offensive); // защищающийся начинает атаковать
        }
    }

}
//начало игры
void start_game(){
	sort_both();

    cout << "Deck: " << print_cards(deck) << endl;
    cout << "First  player: " << print_cards(first_player) << endl;
    cout << "Second player: " << print_cards(second_player) << endl;

    if (is_first_player_turn()) {
        cout << "first player turn" << endl;
        turn(first_player.size()-1, first_player, second_player); //индекс последней карты
    }
    else {
        cout << "second player turn" << endl;
        turn(second_player.size()-1, second_player, first_player);
    }
}

int main()
{
    init_deck();
    steps = 0;

    first_player = give_cards_form_deck(6);
    second_player = give_cards_form_deck(6);

    start_game();

	return 0;
}
