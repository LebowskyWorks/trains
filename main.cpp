//TRAINS v. 1.0
//=============
#include"train.h"
#include<iostream>
#include<windows.h>	//system("CLS")

using namespace std;


int main(){
    StationsCatalog stationsCatalog;

    if(!stationsCatalog.fillFromFile()){
        cout<<"Nie znaleziono pliku - brak danych wej\210ciowych. Aplikacja zostanie zamkni\251ta.\nOK -> ";
        string input;
        getline(cin, input);
        return 1;
    }

    TrainsCatalog trainsCatalog;

    if(!trainsCatalog.fillFromFile()){
        cout<<"Nie znaleziono pliku - brak danych wej\210ciowych. Aplikacja zostanie zamkni\251ta.\nOK -> ";
        string input;
        getline(cin, input);
        return 1;
    }

	char exit;
	char option = '\0';
	bool backToMenu;
	bool backToOption;
	string password = "Bartek";
	string passwordEntered;

	while(option != '0'){
		backToMenu = false;
		exit = '\0';
		system("CLS");
		showTitle();
		showMenu();
		option = getOption("\n\n---------------\nPodaj opcj\251: -> ");
		switch(option){
			case '1':
				while(exit != 'y'){
					if(backToMenu)
						break;
					backToOption = false;
					system("CLS");
					cout<<"Wyszukiwanie po\210\245cze\344\n=====================\n\n";
					string startingStn;
					string finalStn;
					cout<<"Podaj stacj\251 pocz\245tkow\245: -> ";
					getline(cin, startingStn);
					cout<<"Podaj stacj\251 ko\344cow\245: -> ";
					getline(cin, finalStn);
					vector<Train> trainsFound;
					if((startingStn.size() == 0) && (finalStn.size() == 0)){
						backToMenu = true;
						continue;
					}
					else if((startingStn.size() != 0) && (finalStn.size() != 0)){
						trainsFound = trainsCatalog.getTrainsWithStationsRange(startingStn, finalStn);
					}

					else if(startingStn.size() != 0){
                        vector<Train> trainsWithStartingStnFound = trainsCatalog.getTrainsWithStation(startingStn);
                        vector<Train>::iterator it = trainsWithStartingStnFound.begin();
                        while(it != trainsWithStartingStnFound.end()){
                            if(it->getStationPosition(startingStn) != it->getFinalStationPosition()){
                                trainsFound.push_back(*it);
                            }
                            ++it;
                        }
					}
					else if(finalStn.size() != 0){
						vector<Train> trainsWithFinalStnFound = trainsCatalog.getTrainsWithStation(finalStn);
                        vector<Train>::iterator it = trainsWithFinalStnFound.begin();
                        while(it != trainsWithFinalStnFound.end()){
                            if(it->getStationPosition(finalStn) != it->getBeginningStationPosition()){
                                trainsFound.push_back(*it);
                            }
                            ++it;
                        }
					}

					int trainsFoundNumber = static_cast<int>(trainsFound.size());
					if(trainsFoundNumber == 0){
						cout<<"\nNie znaleziono.";
						exit = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
						continue;
					}
					int trainPosition;
					while(true){
						system("CLS");
                        cout<<"Wyszukiwanie po\210\245cze\344\n=====================\n\n";
						int cnt{};
						cout<<"Znalezione po\210\245czenia:\n\n";
						for(auto elem : trainsFound){
							cout<<++cnt<<"). "<<elem.getCard()<<'\n';
						}
						cout<<"\n\n------------------------------------------------\nSzczeg\242\210owe informacje: wybierz pozycj\251 poci\245gu.";
						cout<<"\nWyj\230cie: \'y\'\n-> ";
						string input;
						getline(cin, input);
						if(input.size() == 0){
							backToOption = true;
							break;
						}
						else if(input == "y"){
							backToOption = true;
							backToMenu = true;
							break;
						}
						else if(isNotNumber(input)){
							cout<<"\nNieprawid\210owa dana.\nOK -> ";
							getline(cin, input);
							continue;
						}
						trainPosition = stoi(input);
						if((trainPosition<1) || (trainPosition>trainsFoundNumber)){
							cout<<"\nNieprawid\210owa liczba.\nOK -> ";
							getline(cin, input);
							continue;
						}

                        system("CLS");
                        cout<<"Wyszukiwanie po\210\245cze\344\n=====================\n\n";
                        cout<<"Wybrane po\210\245czenie:\n\n";
                        pair<vector<Station>::iterator, vector<Station>::iterator> range =
                            trainsFound[trainPosition-1].getStationsRangePositions(startingStn, finalStn);
                        if((startingStn.size() != 0) && (finalStn.size() != 0)){
                            cout<<trainsFound[trainPosition-1].getRouteFromTo(range.first, range.second);
                        }
                        else if(startingStn.size() != 0){
                            cout<<trainsFound[trainPosition-1].getRouteFrom(range.first);
                        }
                        else if(finalStn.size() != 0){
                            cout<<trainsFound[trainPosition-1].getRouteTo(range.second);
                        }
                        exit = getOption("\n\n--------------------\nNowe po\210\245czenie: \'n\'\nWyj\230cie: \'y\'\n-> ");
                        if((exit == 'n') || (exit == 'y')){
                            break;
                        }
					}
					if(backToOption){
						continue;
					}
				}
				break;
			case '2':
				while(exit != 'y'){
					if(backToMenu)
						break;
					backToOption = false;
					int trainPosition;
					while(true){
						system("CLS");
						cout<<"Zestawienie po\210\245cze\344\n====================\n\n";
						trainsCatalog.show();
						cout<<"\n\n------------------------------------------------\nSzczeg\242\210owe informacje: wybierz pozycj\251 poci\245gu.\n-> ";
						string input;
						getline(cin, input);
						if(input.size() == 0){
							backToMenu = true;
							break;
						}
						else if(isNotNumber(input)){
							cout<<"\nNieprawid\210owa dana.\nOK -> ";
							getline(cin, input);
							continue;
						}
						trainPosition = stoi(input);
						if((trainPosition<1) || (trainPosition>trainsCatalog.getTrainsNumber())){
							cout<<"\nNieprawid\210owa liczba.\nOK -> ";
							getline(cin, input);
							continue;
						}
						else
							break;
					}
					if(backToMenu){
						continue;
					}
					system("CLS");
                    cout<<"Zestawienie po\210\245cze\344\n====================\n\n";
					cout<<"Wybrane po\210\245czenie:\n\n";
					cout<<trainsCatalog.getTrainPos(trainPosition-1)->getAllRoute();
					exit = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
				}
				break;
			case '3':
				while(exit != 'y'){
					if(backToMenu)
						break;
					bool backToEditionMenu = false;
					bool backToTrainEditionMenu = false;
					while(true){
						if(backToMenu)
							break;
						backToEditionMenu = false;
						system("CLS");
						cout<<"Edycja\n======\n\n";

						if(passwordEntered != password){
                            cout<<"Logowanie do panelu serwisowego: podaj has\210o: -> ";
                            getline(cin, passwordEntered);
                            if(passwordEntered != password){
                                backToMenu = true;
                                break;
                            }
						}

						system("CLS");
						cout<<"Edycja\n======\n\n";
						option = getOption("1. Edycja katalogu stacji\n2. Edycja katalogu poci\245g\242w\n\n-----------------\nWybierz opcj\251: -> ");
						switch(option){
							case '\0':
								backToMenu = true;
								break;
							case '1':
								while(true){
									if(backToEditionMenu)
										break;
									system("CLS");
                                    cout<<"Edycja\n======\n\n";
									option = getOption("1. Dodaj stacj\251\n2. Usun stacj\251\n3. Zmie\344 nazw\251 stacji\n\n-----------------\nWybierz opcj\251: -> ");
									switch(option){
										case '\0':
											backToEditionMenu = true;
											break;
										case '1':
											while(true){
												system("CLS");
                                                cout<<"Edycja\n======\n\n";
												cout<<"Operacja dodawania stacji.\n";
												cout<<"(Warunek: nazwa stacji nie mo\276e si\251 dublowa\206).\n\n";
												cout<<"\nPodaj nazw\251 nowej stacji: -> ";
												string stationName;
												getline(cin, stationName);

                                                if(stationName.size() == 0)
                                                    break;

												else if(stationsCatalog.addStation(stationName)){
                                                    cout<<"\nDodano now\245 stacj\251.";
												}
												else{
                                                    cout<<"\nOdmowa. Nazwa stacji jest nieprawid\210owa lub zdublowana.";
												}
												char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
												if(input == 'y')
													break;
											}
											break;
										case '2':
											while(true){
												system("CLS");
                                                cout<<"Edycja\n======\n\n";
												cout<<"Operacja usuwania stacji.\n";
												cout<<"(Warunek: stacja ta nie mo\276e by\206 aktualnie wykorzystywana przez poci\245gi).\n\n";
												stationsCatalog.show();
                                                cout<<"\n\nPodaj identyfikator stacji kt\242r\245 chcesz usun\245\206: \n-> ";
                                                string stationIdToDelete;
                                                getline(cin, stationIdToDelete);

                                                if(stationIdToDelete.size() == 0)
                                                    break;

                                                else if(stationsCatalog.isContainingStationId(stationIdToDelete)){
                                                    string stationNameToDelete = stationsCatalog.getStationIdPos(stationIdToDelete)->getName();
                                                    vector<Train> trainsWithStation = trainsCatalog.getTrainsWithStation(stationNameToDelete);
                                                    if(trainsWithStation.size() == 0){
                                                        stationsCatalog.deletingStation(stationIdToDelete);
                                                        cout<<"\nUsuni\251to stacj\251.";
                                                    }
                                                    else{
                                                        cout<<"\nOdmowa. Stacja jest obecnie wykorzystywana przez poci\245gi.";
                                                    }
                                                }
                                                else{
                                                    cout<<"\nOdmowa. Nie istnieje stacja o takim identyfikatorze.";
                                                }
												char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
												if(input == 'y')
													break;
											}
											break;
										case '3':
											while(true){
												system("CLS");
                                                cout<<"Edycja\n======\n\n";
												cout<<"Operacja zmiany nazwy stacji.\n\n";
												stationsCatalog.show();
                                                cout<<"\n\nPodaj identyfikator stacji kt\242r\245 chcesz zmieni\206: \n-> ";
                                                string stationIdToModify;
                                                getline(cin, stationIdToModify);

                                                if(stationIdToModify.size() == 0)
                                                    break;

                                                else if(stationsCatalog.isContainingStationId(stationIdToModify)){
                                                    string stationNameToModify = stationsCatalog.getStationIdPos(stationIdToModify)->getName();
                                                    cout<<"Obecna nazwa stacji: "<<stationNameToModify;
                                                    cout<<"\nNowa nazwa stacji: -> ";
                                                    string stationNewName;
                                                    getline(cin, stationNewName);
                                                    if(stationNewName.size() != 0){
                                                         if(stationNewName != stationNameToModify){
                                                            stationsCatalog.getStationIdPos(stationIdToModify)->setName(stationNewName);
                                                            vector<Train> trainsWithStation = trainsCatalog.getTrainsWithStation(stationNameToModify);
                                                            for(auto elem : trainsWithStation){
                                                                string id = elem.getId();
                                                                trainsCatalog.getTrainIdPos(id)->getStationPosition(stationNameToModify)->setName(stationNewName);
                                                            }
                                                            cout<<"\nZmieniono nazw\251 stacji.";
                                                         }
                                                         else
                                                            cout<<"\nNie zmieniono nazwy stacji.";
                                                    }
                                                    else
                                                        cout<<"\nOdmowa. Nieprawid\210owa nazwa.";
                                                }
                                                else
                                                    cout<<"\nOdmowa. Nieprawid\210owy identyfikator stacji.";

												char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
												if(input == 'y')
													break;
											}
											break;
										default:
                                            cout<<"\nNieprawid\210owa dana.\nOK -> ";
											string input;
											getline(cin, input);
									}
								}
								break;
							case '2':
								while(true){
									if(backToEditionMenu)
										break;
									backToTrainEditionMenu = false;
                                    bool exit = false;
									system("CLS");
                                    cout<<"Edycja\n======\n\n";
									option = getOption("1. Dodaj poci\245g\n2. Usu\344 poci\245g\n3. Edytuj poci\245g\n\n-----------------\nWybierz opcj\251: -> ");
									switch(option){
										case '\0':
											backToEditionMenu = true;
											break;
										case '1':
											while(exit == false){
                                                bool out = false;
                                                string stationId;
                                                string stationName;
                                                string hour;
                                                string days;
                                                string comments;
                                                vector<Station>::iterator it;
                                                vector<Station> stations;
                                                while(true){
                                                    system("CLS");
                                                    cout<<"Edycja\n======\n\n";
                                                    cout<<"Operacja dodawania poci\245gu.\n\n";
                                                    cout<<"Katalog stacji:\n\n";
                                                    stationsCatalog.show();
                                                    cout<<"\n\nTrasa: ";
                                                    for(auto elem : stations){
                                                        cout<<" - "<<elem.getName();
                                                    }
                                                    cout<<"\n\nDodaj przystanek (podaj identyfikator stacji). Aby zakonczy\206 wpisz znak 'x'.\n-> ";
                                                    getline(cin, stationId);
                                                    if(stationId.size() == 0){
                                                        out = true;
                                                        break;
                                                    }
                                                    else if(stationId == "x"){
                                                        break;
                                                    }
                                                    else if(stationsCatalog.isContainingStationId(stationId) == false)
                                                    {
                                                        cout<<"\nOdmowa. Brak takiego identyfikatora stacji.";
                                                        out = true;
                                                        break;
                                                    }
                                                    for(auto elem : stations){
                                                        if(elem.getId() == stationId){
                                                            cout<<"\nOdmowa. POwt\242rzenie stacji.";
                                                            out = true;
                                                            break;
                                                        }
                                                    }
                                                    if(out)
                                                        break;
                                                    it = stationsCatalog.getStationIdPos(stationId);
                                                    stations.push_back(*it);
                                                }
                                                if(out){
													char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
													if(input == 'y'){
														exit = true;
														continue;
													}
													else
														continue;
                                                }
                                                if(stations.size()<2){
                                                    cout<<"\nWymagane jest istnienie conajmniej dw\242ch przystank\242w.";
													char input = getOption("\n\n------------\nWyj230cie: \'y\'\n-> ");
													if(input == 'y'){
														exit = true;
														continue;
													}
													else
														continue;
                                                }

                                                system("CLS");
                                                cout<<"Edycja\n======\n\n";
                                                cout<<"Operacja dodawania poci\245gu.\n\n";
                                                cout<<"Trasa: ";
                                                for(auto elem : stations){
                                                    cout<<" - "<<elem.getName();
                                                }
                                                it = stations.begin();
                                                it->setArrival("#");
                                                cout<<endl<<endl<<it->getName()<<", odjazd: -> ";
                                                getline(cin, hour);
                                                it->setDeparture(hour);
                                                ++it;
                                                while(it != stations.end()-1){
                                                    system("CLS");
                                                    cout<<"Edycja\n======\n\n";
                                                    cout<<"Operacja dodawania poci\245gu.\n\n";
                                                    cout<<"Trasa: ";
                                                    for(auto elem : stations){
                                                        cout<<" - "<<elem.getName();
                                                    }
                                                    cout<<endl<<endl<<it->getName()<<", przyjazd: -> ";
                                                    getline(cin, hour);
                                                    it->setArrival(hour);
                                                    cout<<it->getName()<<", odjazd: -> ";
                                                    getline(cin, hour);
                                                    it->setDeparture(hour);
                                                    ++it;
                                                }
                                                cout<<it->getName()<<", przyjazd: -> ";
                                                getline(cin, hour);
                                                it->setArrival(hour);
                                                it->setDeparture("#");
                                                cout<<"\nKursuje: -> ";
                                                getline(cin, days);
                                                cout<<"Uwagi: -> ";
                                                getline(cin, comments);
                                                string id = trainsCatalog.getNewTrainId();

                                                Train newTrain;
                                                newTrain.setId(id);
                                                newTrain.setStops(stations);
                                                newTrain.setDays(days);
                                                newTrain.setComments(comments);
                                                trainsCatalog.addTrain(newTrain);
                                                cout<<"\n\nDodano nowy poci\245g.";
												char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
												if(input == 'y')
													break;
											}
											break;
										case '2':
											while(true){
												system("CLS");
                                                cout<<"Edycja\n======\n\n";
												cout<<"Operacja usuwania poci\245gu.\n\n";
												trainsCatalog.showAllData();
                                                cout<<"\n\nPodaj identyfikator poci\245gu kt\242ry chcesz usun\245\206: \n-> ";
                                                string trainIdToDelete;
                                                getline(cin, trainIdToDelete);
                                                if(trainIdToDelete.size() == 0)
                                                    break;
												else if(trainsCatalog.deletingTrain(trainIdToDelete)){
                                                    cout<<"\nUsuni\251to poci\245g.";
												}
												else{
                                                    cout<<"\nOdmowa. Nie istnieje poci\245g o takim identyfikatorze.";
												}
												char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
												if(input == 'y')
													break;
											}
											break;
										case '3':
											while(true){
												if(backToTrainEditionMenu)
													break;
												system("CLS");
                                                cout<<"Edycja\n======\n\n";
												option = getOption("1. Dodaj przystanek\n2. Usu\344 przystanek\n3. Zmie\344 godzin\251 odjazdu/przyjazdu\n\n-----------------\nWybierz opcje: -> ");
												switch(option){
													case '\0':
														backToTrainEditionMenu = true;
														break;
													case '1':
														while(true){
															system("CLS");
                                                            cout<<"Edycja\n======\n\n";
															cout<<"Operacja dodawania przystanku."<<endl;
                                                            cout<<"(Warunek: stacja musi ju\276 istnie\206 w katalogu stacji).\n\n";

                                                            trainsCatalog.showAllData();
                                                            cout<<"\n\nPodaj identyfikator poci\245gu: -> ";
                                                            string trainId;
                                                            getline(cin, trainId);
                                                            if(trainId.size() == 0){
                                                                break;
                                                            }
                                                            else if(trainsCatalog.isContainingTrainId(trainId)){
                                                                vector<Train>::iterator itp = trainsCatalog.getTrainIdPos(trainId);
                                                                while(true){
                                                                    system("CLS");
                                                                    cout<<"Edycja\n======\n\n";
                                                                    cout<<"Operacja dodawania przystanku."<<endl;
                                                                    cout<<"(Warunek: stacja musi ju\276 istnie\206 w katalogu stacji).\n\n";
                                                                    cout<<"Katalog stacji:\n\n";
                                                                    stationsCatalog.show();
                                                                    cout<<endl<<endl<<itp->getAllData();
                                                                    cout<<"\n\nPodaj identyfikator stacji: -> ";
                                                                    string stationId;
                                                                    getline(cin, stationId);
                                                                    if(stationId.size() == 0){
                                                                        break;
                                                                    }
                                                                    if(stationsCatalog.isContainingStationId(stationId)){
                                                                        int stationsNumber = itp->getStopsNumber();
                                                                        string range = to_string(stationsNumber+1);
                                                                        cout<<"Podaj pozycj\251 nowej stacji (1 - "<<range<<"): -> ";
                                                                        string position;
                                                                        getline(cin, position);
                                                                        int insertPosition = stoi(position)-1;
                                                                        Station insertStation = *stationsCatalog.getStationIdPos(stationId);
                                                                        if(insertPosition == 0){
                                                                            cout<<"Podaj godzin\251 odjazdu ze stacji: -> ";
                                                                            string departure;
                                                                            getline(cin, departure);
                                                                            insertStation.setDeparture(departure);
                                                                            cout<<"Podaj godzin\251 przyjazdu do nast\251pnej stacji: -> ";
                                                                            string arrival;
                                                                            getline(cin, arrival);
                                                                            vector<Station>::iterator it = itp->getBeginningStationPosition();
                                                                            it->setArrival(arrival);
                                                                        }
                                                                        else if(insertPosition == stationsNumber){
                                                                            cout<<"Podaj godzin\251 przyjazdu do stacji: -> ";
                                                                            string arrival;
                                                                            getline(cin, arrival);
                                                                            insertStation.setArrival(arrival);
                                                                            insertStation.setDeparture("#");
                                                                            cout<<"Podaj godzin\251 odjazdu z poprzedniej stacji: -> ";
                                                                            string departure;
                                                                            getline(cin, departure);
                                                                            vector<Station>::iterator it = itp->getFinalStationPosition();
                                                                            it->setDeparture(departure);
                                                                        }
                                                                        else{
                                                                            cout<<"Podaj godzin\251 przyjazdu do stacji: -> ";
                                                                            string arrival;
                                                                            getline(cin, arrival);
                                                                            insertStation.setArrival(arrival);
                                                                            cout<<"Podaj godzin\251 odjazdu ze stacji: -> ";
                                                                            string departure;
                                                                            getline(cin, departure);
                                                                            insertStation.setDeparture(departure);
                                                                        }

                                                                        if(itp->insertStop(insertPosition, insertStation)){
                                                                            cout<<"\n\nWstawiono now\245 stacj\251.";
                                                                        }
                                                                        else{
                                                                            cout<<"\n\nNie wstawiono nowej stacji.";
                                                                        }
                                                                    }
                                                                    else{
                                                                        cout<<"\n\nNieprawid\210owy identyfikator stacji.";
                                                                    }

                                                                    option = getOption("\n\nnast\251pna stacja: \'n\' -> ");
                                                                    if(option != 'n')
                                                                        break;
                                                                }
                                                            }
                                                            else{
                                                                cout<<"\n\nNieprawid\210owy identyfikator poci\245gu.";
                                                            }

															char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
															if(input == 'y')
																break;
														}
														break;
													case '2':
														while(true){
															system("CLS");
                                                            cout<<"Edycja\n======\n\n";
															cout<<"Operacja usuwania przystanku."<<endl;
                                                            cout<<"(Warunek: musz\245 pozosta\206 przynajmniej dwie stacje).\n\n";
                                                            trainsCatalog.showAllData();
                                                            cout<<"\n\nPodaj identyfikator poci\245gu: -> ";
                                                            string trainId;
                                                            getline(cin, trainId);
                                                            if(trainId.size() == 0){
                                                                break;
                                                            }
                                                            if(trainsCatalog.isContainingTrainId(trainId)){
                                                                vector<Train>::iterator it = trainsCatalog.getTrainIdPos(trainId);
                                                                system("CLS");
                                                                cout<<"Edycja\n======\n\n";
                                                                cout<<"Operacja usuwania przystanku.\n";
                                                                cout<<"(Warunek: musz\245 pozosta\206 przynajmniej dwie stacje).\n\n";
                                                                cout<<endl<<endl<<it->getAllData();
                                                                cout<<"\n\nPodaj identyfikator stacji do usuni\251cia: -> ";
                                                                string stationId;
                                                                getline(cin, stationId);
                                                                if(it->deletingStop(stationId)){
                                                                    cout<<"\n\nUsuni\251to stacj\251.";
                                                                }
                                                                else{
                                                                    cout<<"\n\nNie usuni\251to stacji - nieprawid\210owy identyfikator lub poci\245g posiada ju\276 minimum przystank\242w.";
                                                                }
                                                            }
                                                            else{
                                                                cout<<"\n\nNieprawid\210owy identyfikator poci\245gu.";
                                                            }

															char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
															if(input == 'y')
																break;
														}
														break;
													case '3':
														while(true){
															system("CLS");
                                                            cout<<"Edycja\n======\n\n";
															cout<<"Operacja zmiany godziny przyjazdu/odjazdu.\n\n";

                                                            trainsCatalog.showAllData();
                                                            cout<<"\nPodaj identyfikator poci\245gu: -> ";
                                                            string trainId;
                                                            getline(cin, trainId);
                                                            if(trainId.size() == 0){
                                                                break;
                                                            }
                                                            else if(trainsCatalog.isContainingTrainId(trainId)){
                                                                vector<Train>::iterator itp = trainsCatalog.getTrainIdPos(trainId);
                                                                while(true){
                                                                    system("CLS");
                                                                    cout<<"Edycja\n======\n\n";
                                                                    cout<<"Operacja zmiany godziny przyjazdu/odjazdu.\n\n";
                                                                    cout<<itp->getAllData();
                                                                    cout<<"\n\nPodaj identyfikator stacji: -> ";
                                                                    string stationId;
                                                                    getline(cin, stationId);
                                                                    if(stationId.size() == 0){
                                                                        break;
                                                                    }
                                                                    if(itp->isContainingStationId(stationId)){
                                                                        string arrival;
                                                                        string departure;
                                                                        vector<Station>::iterator its = itp->getStationIdPosition(stationId);
                                                                        system("CLS");
                                                                        cout<<"Edycja\n======\n\n";
                                                                        cout<<"Operacja zmiany godziny przyjazdu/odjazdu.\n\n";
                                                                        cout<<itp->getAllData();
                                                                        cout<<"\n\nstacja: "<<its->getName();
                                                                        if(its != itp->getBeginningStationPosition()){
                                                                            cout<<"\ngodzina przyjazdu - obecna: "<<its->getArrival();
                                                                            cout<<"\ngodzina przyjazdu - nowa: -> ";
                                                                            getline(cin, arrival);
                                                                            if(arrival.size() != 0){
                                                                                its->setArrival(arrival);
                                                                            }
                                                                        }
                                                                        if(its != itp->getFinalStationPosition()){
                                                                            cout<<"\ngodzina odjazdu - obecna: "<<its->getDeparture();
                                                                            cout<<"\ngodzina odjazdu - nowa: -> ";
                                                                            getline(cin, departure);
                                                                            if(departure.size() != 0){
                                                                                its->setDeparture(departure);
                                                                            }
                                                                        }
                                                                    }
                                                                    else{
                                                                        cout<<"\nNieprawid\210owy identyfikator stacji.";
                                                                    }
                                                                    option = getOption("\n\nnast\251pna stacja: \'n\' -> ");
                                                                    if(option != 'n')
                                                                        break;
                                                                }
                                                            }
                                                            else{
                                                                cout<<"\nNieprawid\210owy identyfikator poci\245gu.";
                                                            }

															char input = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
															if(input == 'y')
																break;
														}
														break;
													default:
                                                        cout<<"\nNieprawid\210owa dana.\nOK -> ";
														string input;
														getline(cin, input);
												}
											}
											break;
										default:
                                            cout<<"\nNieprawid\210owa dana.\nOK -> ";
											string input;
											getline(cin, input);
									}
								}
								break;
							default:
                                cout<<"\nNieprawid\210owa dana.\nOK -> ";
								string input;
								getline(cin, input);
						}
					}
					if(backToMenu){
						continue;
					}

					exit = getOption("\n\n------------\nWyj\230cie: \'y\'\n-> ");
				}
				break;
			case '0':	//koniec programu.
				break;
			default:
				cout<<"\nNieprawid\210owa warto\230\206.\nOK -> ";
				string input;
                getline(cin, input);
		}
	}

	if(!stationsCatalog.saveToFile()){
        cout<<"\n\nNie zapisano danych do pliku. Aplikacja zostanie zamkni\251ta.\nOK -> ";
        string input;
        getline(cin, input);
        return 1;
	}
	if(!trainsCatalog.saveToFile()){
        cout<<"\n\nNie zapisano danych do pliku. Aplikacja zostanie zamkni\251ta.\nOK -> ";
        string input;
        getline(cin, input);
        return 1;
	}


    cout<<endl<<endl;
	return 0;
}
