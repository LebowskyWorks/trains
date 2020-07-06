#ifndef TRAINS_H
#define TRAINS_H

#include<vector>
#include<string>	//string, size(), stoi(), to_string()
#include<utility>	//pair<>

using namespace std;


class Station{
public:
	Station() = default;                        //Konstruktor domyslny tworzony jest tu automatycznie (nie musze go juz definiowac).
	Station(vector<string> stationArguments);   //Konstruktor parametryczny.
	string getId() {return id;}
	string getName() {return name;}
	string getArrival()  {return arrival;}
	string getDeparture() {return departure;}
	string getCard();                           //Zwraca wizytowke stacji - jej skrocone dane.
    string getArrivalCard();                    //Pomija godzine przyjazdu do stacji (dla stacji poczatkowych).
    string getDepartureCard();                  //Pomija godzine odjazdu ze stacji (dla stacji koncowych).
	string getAllData();                        //Zwraca pelne dane stacji (tzn. wraz z jej identyfikatorem).
    string getArrivalAllData();                 //Dodatkowo zwraca identyfikator stacji (dla stacji poczatkowych).
    string getDepartureAllData();               //Dodatkowo zwraca identyfikator stacji (dla stacji koncowych).
	void setId(string idNumber) {id = idNumber;}
	void setName(string nameStation) {name = nameStation;}
	void setArrival(string arriv) {arrival = arriv;}
	void setDeparture(string depart) {departure = depart;}

private:
	string id;                                  //Identyfikator stacji.
	string name;                                //Nazwa stacji.
	string arrival;                             //Godzina przyjazdu do stacji.
	string departure;                           //Godzina odjazdu ze stacji.
};


class Train{
public:
	Train() = default;                          //Konstruktor domyslny tworzony jest tu automatycznie (nie musze go juz definiowac).
	Train(vector<string> trainArguments);       //Konstruktor parametryczny.
	string getId() {return id;}
	string getDays() {return days;}
	string getComments() {return comments;}
	vector<Station>& getStops() {return stops;}
	size_t getStopsNumber();                                            //Zwraca liczbe stacji pociagu (przystankow).
	string getCard();                                                   //Zwraca wizytowke pociagu - jego skrocony przebieg trasy.
	string getAllData();                                                //Zwraca pelna trase pociagu wraz z identyfikatorami stacji.
	string getAllRoute();                                               //Zwraca pelna trase pociagu bez identyfikatorow stacji.
	string getRouteFromTo(vector<Station>::iterator startPos, vector<Station>::iterator endPos);    //Zwraca wybrany odcinek trasy pociagu (od - do).
	string getRouteFrom(vector<Station>::iterator startPos);                                        //Zwraca wybrany odcinek trasy pociagu (od).
	string getRouteTo(vector<Station>::iterator endPos);                                            //Zwraca wybrany odcinek trasy pociagu (do).
	vector<Station>::iterator getBeginningStationPosition();            //Zwraca pozycje pierwszej stacji w wektorze stops.
	vector<Station>::iterator getFinalStationPosition();                //Zwraca pozycje ostatniej stacji w wektorze stops.
	vector<Station>::iterator getStationIdPosition(string stationId);   //Zwraca pozycje stacji o wybranym identyfikatorze w wektorze stops.
	vector<Station>::iterator getStationPosition(string stationName);   //Zwraca pozycje stacji o wybranej nazwie w wektorze stops.
	pair<vector<Station>::iterator, vector<Station>::iterator> getStationsRangePositions(string beginningStationName, string finalStationName); //Zwraca dwie krancowe pozycje wybranego odcinka trasy pociagu w wektorze stops.
	void setId(string idNumber) {id = idNumber;}
	void setDays(string runningDays) {days = runningDays;}
	void setComments(string cmnts) {comments = cmnts;}
	void setStops(vector<Station> stps) {stops = stps;}
	bool isContainingStation(string stationName);                       //Sprawdza czy pociag zawiera stacje o podanej nazwie.
	bool isContainingStationId(string stationId);                       //Sprawdza czy pociag zawiera stacje o podanym identyfikatorze.
	bool isContainingStationsRange(string beginningStationName, string finalStationName);   //Sprawdza czy pociag zawiera obie stacje o podanych nazwach.
	bool deletingStop(string stationId);                                //Usuwa stacje z pociagu i zwraca informacje czy sie to udalo.
	bool insertStop(size_t pos, Station station);                       //Dodaje stacje do pociagu na wskazanej pozycji i zwraca informacje czy sie to udalo.
private:
	string id;                                                          //Identyfikator pociagu.
	vector<Station> stops;                                              //Stacje ktore pociag zawiera (przystanki).
	string days;                                                        //Dni w ktorych pociag kursuje.
	string comments;                                                    //Dodatkowe informacje o pociagu.
};


