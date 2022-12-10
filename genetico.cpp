#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "fun.h"

using namespace std;

vector<char> champion;
int champion_fitness;
int tamPoblacion;
int campeon(vector<vector<char>> muestra) {
    // int fitind;
    int fitcampeon = fitness(muestra[0]);
    // int ind = 0;
    for (int i = 0; i < muestra.size(); i++) {
        if (fitcampeon < fitness(muestra[i])) {
            fitcampeon = fitness(muestra[i]);
            // ind = i;
        }
    }
    // fitind.push_back(fitcampeon);
    // fitind.push_back(ind);
    return fitcampeon;
}

bool checkrep(int rep, vector<int> indices) {
    for (int i = 0; i < indices.size(); i++) {
        if (rep == indices[i]) {
            return true;
        }
    }
    return false;
}

vector<char> pGreedy(const string &nombreArchivo, const float &threshold,
                     const float &nivelDeDeterminismo) {
    // cout << nombreArchivo << "\t" << threshold << "\t" << nivelDeDeterminismo
    //      << endl;
    vector<pair<int, string>> newEmpates;
    empates = move(newEmpates);
    // vector<string> w;
    leerArchivo(nombreArchivo, threshold, w, nivelDeDeterminismo);
    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    vector<char> wordfinal;

    clock_t start;
    tiempo = 0.0;  // resetear tiempo

    start = (double)clock();

    int iteracion = 0;

    do {
        if (rand() % 100 <= alpha) {
            vector<pair<int, char>> alfap;
            alfap.push_back(pair<int, char>(0, 'A'));
            alfap.push_back(pair<int, char>(0, 'G'));
            alfap.push_back(pair<int, char>(0, 'C'));
            alfap.push_back(pair<int, char>(0, 'T'));
            alfap[0].first = 0;
            alfap[1].first = 0;
            alfap[2].first = 0;
            alfap[3].first = 0;

            //    cout<<"b"<<endl;
            for (int i = 0; i < N; i++) {
                // cout << i << " " << N << endl;
                if (w[i][iteracion] == 'A') {
                    alfap[0].first++;
                }
                if (w[i][iteracion] == 'G') {
                    alfap[1].first++;
                }
                if (w[i][iteracion] == 'C') {
                    alfap[2].first++;
                }
                if (w[i][iteracion] == 'T') {
                    alfap[3].first++;
                }
            }

            // cout<<"a"<<endl;
            sort(alfap.begin(), alfap.end());

            // for(size_t i = 1; i < alfap.size(); i++){

            //     if(alfap[i-1].first == alfap[i].first){
            //         wordfinal.push_back(alfap[rand()%i].second);
            //     }
            // }

            // wordfinal.push_back(alfap[0].second);

            if (alfap[0].first == alfap[3].first) {
                // cout<<"empate3 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 4].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 4; i++) {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                    aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            } else if (alfap[0].first == alfap[2].first) {
                // cout<<"empate2 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 3].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 3; i++) {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                    aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            } else if (alfap[0].first == alfap[1].first) {
                // cout<<"empate1 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 2].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 2; i++) {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                    aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            } else {
                wordfinal.push_back(alfap[0].second);
            }

            iteracion++;
        } else {
            wordfinal.push_back(genes[rand() % 4]);
        }

    } while (iteracion < M);

    // muestra string generado
    // cout << "wordfinal: ";
    // for (int i = 0; i < M; i++) {
    //     cout << wordfinal[i];
    // }
    // cout << endl;

    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++) {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++) {
            if (wordfinal[j] != w[i][j]) {
                dif++;
            }
        }
        if (dif >= th) {
            p++;
        }
    }
    f_i = p;
    // puntaje
    tiempo += ((double)clock() - start);
    tiempo = tiempo / (double)CLOCKS_PER_SEC;

    // cout << p << '\t' << tiempo << endl;
    // cout << p << endl;
    return wordfinal;
}

