#include"train.h"
#include<iostream>
#include<fstream>   //ofstream(), ifstream()
#include<cctype>    //isdigit()
#include<algorithm> //sort()
#include<iomanip>   //setw()

using namespace std;


//--------------------------------------------------------------------------------------Station.
Station::Station(vector<string> stationArguments)
:	id(stationArguments[0]), name(stationArguments[1]){}


int Station::getNumberFromId(){
    string number = id.substr(1);
    return stoi(number);
}


string Station::getCard() {
	string card;
	card += arrival+' ';
	card += name+' ';
	card += departure;
	return card;
}


string Station::getArrivalCard() {
	string card;
	card += arrival+' ';
	card += name;
	return card;
}


string Station::getDepartureCard() {
	string card;
	card += name+' ';
	card += departure;
	return card;
}


string Station::getAllData() {
	size_t idSize = id.size();
    string filler(5-idSize, ' ');
	if(idSize>=5)
        filler = " ";

	string content;
	content += arrival+" [";
	content += id+']';
	content += filler;
	content += name+' ';
	content += departure;
	return content;
}


string Station::getArrivalAllData() {
	size_t idSize = id.size();
    string filler(5-idSize, ' ');
	if(idSize>=5)
        filler = " ";

	string content;
	content += arrival+" [";
	content += id+']';
	content += filler;
	content += name;
	return content;
}


string Station::getDepartureAllData() {
	size_t idSize = id.size();
    string filler(5-idSize, ' ');
	if(idSize>=5)
        filler = " ";

	string content;
	content += '[';
	content += id+']';
	content += filler;
	content += name+' ';
	content += departure;
	return content;
}


//--------------------------------------------------------------------------------------Train.
Train::Train(vector<string> trainArguments){
	vector<string>::iterator it = trainArguments.begin();
	setId(*it);
	++it;
	setDays(*it);
	++it;
	setComments(*it);
	++it;
	for(; it != trainArguments.end(); ++it){
        Station station;
        station.setId(*it);
        ++it;
        station.setName(*it);
        ++it;
        station.setArrival(*it);
        ++it;
        station.setDeparture(*it);
        stops.push_back(station);
	}
}


int Train::getNumberFromId(){
    string number = id.substr(1);
    return stoi(number);
}


size_t Train::getStopsNumber(){
    return stops.size();
}


string Train::getCard() {
	string card;
	if(stops.size() == 2){
		card += stops[0].getDepartureCard();
		card += " - ";
		card += stops[1].getArrivalCard();
	}
	else if(stops.size() == 3){
		card += stops[0].getDepartureCard();
		card += " - ";
		card += stops[1].getCard();
		card += " - ";
		card += stops[2].getArrivalCard();
	}
	else if(stops.size()>3){
		size_t middle = stops.size()/2;
		card += stops[0].getDepartureCard();
		card += " - ";
		card += stops[middle].getCard();
		card += " - ";
		card += stops[stops.size()-1].getArrivalCard();
	}
	return card;
}

string Train::getAllData() {
	size_t idSize = id.size();
	string filler(5-idSize, ' ');

	string content;
	content += '[';
	content += id+']';
	content += filler;
	content += stops[0].getDepartureAllData()+" - ";
	size_t cnt;
	for(cnt = 1; cnt<stops.size()-1; ++cnt){
        content += stops[cnt].getAllData()+" - ";
	}
	content += stops[cnt].getArrivalAllData();
	content += "\n\nokres kursowania: "+days;
	content += "\nuwagi: "+comments;
	return content;
}


string Train::getAllRoute(){
	string content;
	content += stops[0].getDepartureCard()+" - ";
	size_t cnt;
	for(cnt = 1; cnt<stops.size()-1; ++cnt){
        content += stops[cnt].getCard()+" - ";
	}
	content += stops[cnt].getArrivalCard();
	content += "\n\nokres kursowania: "+days;
	content += "\nuwagi: "+comments;
	return content;
}


string Train::getRouteFromTo(vector<Station>::iterator startPos, vector<Station>::iterator endPos) {
	vector<Station>::iterator it = startPos;
	string content;
	while(it != endPos){
		content += it->getCard()+" - ";
		++it;
	}
	content += it->getArrivalCard();
	content += "\n\nokres kursowania: "+days;
	content += "\nuwagi: "+comments;
	return content;
}