class StationsCatalog{
public:
	vector<Station>::iterator getStationIdPos(string idStation);       //Zwraca pozycje stacji o wybranym identyfikatorze w wektorze stations.
	vector<Station>::iterator getStationNamePos(string stationName);   //Zwraca pozycje stacji o wybranej nazwie w wektorze stations.
	int getStationsNumber();                                           //Zwraca liczbe stacji w katalogu.
	string getNewStationId();                                          //Tworzy identyfikator dla nowej stacji.
	bool isContainingStation(string stationName);                      //Sprawdza czy katalog stacji zawiera stacje o danej nazwie.
	bool isContainingStationId(string idStation);                      //Sprawdza czy katalog stacji zawiera stacje o danym identyfikatorze.
	bool addStation(string stationName);                               //Dodaje nowa stacje do katalogu stacji i zwraca informacje czy sie to udalo.
	bool deletingStation(string idStation);                            //Usuwa z katalogu stacji stacje o podanym identyfikatorze i zwraca informacje czy sie to udalo.
	bool fillFromFile();                                               //Wczytuje z pliku dane do katalogu stacji i zwraca informacje czy sie to udalo.
	bool saveToFile();                                                 //Zapisuje do pliku dane z katalogu stacji i zwraca informacje czy sie to udalo.
	void show();                                                       //Wypisuje zawartosc katalogu stacji
private:
	vector<Station> stations;
};


class TrainsCatalog{
public:
	vector<Train>::iterator getTrainPos(size_t pos);            //Zwraca wskazana pozycje pociagu w wektorze trains.
	vector<Train>::iterator getTrainIdPos(string idTrain);      //Zwraca pozycje pociagu o danym identyfikatorze w wektorze trains.
	vector<Train> getTrainsWithStation(string stationName);     //Zwraca wektor pociagow zawierajacych stacje o danej nazwie.
	vector<Train> getTrainsWithStationsRange(string beginningStationName, string finalStationName); //Zwraca wektor pociagow zawierajacych obie stacje o podanych nazwach.
	int getTrainsNumber();                                      //Zwraca liczbe pociagow  w katalogu pociagow.
	string getNewTrainId();                                     //Tworzy identyfikator dla nowego pociagu.
	bool isContainingTrainId(string trainId);                   //Sprawdza czy katalog pociagow zawiera pociag o danym identyfikatorze.
	bool deletingTrain(string idTrain);                         //Usuwa z katalogu pociagow pociag o podanym identyfikatorze i zwraca informacje czy sie to udalo.
	void addTrain(Train tr);;                                   //Dodaje do katalogu pociagow podany pociag i zwraca informacje czy sie to udalo.
	bool fillFromFile();                                        //Wczytuje z pliku dane do katalogu pociagow i zwraca informacje czy sie to udalo.
	bool saveToFile();                                          //Zapisuje do pliku dane z katalogu pociagow i zwraca informacje czy sie to udalo.
	void show();                                                //Wypisuje zawartosc katalogu pociagow.
	void showAllData();                                         //Wypisuje zawartosc katalogu pociagow (pelne dane - wraz z identyfikatorami pociagow).
private:
	vector<Train> trains;
};


void showTitle();
void showMenu();
char getOption(string prompt);
bool isNotNumber(string input);

#endif