bool localSearch2(vector<char> &wordfinal) {
    // cout<<"test1"<<endl;
    // calcula fitness final
    int fitnessWordfinal = 0;
    fitnessWordfinal = fitness(wordfinal);

    // cout<<"test2"<<endl;
    int largo = empates.size();
    // en cuantas columnas hubo empate
    for (int i = 0; i < largo; i++) {
        int columna = empates[i].first;
        // cout<<empates[i].first<<endl; |
        // cout<<"test3: largo"<<largo<<endl;
        // cout<<"test3.5: columna"<<columna<<endl;
        vector<char> vecino = wordfinal;
        // for (int i = 0; i < wordfinal.size(); i++) {
        //     cout<<vecino[i];
        // }
        // cout<<endl;
        for (int k = 0; k < empates[i].second.size(); k++) {
            // empates.first es la columna y second son los caracteres

            vecino[columna] = empates[i].second[k];
            vecino[empates[rand() % empates.size()].first] =
                empates[rand() % empates.size()].second[rand() % 4];
            // vecino[empates.size()-k]=empates[rand()%empates.size()].second[k];

            // vecino[empates[rand()%empates.size()].first]=empates[rand()%empates.size()].second[rand()%4];
            // vecino[rand()%M]=genes[rand()%4];

            // cout<<"test4"<<endl;
            // cout<<empates[i].second[k]<<endl;
            // vecino[columna]=empates[i].second[k];
            int fitnessVecino = 0;
            // cout<<"test5"<<endl;
            // calcular fitness de wordfinal y vecino y comparar
            fitnessVecino = fitness(vecino);
            if (fitnessVecino >= fitnessWordfinal) {
                wordfinal = vecino;
                if (fitnessVecino > fitnessWordfinal) {
                    cout << fitnessWordfinal << "\t";
                    return true;
                }
                fitnessWordfinal = fitnessVecino;
                // cout << "uh?" << endl;
            }
        }
    }

    return false;
}

void mutar(vector<char> &mijo, float nivelDeMutacion) {
    // nivel de mutacion varia entre 0 y 1, dsp de pasa a ser entre 0 y 100
    // entre mayor el nivel de mutacion tonces mas deberia poder mutar
    // imprime(mijo);
    nivelDeMutacion *= 100;

    for (int i = 0; i < M; i++) {
        if (rand() % 101 <= nivelDeMutacion) {
            char aux = mijo[i];
            while (aux == mijo[i]) {
                mijo[i] = genes[rand() % 4];
            }
        }
    }
    // cout << endl;
    // imprime(mijo);
}

void evaluar(vector<vector<char>> pobla, int tamPobla) {  //????
    for (int i = 0; i < tamPobla; i++) {
        int mijo_fitness = fitness(pobla[i]);
        if (mijo_fitness > champion_fitness) {
            champion = pobla[i];  // deberia ser move(pobla[i])??
            champion_fitness = mijo_fitness;
            // cout << champion_fitness << endl;
        }
    }
}

void spawnPoblacion(const string &nombreArchivo, const float &threshold,
                    const float &nivelDeDeterminismo) {
//    pGreedy(nombreArchivo, threshold, nivelDeDeterminismo);
//     tamPoblacion=empates.size();
//    vector<vector<char>> pacual;
//     cout<<"a"<<endl;
    for ( int i = 0; i < tamPoblacion; i++)
    {
        
        vector<char> mijo =
        pGreedy(nombreArchivo, threshold, nivelDeDeterminismo);
        lapobla.push_back(mijo);
    
        //  cout<<i<<endl;
        // vector<char>aux;
        // for (int j = 0; j < M; j++)
        // {  
        //     cout<<w[11][0]<<endl;
        //    aux.push_back(w[empates[i].first][j]);
        // } 
        // pacual.push_back(aux);
        // cout<<"emp: "<<empates.size()<<endl;
        // cout<<"pacualsize: "<<pacual.size()<<endl;
    }
//    cout<<"b"<<endl;
   
//     for (int i = 0; i < pacual.size(); i++) {
        
//         vector<char> mijo = pacual[i];
          
//         lapobla.push_back(mijo);
//     }
    
}

vector<vector<char>> mortalKombat(vector<vector<char>> winersactual) {
    vector<vector<char>> winersfuturo;
    // cout << "ma" << endl;
    if (winersactual.size() == 2) {
        return winersactual;
    }
    // cout << "ma1" << endl;
    for (int i = 0; i < winersactual.size(); i = i + 2) {
        if (i + 1 >= winersactual.size()) {
            winersfuturo.push_back(winersactual[i]);
            break;
        }
        if (fitness(winersactual[i]) > fitness(winersactual[i + 1])) {
            winersfuturo.push_back(winersactual[i]);
        } else {
            winersfuturo.push_back(winersactual[i + 1]);
        }
    }
    // cout << "mb" << endl;
    winersactual = winersfuturo;
    return mortalKombat(winersactual);
}
// vector<char> crossover(vector<char> &padre1, vector<char> &padre2);
void crossover(vector<vector<char>> &aux, vector<vector<char>> &padres,
               vector<char> &padre1, vector<char> &padre2,
               const float nivelDeMutacion) {
    // vector<vector<char>> aux;
    vector<char> hijo1;
    vector<char> hijo2;
    for (int i = 0; i < M; i++) {
        int random = rand() % 2;
        if (random == 1) {
            hijo1.push_back(padres[1][i]);
            hijo2.push_back(padres[0][i]);
        } else {
            hijo2.push_back(padres[1][i]);
            hijo1.push_back(padres[0][i]);
        }
    }
    mutar(hijo1, nivelDeMutacion);
    mutar(hijo2, nivelDeMutacion);

    aux.push_back(hijo1);
    aux.push_back(hijo2);

    // return aux;
}