string Train::getRouteFrom(vector<Station>::iterator startPos) {
	vector<Station>::iterator it = startPos;
	string content;
	while(it != stops.end()-1){
		content += it->getCard()+" - ";
		++it;
	}

	content += it->getArrivalCard();
	content += "\n\nokres kursowania: "+days;
	content += "\nuwagi: "+comments;
	return content;
}


string Train::getRouteTo(vector<Station>::iterator endPos) {
	vector<Station>::iterator it = stops.begin();
	string content;
	while(it != endPos){
		content += it->getCard()+" - ";
		++it;
	}
	content += it->getArrivalCard();
	content += "\n\nokres kursowania: "+days;
	content += "\nuwagi: "+comments;
	return content;
}


vector<Station>::iterator Train::getBeginningStationPosition(){
    return stops.begin();
}


vector<Station>::iterator Train::getFinalStationPosition(){
    if(stops.size()>0)
        return stops.end()-1;
    return stops.end();
}


vector<Station>::iterator Train::getStationIdPosition(string stationId){
	vector<Station>::iterator it = stops.begin();
	while(it != stops.end()){
		if(it->getId() == stationId){
			break;
		}
		++it;
	}
	return it;
}


vector<Station>::iterator Train::getStationPosition(string stationName){
	vector<Station>::iterator it = stops.begin();
	while(it != stops.end()){
		if(it->getName() == stationName){
			break;
		}
		++it;
	}
	return it;
}


pair<vector<Station>::iterator, vector<Station>::iterator> Train::getStationsRangePositions(string beginningStationName, string finalStationName) {
	vector<Station>::iterator start = stops.end();
	vector<Station>::iterator stop = stops.end();
	vector<Station>::iterator it = stops.begin();
	while(it != stops.end()){
		if(it->getName() == beginningStationName){
			start = it;
			break;
		}
		++it;
	}
	it = stops.begin();
	if(it != stops.end()){
		while(it != stops.end()){
			if(it->getName() == finalStationName){
				stop = it;
				break;
			}
			++it;
		}
	}
	return pair<vector<Station>::iterator, vector<Station>::iterator>(start, stop);
}


bool Train::isContainingStation(string stationName){
	vector<Station>::iterator it = stops.begin();
	while(it != stops.end()){
		if(it->getName() == stationName)
			return true;
		++it;
	}
	return false;
}


bool Train::isContainingStationId(string stationId){
	vector<Station>::iterator it = stops.begin();
	while(it != stops.end()){
		if(it->getId() == stationId)
			return true;
		++it;
	}
	return false;
}


bool Train::isContainingStationsRange(string beginningStationName, string finalStationName) {
	pair<vector<Station>::iterator, vector<Station>::iterator>	range = getStationsRangePositions(beginningStationName, finalStationName);
	if((range.first != stops.end()) && (range.second != stops.end()) && (range.first<range.second))
		return true;
	else
		return false;
}


bool Train::deletingStop(string stationId){
    if(stops.size()>2){
        vector<Station>::iterator it = stops.begin();
        for(; it != stops.end(); ++it){
            if(it->getId() == stationId){
                stops.erase(it);
                return true;
            }
        }
    }
    return false;
}


bool Train::insertStop(size_t pos, Station station){
    if(isContainingStation(station.getName()) == false){
        size_t stopsNumber = getStopsNumber();
        if(pos<=stopsNumber){
            vector<Station>::iterator it = stops.begin();
            it = it+pos;
            stops.insert(it, station);
            return true;
        }
    }
    return false;
}


//--------------------------------------------------------------------------------------StationsCatalog.
vector<Station>::iterator StationsCatalog::getStationIdPos(string idStation) {
	vector<Station>::iterator it = stations.begin();
	while(it != stations.end()){
		if(it->getId() == idStation)
			return it;
		++it;
	}
	return it;
}


vector<Station>::iterator StationsCatalog::getStationNamePos(string stationName) {
	vector<Station>::iterator it = stations.begin();
	while(it != stations.end()){
		if(it->getName() == stationName)
			return it;
		++it;
	}
	return it;
}


int StationsCatalog::getStationsNumber(){
	return stations.size();
}


string StationsCatalog::getNewStationId(){
	string id;
	string idNumber;
	int cnt;
	vector<Station>::iterator it = stations.begin();
	for(cnt = 1; it != stations.end(); ++cnt, ++it){
		id = it->getId();
		idNumber = id.substr(1);
		if(cnt != stoi(idNumber)){                          //Tworzy identyfikator z pierwszej wolnej liczby.
			break;
		}
	}
	return "s"+to_string(cnt);
}


