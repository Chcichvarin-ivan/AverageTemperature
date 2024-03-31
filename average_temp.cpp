/*
 * @Author: Ivan Chichvarin ichichvarin@humanplus.ru
 * @Date: 2024-03-31 20:54:55
 * @LastEditors: Ivan Chichvarin ichichvarin@humanplus.ru
 * @LastEditTime: 2024-03-31 22:33:45
 * @FilePath: /AverageTemperature/average_temp.cpp
 * 
 */
#include "log_duration.h"

#include <assert.h>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <vector>

using namespace std;

vector<float> ComputeAvgTemp(const vector<vector<float>>& measures) {
    vector<float> ret_val;
    if(!measures.empty()){
        ret_val.resize(measures.at(0).size());
        vector<float> denominator(measures.at(0).size());        
        for(auto measure_vector: measures){;
            for (size_t iterator = 0; iterator < measure_vector.size(); iterator++) {
                ret_val.at(iterator) += (measure_vector[iterator] > 0 ? measure_vector[iterator] : 0);
                denominator.at(iterator) += (measure_vector[iterator] > 0 ? (float)1 : (float)0);
            }

        }
        
        for (size_t iterator = 0; iterator < ret_val.size(); iterator++){
            if(denominator.at(iterator)!=0)
            {
                ret_val.at(iterator) = ret_val.at(iterator)/denominator.at(iterator);
            }    
        }
        
    }
    

    return ret_val;
}

vector<float> GetRandomVector(int size) {
    static mt19937 engine;
    uniform_real_distribution<float> d(-100, 100);

    vector<float> res((long unsigned int)size);
    for (int i = 0; i < size; ++i) {
        res[(long unsigned int)i] = d(engine);
    }

    return res;
}

void Test() {
    // 4 дня по 3 измерения
    vector<vector<float>> v = {
        {0, -1, -1},
        {1, -2, -2},
        {2, 3, -3},
        {3, 4, -4}
    };

    // среднее для 0-го измерения (1+2+3) / 3 = 2 (не учитывам 0)
    // среднее для 1-го измерения (3+4) / 2 = 3.5 (не учитывам -1, -2)
    // среднее для 2-го не определено (все температуры отрицательны), поэтому должен быть 0

    assert(ComputeAvgTemp(v) == vector<float>({2, 3.5f, 0}));
} 


int main() {
    Test();
    vector<vector<float>> data;
    data.reserve(5000);

    for (int i = 0; i < 5000; ++i) {
        data.push_back(GetRandomVector(5000));
    }

    vector<float> avg;
    {
        LOG_DURATION("ComputeAvgTemp"s);
        avg = ComputeAvgTemp(data);
    }

    cout << "Total mean: "s << accumulate(avg.begin(), avg.end(), 0.f) / (float)avg.size() << endl;
}