vector<vector<char>> fight() {
    // cout << "tam: " << lapobla.size() << endl;
    vector<vector<char>> padres;
    for (int i = 0; i < 2; i++) {
        // cout << i << endl;
        // vector<char> candidato;
        // int fitness_candidato = 0;
        // for (int j = 0; j < 3; j++) {
        //     cout << j << endl;
        //     int aux = rand() % tamPoblacion;
        //     int fitness_aux = fitness(lapobla[aux]);
        //     if (fitness_aux > fitness_candidato) {
        //         candidato = lapobla[aux];
        //         fitness_candidato = fitness_aux;
        //     }
        //     padres.push_back(candidato);
        // }

        int azar = rand() % tamPoblacion;
        padres.push_back(lapobla[azar]);
    }
    return padres;
}

void degeneracion(vector<vector<char>> &lapobla, float nivelDeMutacion,
                  const float newG, const int &tamPoblacion) {
    vector<vector<char>> aux;

    int totalMijos = tamPoblacion * newG / 2;
    if (totalMijos % 2 == 1) {
        totalMijos--;
    }
    // cout << "total de hijos = " << totalMijos << endl;
    for (int i = 0; i < totalMijos; i++) {
        vector<vector<char>> muestra;
        for (int j = 0; j < totalMijos; j++) {
            vector<int> indices;
            int ind;
            do {
                ind = rand() % (tamPoblacion);
            } while (checkrep(ind, indices));

            indices.push_back(ind);
            muestra.push_back(lapobla[ind]);
        }

        // cout << "a" << endl;
        vector<vector<char>> padres = mortalKombat(muestra);
        // vector<vector<char>> padres = fight();
        vector<char> padre1 = padres[0];
        vector<char> padre2 = padres[1];

        crossover(aux, padres, padre1, padre2, nivelDeMutacion);
        // mutar(mijo, nivelDeMutacion);
        // aux.push_back(mijo);
    }
    // cout << "despues de todos los hijos" << endl;
    vector<char> oldChampion = champion;
    // cout << "uhh?? 1" << endl;

    evaluar(aux, totalMijos * 2);
    // cout << "uhh?? 2" << endl;

    // if (oldChampion !=
    //     champion) {  // la generacion nueva tiene un mejor champion
    // cout << "campeon: " << champion_fitness << endl;
    int totalDuplicados = tamPoblacion - totalMijos * 2;
    // cout << "poblacion restante: " << totalDuplicados << endl;
    for (int i = 0; i < totalDuplicados; i++) {
        vector<int> indices;
        int ind;
        do {
            ind = rand() % tamPoblacion;
        } while (checkrep(ind, indices));
        indices.push_back(ind);
        aux.push_back(lapobla[ind]);
    }
    lapobla = aux;
    //  for (int m = 0; m < lapobla.size(); m++)
    // {
    //    cout<<fitness(lapobla[m])<<"  ";

    // }
    // cout<<endl;
    // }
    // else {
    //     cout << "no hubo mjr champion" << endl;
    // }
    // cout << "F I N " << endl;
}

int main(int argc, const char *argv[]) {
    map<string, string> param;
    param["-i"] = "dataset/100-300-001.txt";  // instancia
    param["--tiempo"] = "209";          // tiempo
    param["--th"] = "0.75";           // threshold
    param["--det"] = "0.95";          // nivelDeDeterminismo
    param["--tam"] = "100";           // tamanoPoblacion
    param["--mut"] = "0.05";          // nivelDeMutacion
    param["--newG"] = "0.80";  // porcentaje de la siguiente poblacion compuesta
                               // por la nueva generacion

    for (int i = 1; i < argc - 1; i += 2) {
        param[argv[i]] = argv[i + 1];
    }

    // signal(SIGCHLD, sig_handler);

    srand(0);
    vector<char> wordfinal;
    // alarm(stoi(param["-tiempo"]));

    champion_fitness = 0;
    tamPoblacion = stoi(param["--tam"]);
    spawnPoblacion(param["-i"], stof(param["--th"]), stof(param["--det"]));

    evaluar(lapobla, tamPoblacion);
    // for (int i = 0; i < tamPoblacion; i++) {
    //     imprime(lapobla[i]);
    //     cout << "\n" << i << endl;
    // }
    int porfavorDetente = stoi(param["--tiempo"]);
    while ((tiempo / (double)CLOCKS_PER_SEC) < porfavorDetente) {
        clock_t start = clock();
        degeneracion(lapobla, stof(param["--mut"]), stof(param["--newG"]),
                     stoi(param["--tam"]));
        tiempo += ((double)clock() - start);
    }
    cout << champion_fitness * -1 << endl;
    return 0;
}