bool StationsCatalog::isContainingStation(string stationName){
	vector<Station>::iterator it = getStationNamePos(stationName);
	if(it == stations.end())
        return false;
    return true;
}


bool StationsCatalog::isContainingStationId(string idStation){
    vector<Station>::iterator it = getStationIdPos(idStation);
    if(it == stations.end()){
        return false;
    }
    return true;
}


bool StationsCatalog::addStation(string nameStn){
    if(nameStn.size() == 0)
        return false;
    if(isContainingStation(nameStn))
        return false;
    string idStn = getNewStationId();
    Station newStation({idStn, nameStn});
    stations.push_back(newStation);
    sortStations();
    return true;
}


bool StationsCatalog::deletingStation(string idStation){
    vector<Station>::iterator it = getStationIdPos(idStation);
    if(it != stations.end()){
        stations.erase(it);
        return true;
    }
    return false;
}


bool StationsCatalog::fillFromFile(){
	ifstream plik("stations.txt");
	if(plik.fail())                                 //Jezeli strumien jest w stanie bledu - bo np. nie znalazl takiego pliku na dysku.
        return false;
	string line;
	vector<string> stationArguments;
    while(getline(plik, line)){	                    //Kiedy pobieranie wykroczy poza ostatnia linie pliku strumien znajdzie sie w stanie bledu.
        if(line != "*"){                            //Znak gwiazdki w moim pliku tekstowym "stations.txt" oddziela poszczegolne stacje od siebie.
            stationArguments.push_back(line);
        }
        else{
            stations.push_back(Station(stationArguments));  //Tworze tu tymczasowy obiekt bez nazwy typu Station i zaraz pcham go do wektora stations.
            stationArguments.clear();
        }
	}
	plik.close();
	return true;
}


bool StationsCatalog::saveToFile(){
	ofstream plik("stations.txt");
	if(plik.fail())
		return false;
	string catalogContent;
	for(auto elem : stations){
		catalogContent += elem.getId();
		catalogContent += "\n";
		catalogContent += elem.getName();
		catalogContent += "\n";
		catalogContent += "*\n";
	}
	plik<<catalogContent;
	plik.close();
	return true;
}


void StationsCatalog::sortStations(){
    sort(stations.begin(), stations.end(), [](Station a, Station b){return a.getNumberFromId()<b.getNumberFromId();});
}


void StationsCatalog::show() {
	vector<Station>::iterator it = stations.begin();
	while(it != stations.end()){
		cout<<it->getAllData()<<'\n';
		++it;
	}
}


void StationsCatalog::showNameSorted(){
    vector<Station> stationsNameSorted = stations;
    sort(stationsNameSorted.begin(), stationsNameSorted.end(), [](Station a, Station b){return a.getName()<b.getName();});
	vector<Station>::iterator it = stationsNameSorted.begin();
	while(it != stationsNameSorted.end()){
		cout<<it->getAllData()<<'\n';
		++it;
	}
}


//--------------------------------------------------------------------------------------TrainsCatalog.
vector<Train>::iterator TrainsCatalog::getTrainPos(size_t pos) {
	vector<Train>::iterator it = trains.begin();
	if(pos<trains.size())
		return it+pos;
	return trains.end();
}


vector<Train>::iterator TrainsCatalog::getTrainIdPos(string idTrain){
	vector<Train>::iterator it = trains.begin();
	while(it != trains.end()){
		if(it->getId() == idTrain){
			return it;;
		}
		++it;
	}
	return it;
}


vector<Train> TrainsCatalog::getTrainsWithStation(string stationName) {
	vector<Train> trainsFound;                 //"Worek" na znaleziska.
	vector<Train>::iterator it = trains.begin();
	while(it != trains.end()){
		if(it->isContainingStation(stationName)){
			trainsFound.push_back(*it);
		}
		++it;
	}
	return trainsFound;
}


vector<Train> TrainsCatalog::getTrainsWithStationsRange(string beginningStationName, string finalStationName) {
	vector<Train> trainsFound;                 //"Worek" na znaleziska.
	vector<Train>::iterator it = trains.begin();
	while(it != trains.end()){
		if(it->isContainingStationsRange(beginningStationName, finalStationName)){
			trainsFound.push_back(*it);
		}
		++it;
	}
	return trainsFound;
}


