#include <string>
#include <random>
#include <sstream>
#include <iostream>

#include"cluster.h"

using namespace std;

#define maxTasksPerCycle 5



Task randTask(int maxcores, ull maxcycles) {
    static random_device rd;
    static mt19937 gen(rd());

    uniform_int_distribution<int> core_dist(1, maxcores); 
    uniform_int_distribution<ull> cycle_dist(1, maxcycles);

    int cores = core_dist(gen);
    ull cycles = cycle_dist(gen);


    stringstream id_stream;
    id_stream << cores << "c" << cycles << "t";
    string id = id_stream.str();

    return Task{ id, cores, cycles };
}

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}



void main()
{
    setlocale(LC_ALL, "ru");
    int cores = 0;
    cout << "Введите количество ядер кластера:" << endl;
    cin >> cores;
    Cluster c(cores);

    int tcor = 0;
    cout << "Введите максимальное количество ядер на задачу:" << endl;
    cin >> tcor;

    int tcyc = 0;
    cout << "Введите максимальное количество тактов на задачу:" << endl;
    cin >> tcyc;

    double busysum = 0;
    double resourcesum = 0;

    ull cyc = 0;
    cout << "Введите количество циклов эксперимента:" << endl;
    cin >> cyc;

    for (ull i = 0; i < cyc;i++)
    {
        int addtasks = randomInt(0, maxTasksPerCycle);
        for (int j = 0; j < addtasks;j++)
        {
            Task t = randTask(tcor, tcyc);
            resourcesum += t.cycles * t.ncores;
            c.addTask(t);
        }
        c.process();
        busysum += c.getBusy();

    }

    cout << "Выполнено " << c.getCompleted() << " задач общей сложностью "<<resourcesum<<" ядро-тактов (в среднем "<<resourcesum/ c.getCompleted()<< " на задачу)" << endl;
    cout << "Средняя загруженность кластера " << (busysum / (cores * cyc)) * 100 << "% " << endl;

    system("pause");

}

