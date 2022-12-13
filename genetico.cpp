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
int champion_fitness=0;
int tamPoblacion;
int campeon(vector<vector<char>> muestra) {
    int fitcampeon = fitness(muestra[0]);  
    for (int i = 0; i < muestra.size(); i++) {
        if (fitcampeon < fitness(muestra[i])) {
            fitcampeon = fitness(muestra[i]);        
        }
    }
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
    vector<pair<int, string>> newEmpates;
    empates = move(newEmpates);
    // leerArchivo(nombreArchivo, threshold, w, nivelDeDeterminismo);
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

            for (int i = 0; i < N; i++) {
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

            sort(alfap.begin(), alfap.end());

            if (alfap[0].first == alfap[3].first) {
                wordfinal.push_back(alfap[rand() % 4].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 4; i++) {
                    aux.second.push_back(alfap[i].second);
                }
                empates.push_back(aux);
            } else if (alfap[0].first == alfap[2].first) {
                wordfinal.push_back(alfap[rand() % 3].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 3; i++) {
                    aux.second.push_back(alfap[i].second);
                }
                empates.push_back(aux);
            } else if (alfap[0].first == alfap[1].first) {
                wordfinal.push_back(alfap[rand() % 2].second);
                pair<int, string> aux;
                aux.first = iteracion;
                for (int i = 0; i < 2; i++) {
                    aux.second.push_back(alfap[i].second);
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

    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++) {
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
    f_i = p; // puntaje
    tiempo += ((double)clock() - start);
    tiempo = tiempo / (double)CLOCKS_PER_SEC;
    return wordfinal;
}

vector<char> localSearch(vector<char> &wordfinal) {

    int fitnessWordfinal = 0;
    fitnessWordfinal = fitness(wordfinal);
    int largo = empates.size();
   
    for (int i = 0; i < largo; i++) {
        
        vector<char> vecino = wordfinal;          
        int columnaRandom= rand() % empates.size();
        vecino[empates[columnaRandom].first] = empates[columnaRandom].second[rand() % 4];
        columnaRandom= rand() % empates.size();
        vecino[empates[columnaRandom].first] = empates[columnaRandom].second[rand() % 4];
        int fitnessVecino = 0;
        fitnessVecino = fitness(vecino);
        if (fitnessVecino >= fitnessWordfinal) {
            wordfinal = vecino;
            if (fitnessVecino > fitnessWordfinal) {
                cout << fitnessWordfinal << "\t";
                champion_fitness= fitnessWordfinal;
                champion=wordfinal;
                    return wordfinal;
                }
                fitnessWordfinal = fitnessVecino;      
            }
            vector<char> nada;
            return nada;
        }
    vector<char> nada;
    return nada;
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
}

void evaluar(vector<vector<char>> pobla, int tamPobla) {  //????

    for (int i = 0; i < tamPobla; i++) {
        int mijo_fitness = fitness(pobla[i]);
        if (mijo_fitness > champion_fitness) {
            champion = pobla[i];  
            champion_fitness = mijo_fitness;
        }
    }
}

void spawnPoblacion(const string &nombreArchivo, const float &threshold,
                    const float &nivelDeDeterminismo) {
    vector<char> aux = pGreedy(nombreArchivo, threshold, 1.0);
    float tempo=0.0;
    cout<<"aaaa1: "<<lapobla.size()<<endl;
    while (lapobla.size()<tamPoblacion && ((tempo / (double)CLOCKS_PER_SEC) < 10)) {
        clock_t start= clock();
        vector<char> mijo = localSearch(aux);
       
        if (mijo.size()>1)  {
            lapobla.push_back(mijo);
        }
        tempo += ((double)clock() - start);
    }
    alpha=50;
    cout<<"aaaa: "<<lapobla.size()<<endl;
    int cont = lapobla.size();
    for ( int i = 0; i < tamPoblacion - cont; i++) {
        vector<char> mijo =
        pGreedy(nombreArchivo, threshold, 0.80);
        lapobla.push_back(mijo);
       
    }
cout<<"aaa11a: "<<lapobla.size()<<endl;
}

vector<vector<char>> mortalKombat(vector<vector<char>> winersactual) {
    vector<vector<char>> winersfuturo;
    if (winersactual.size() == 2) {
        return winersactual;
    }
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
    winersactual = winersfuturo;
    return mortalKombat(winersactual);
}

void crossover(vector<vector<char>> &aux, vector<vector<char>> &padres,
               vector<char> &padre1, vector<char> &padre2,
               const float nivelDeMutacion) {
   
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

 
}

vector<vector<char>> fight() {
    vector<vector<char>> padres;
    for (int i = 0; i < 2; i++) {
      

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
        vector<vector<char>> padres = mortalKombat(muestra);
        vector<char> padre1 = padres[0];
        vector<char> padre2 = padres[1];
        crossover(aux, padres, padre1, padre2, nivelDeMutacion);
    }
    vector<char> oldChampion = champion;
    evaluar(aux, totalMijos * 2);
    int totalDuplicados = tamPoblacion - totalMijos * 2;
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

}

// int main(int argc, const char *argv[]) {
//     map<string, string> param;
//     param["-i"] = "dataset/100-300-001.txt";  // instancia
//     param["--tiempo"] = "15";          // tiempo
//     param["--th"] = "0.75";           // threshold
//     param["--det"] = "0.95";          // nivelDeDeterminismo
//     param["--tam"] = "100";           // tamanoPoblacion
//     param["--mut"] = "0.05";          // nivelDeMutacion
//     param["--newG"] = "0.80";  // porcentaje de la siguiente poblacion compuesta
//                                // por la nueva generacion

//     for (int i = 1; i < argc - 1; i += 2) {
//         param[argv[i]] = argv[i + 1];
//     }
//     srand(0);
    
//     leerArchivo( param["-i"], stof(param["--th"]),w,stof(param["--det"]));
//     vector<char> wordfinal;
//     wordfinal = pGreedy( param["-i"], stof(param["--th"]), stof(param["--det"]) );
//     int porfavorDetente = stoi(param["--tiempo"]);

//     while ((tiempo / (double)CLOCKS_PER_SEC) < porfavorDetente) {
//         clock_t start= clock();
//         localSearch(wordfinal);

//         tiempo += ((double)clock() - start);
//     }
//     cout << -1*champion_fitness << endl;


//     return 0;
// }

int main(int argc, const char *argv[]) {
    map<string, string> param;
    param["-i"] = "dataset/100-600-002.txt";  // instancia
    param["--tiempo"] = "12";          // tiempo
    param["--th"] = "0.80";           // threshold
    param["--det"] = "1";          // nivelDeDeterminismo
    param["--tam"] = "100";           // tamanoPoblacion
    param["--mut"] = "0.05";          // nivelDeMutacion
    param["--newG"] = "0.80";  // porcentaje de la siguiente poblacion compuesta
                               // por la nueva generacion

    for (int i = 1; i < argc - 1; i += 2) {
        param[argv[i]] = argv[i + 1];
    }

    // signal(SIGCHLD, sig_handler);

    leerArchivo(param["-i"], stof(param["--th"]), w, stof(param["--det"]));

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