int TrainsCatalog::getTrainsNumber() {
	return trains.size();
}


string TrainsCatalog::getNewTrainId(){
	string id;
	string idNumber;
	int cnt;
	vector<Train>::iterator it = trains.begin();
	for(cnt = 1; it != trains.end(); ++cnt, ++it){
		id = it->getId();
		idNumber = id.substr(1);
		if(cnt != stoi(idNumber)){                      //Tworzy identyfikator z pierwszej wolnej liczby.
			break;
		}
	}
	return "p"+to_string(cnt);
}


bool TrainsCatalog::isContainingTrainId(string trainId){
    vector<Train>::iterator it = trains.begin();
    it = getTrainIdPos(trainId);
    if(it != trains.end()){
        return true;
    }
    return false;
}


bool TrainsCatalog::deletingTrain(string idTrain){
    vector<Train>::iterator it = getTrainIdPos(idTrain);
    if(it != trains.end()){
        trains.erase(it);
        return true;
    }
    return false;
}


void TrainsCatalog::addTrain(Train train){
    trains.push_back(train);
    sortTrains();
}


bool TrainsCatalog::fillFromFile(){
	ifstream plik("trains.txt");
	if(plik.fail())                         //Jezeli strumien jest w stanie bledu - bo np. nie znalazl takiego pliku na dysku.
        return false;
	string line;
	vector<string> trainArguments;
    while(getline(plik, line)){	            //Kiedy pobieranie wykroczy poza ostatnia linie pliku strumien znajdzie sie w stanie bledu.
        if(line != "*"){                    //Znak gwiazdki w moim pliku tekstowym "trains.txt" oddziela poszczegolne pociagi od siebie.
            trainArguments.push_back(line);
        }
        else{
            trains.push_back(Train(trainArguments));  //Tworze tu tymczasowy obiekt bez nazwy typu Train i zaraz pcham go do wektora trains.
            trainArguments.clear();
        }
	}
	plik.close();
	return true;
}


bool TrainsCatalog::saveToFile(){
	ofstream plik("trains.txt");
	if(plik.fail())
		return false;
	string catalogContent;
	for(auto elem : trains){
		catalogContent += elem.getId();
		catalogContent += "\n";
		catalogContent += elem.getDays();
		catalogContent += "\n";
		catalogContent += elem.getComments();
		catalogContent += "\n";

		for(auto elem : elem.getStops()){
			catalogContent += elem.getId();
			catalogContent += "\n";
			catalogContent += elem.getName();
			catalogContent += "\n";
			catalogContent += elem.getArrival();
			catalogContent += "\n";
			catalogContent += elem.getDeparture();
			catalogContent += "\n";
		}
		catalogContent += "*\n";
	}
	plik<<catalogContent;
	plik.close();
	return true;
}


void TrainsCatalog::sortTrains(){
    sort(trains.begin(), trains.end(), [](Train a, Train b){return a.getNumberFromId()<b.getNumberFromId();});
}


void TrainsCatalog::show() {
	vector<Train>::iterator it = trains.begin();
	string positionString;;
	int cnt{};
	while(it != trains.end()){
        positionString = to_string(++cnt)+").";
        cout<<left<<setw(5)<<positionString<<right<<it->getCard()<<'\n';
        ++it;
	}
}


void TrainsCatalog::showAllData(){
	vector<Train>::iterator it = trains.begin();
	string idString;
	while(it != trains.end()){
        idString = '['+it->getId()+']';
        cout<<left<<setw(7)<<idString<<right<<it->getCard()<<'\n';
        ++it;
	}
}


//--------------------------------------------------------------------------------------global functions.
void showTitle(){
    cout<<"TRAINS v. 1.1\n=============\n\n";
}


void showMenu(){
	cout<<"opcja nr 1:	Szukaj po\210\245czenia\n";
	cout<<"opcja nr 2:	Poka\276 rozk\210ad jazdy\n";
	cout<<"opcja nr 3:	Edycja (opcja serwisowa)\n";
	cout<<"opcja nr 0:	Koniec\n";
}


char getOption(string prompt){
	cout<<prompt;
	string input;
	getline(cin, input);
	if(input.size()==0)
		return '\0';
	else if(input.size()==1)
		return input[0];
    else
		return '*';
}


bool isNotNumber(string input){
    for(auto elem : input){
        if(isdigit(elem) == 0)
            return true;
    }
    return false;
}

