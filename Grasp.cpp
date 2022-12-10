#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <iomanip>

#include <unistd.h>
#include <signal.h>

using namespace std;

int N, M, th, alpha;
vector<string> w;
vector<pair<int,string>> empates;
vector<char> genes = {'A', 'C', 'G', 'T'};
int f_i;
double tiempo = 0.0;

void alobruto();

void sig_handler(int sig) {
    if (sig == SIGALRM) {
        printf("llega senal de fin hijo\n");
        exit(0);
    }
}

ifstream leerArchivo(const string &nombreArchivo, const string &threshold, vector<string> &w, const string &nivelDeDeterminismo)
{

    string directorio = "dataset/";
    directorio += nombreArchivo;
    // cout << directorio << endl;
    ifstream archivo(directorio);

    if(!archivo){
        cout << "Error al abir el archivo" << endl;
        exit(EXIT_FAILURE);
    }

    string linea;

    while (getline(archivo, linea))
    {
        w.push_back(linea);
    }

    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }

    auto it = nombreArchivo.begin();
    int cont = 0; // contador de ' - '
    string s;
    while (*it != '.') // 5-4-001.txt
    {
        if (*it != '-')
        {
            s.push_back(*it);
        }
        else if (cont == 0)
        {
            N = stoi(s);
            string new_m;
            s = move(new_m);
            cont++;
        }
        else
        {
            M = stoi(s);
        }
        it++;
    }

    th = stof(threshold) * M;
    alpha = stof(nivelDeDeterminismo) * 100;

    return archivo;
}

