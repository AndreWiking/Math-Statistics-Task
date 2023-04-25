
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

static const size_t Calculate_Times = 1000;
static const size_t Max_N = 1000;
static const std::string_view OutFileName("graph_data.txt");

enum Distribution{
    normal, cauchy, bernoulli, geometric
};

double CalculateProbability(size_t n, double x, size_t times, Distribution distribution, double a1, double a2) {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::normal_distribution<> Normal(a1, a2);
    std::cauchy_distribution<double> Cauchy(a1, a2);
    std::bernoulli_distribution Bern(a1);
    std::geometric_distribution<> Geom(a1);

    size_t positive = 0;
    for (size_t t = 0; t < times; ++t) {
        double sum = 0;
        for (size_t i = 0; i < n; ++i) {
            switch (distribution) {
                case normal:
                    sum += Normal(generator);
                    break;
                case cauchy:
                    sum += Cauchy(generator);
                    break;
                case bernoulli:
                    sum += Bern(generator);
                    break;
                case geometric:
                    sum += Geom(generator);
                    break;
            }
        }
        if (sum < x) ++positive;
    }
    return double(positive) / times;
}

void PrintData(std::string file_name, std::vector<std::vector<double>> &graph) {
    std::ofstream out;
    out.open(file_name);
    for (size_t i = 0; i < Max_N; ++i) {
        out << i + 1;
        for (size_t j = 0; j < graph.size(); ++j)
            out << ',' << graph[j][i];
        out << '\n';
    }
    out.close();
}

void NewGraph(std::vector<std::vector<double>> &graph, double x, Distribution distribution, double a1, double a2) {
    graph.push_back({});
    for (int i = 1; i <= Max_N; ++i)
        graph.back().push_back(CalculateProbability(i, x, Calculate_Times, distribution, a1, a2));
}

int main() {

    std::vector<std::vector<double>> graph{};

    NewGraph(graph, 0, normal, -0.1, 1);
    NewGraph(graph, 0, normal, 0.1, 1);
    NewGraph(graph, 0, normal, 0.1, 1);

    PrintData(OutFileName.data(), graph);

    return 0;
}