vector<char> pGreedy(const string &nombreArchivo, const string &threshold, const string &nivelDeDeterminismo)
{
    vector<pair<int,string>> newEmpates;
    empates=move(newEmpates);
    // vector<string> w;
    leerArchivo(nombreArchivo, threshold, w, nivelDeDeterminismo);
    // for (auto it = w.begin(); it != w.end(); it++)
    // {
    //     cout << *it << endl;
    // }
    vector<char> wordfinal;

    clock_t start;
    tiempo= 0.0;    //resetear tiempo

    start = (double)clock();

    int iteracion = 0;

    do
    {
        if (rand() % 100 <= alpha)
        {

            vector<pair<int, char>> alfap;              //contador de caracteres por columna
            alfap.push_back(pair<int, char>(0, 'A'));
            alfap.push_back(pair<int, char>(0, 'G'));
            alfap.push_back(pair<int, char>(0, 'C'));
            alfap.push_back(pair<int, char>(0, 'T'));
            alfap[0].first = 0;
            alfap[1].first = 0;
            alfap[2].first = 0;
            alfap[3].first = 0;

            //    cout<<"b"<<endl;
            for (int i = 0; i < N; i++)
            {
                // cout << i << " " << N << endl;
                if (w[i][iteracion] == 'A')
                {
                    alfap[0].first++;
                }
                if (w[i][iteracion] == 'G')
                {
                    alfap[1].first++;
                }
                if (w[i][iteracion] == 'C')
                {
                    alfap[2].first++;
                }
                if (w[i][iteracion] == 'T')
                {
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

            if (alfap[0].first == alfap[3].first)
            {
                // cout<<"empate3 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 4].second);
                pair<int,string> aux;
                aux.first=iteracion;
                for (int i = 0; i <4; i++)
                {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                        aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            }
            else if (alfap[0].first == alfap[2].first)
            {
                // cout<<"empate2 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 3].second);
                pair<int,string> aux;
                aux.first=iteracion;
                for (int i = 0; i <3; i++)
                {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                         aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            }
            else if (alfap[0].first == alfap[1].first)
            {
                // cout<<"empate1 "<<iteracion<<endl;
                wordfinal.push_back(alfap[rand() % 2].second);
                pair<int,string> aux;
                aux.first=iteracion;
                for (int i = 0; i <2; i++)
                {
                    // if (wordfinal[iteracion]!=alfap[i].second)
                    // {
                         aux.second.push_back(alfap[i].second);
                    // }
                }
                empates.push_back(aux);
            }
            else
            {

                wordfinal.push_back(alfap[0].second);
            }

            iteracion++;
        }
        else
        {
            wordfinal.push_back(genes[rand() % 4]);
        }

    } while (iteracion < M);

    // muestra string generado

    // for (int i = 0; i < M; i++)
    // {
    //     cout << wordfinal[i];
    // }
    // cout << endl;

    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++)
    {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++)
        {

            if (wordfinal[j] != w[i][j])
            {
                dif++;
            }
        }
        if (dif >= th)
        {
            p++;
        }
    }
    f_i=p;
    // puntaje
    tiempo += ((double)clock() - start);
    tiempo = tiempo / (double)CLOCKS_PER_SEC;

    cout << p << '\t' << tiempo << endl;
    // cout << p << endl;

    // cout << "mori" << endl;
    // for(int i=0; i<empates.size(); i++){
    //     cout << "en la coulumna " << empates[i].first << " empatan estos caracteres: ";
    //     for(int j=0; j<empates[i].second.size(); j++){
    //         cout << empates[i].second[j] << ", ";
    //     }
    //     cout << endl;
    // }

    return wordfinal;
}

// void localSearch(vector<char>& wordfinal){
//     // cout<<"test1"<<endl;
//     //calcula fitness final
//     int fitnessWordfinal= 0;
//     for (int i = 0; i < N; i++){
//         int dif = 0;
//         for (int j = 0; j < M; j++)
//         {

//             if (wordfinal[j] != w[i][j])
//             {
//                 dif++;
//             }
//         }

//         if (dif >= th)
//         {
//             fitnessWordfinal++;
//         }
//     }
//     // cout<<"test2"<<endl;
//     int largo= empates.size();  //en cuantas columnas hubo empate
//     for(int i=0; i<largo; i++){
//         int columna= empates[i].first;
//         // cout<<empates[i].first<<endl;
//         // cout<<"test3: largo"<<largo<<endl;
//         // cout<<"test3.5: columna"<<columna<<endl;
//         vector<char> vecino=wordfinal;
//         //  for (int i = 0; i < wordfinal.size(); i++)
//         // {
//         //     cout<<vecino[i];
//         // }
//         // cout<<endl;

//         for(int k=0; k<empates[i].second.size();k++){   //empates.first es la columna y second son los caracteres
//             //wordfinal[columna]=
//             // cout<<"test4"<<endl;
//             // cout<<empates[i].second[k]<<endl;

//             vecino[columna]=empates[i].second[k];

//             int fitnessVecino=0;
//             // cout<<"test5"<<endl;
//             //calcular fitness de wordfinal y vecino y comparar
//             for (int i = 0; i < N; i++){
//                 int dif = 0;
//                 for (int j = 0; j < M; j++)
//                 {

//                     if (wordfinal[j] != w[i][j])
//                     {
//                         dif++;
//                     }
//                 }

//                 if (dif > th)
//                 {
//                     fitnessVecino++;
//                 }
//             }

//             if(fitnessVecino>=fitnessWordfinal){
//                 wordfinal= vecino;
//                 fitnessWordfinal= fitnessVecino;
//             }
//         }
//     }
//     // cout<<"A"<<endl;
//     // for (int i = 0; i < wordfinal.size(); i++)
//     // {
//     //     cout<<wordfinal[i];
//     // }
//     // cout<<endl;

//      cout<<fitnessWordfinal<<endl;
//     asd=fitnessWordfinal;
// }

int fitness(vector<char> word){
    int p = 0;
    int dif = 0;

    for (int i = 0; i < N; i++)
    {
        // cout<<w[i]<<" "<< th <<endl;
        dif = 0;
        for (int j = 0; j < M; j++)
        {

            if (word[j] != w[i][j])
            {
                dif++;
            }
        }
        if (dif >= th)
        {
            p++;
        }
    }
    return p;
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
        // for (int k = 0; k < empates[i].second.size(); k++) {
            // empates.first es la columna y second son los caracteres

            // vecino[columna] = empates[i].second[k];

            int no_empate_random = rand() % 100;

            if (fitnessWordfinal<90){
                int columnaRandom= rand() % empates.size();
                vecino[empates[columnaRandom].first] = empates[columnaRandom].second[rand() % 4];
                columnaRandom= rand() % empates.size();
                vecino[empates[columnaRandom].first] = empates[columnaRandom].second[rand() % 4];
                // vecino[empates[rand() % empates.size()].first] = empates[rand() % empates.size()].second[rand() % 4];
                // vecino[empates[rand() % empates.size()].first] = empates[rand() % empates.size()].second[rand() % 4];
            }else{
                // int numnoem;        //no empates*.
                // bool flag=false;
                // do
                // {
                //     numnoem=rand()%M;
                //     cout<<"n: "<<numnoem<<endl;
                //     for (int i = 0; i < empates.size(); i++)
                //     {
                //         if (numnoem==empates[i].first)
                //         {
                //             cout<<"ñ1"<<endl;
                //             flag=true;
                //             break;
                //         }   
                        
                //     }
                //      cout<<"a"<<endl;
                // } while (flag==true);
                // cout<<"------"<<endl;
                // int numnoem2;        //no empates*.
                // bool flag2=false;
                // do
                // {
                //     cout<<"ñ"<<endl;
                //     numnoem2=rand()%M;
                //     for (int i = 0; i < empates.size(); i++)
                //     {
                //         if (numnoem2==empates[i].first)
                //         {
                //             flag2=true;
                //             break;
                //              cout<<"c"<<endl;
                //         } 
                      
                //     }
                //      cout<<"b : "<<empates.size()<<endl;
                // } while (flag2==true);
                // cout<<"salio"<<endl;
                vecino[rand()%M]=genes[rand()%4];
                 vecino[rand()%M]=genes[rand()%4];
                 
                // int columnaRandom = rand() % empates.size();
                // vecino[empates[columnaRandom].first] = empates[columnaRandom].second[rand() % 4];
            }
              
            //     vecino[numnoem]=genes[rand()%4];
            //     vecino[empates[rand() % empates.size()].first] = empates[rand() % empates.size()].second[rand() % 4];
            //     vecino[empates[rand() % empates.size()].first] = empates[rand() % empates.size()].second[rand() % 4];
            //     // cout<<"sale"<<endl;
            // }
            
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
        // }
    }

    return false;
}

int main(int argc, const char *argv[])
{
    // ./grasp -i nombreArchivo -t tiempoMaxSec -th threashold -p nivelDeDeterminismo
    signal(SIGCHLD, sig_handler);


    srand(time(NULL));
    vector<char> wordfinal;
    if (argc == 9)  //se puede mejorar
    {
        // cout << "tiempo: " << argv[4] << endl;
        int porfavor_detente= stoi(argv[4]);
        alarm(porfavor_detente);
        //nombreArchivo, threshold, nivelDeDeterminismo
        // cout << "nombreArchivo: " << argv[2] << " threshold: " << argv[6] << " nivelDeDeterminismo: " << argv[8] << endl;
        wordfinal = pGreedy(argv[2], argv[6], argv[8]);
        

    }else{
        cout << "error en el formato" << endl;

        // int porfavor_detente= 90;
        // alarm(porfavor_detente);
        wordfinal = pGreedy("100-300-001.txt", "0.80", "1");
        // alobruto();
       
    }

        // for (int i = 0; i < empates.size(); i++)
        // {
        //     cout<<empates[i].first<<" "<<empates[i].second<<endl;
        // }

        //  for (int i = 0; i < wordfinal.size(); i++)
        // {
        //     cout<<wordfinal[i];
        // }
        // cout<<endl;

    while(true){
        // cout<<"empates size()"<<empates.size()<<endl;
        clock_t start= clock();
        if(localSearch2(wordfinal)){
            tiempo = tiempo ;
            cout << tiempo / (double)CLOCKS_PER_SEC << endl;
            tiempo= 0.0;
        }
        else{
            tiempo += ((double)clock() - start);
        }
    }

}


