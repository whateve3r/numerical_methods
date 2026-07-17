#include <iostream>
#include <iomanip>

#include <cmath>
#include <vector>
#include <random>

enum Method
{
    FAST = 0,
    ONE_PASS = 1,
    TWO_PASS = 2
};

template<typename T> T variance(std::vector<T> data, Method method)
{
    T dx{};
    T m{};

    switch(method)
    {
        case FAST:
        {
            T sum{};
            T rs{};

            for (size_t i = 0; i < data.capacity(); i++)
            {
                sum += pow(data[i], 2);
                
                m += data[i];
            }

            rs = sum / static_cast<T>(data.capacity());
            m /= static_cast<T>(data.capacity());

            dx = rs - pow(m, 2);
            break;
        }

        case ONE_PASS:
            m = data[0];
            dx = 0;

            for (size_t i = 0; i < data.capacity(); i++)
            {
                size_t count = i + 1;

                T old_m  = m;

                m = old_m + ((data[i] - old_m) / count);

                dx = dx + ((data[i] - old_m) * (data[i] - m) - dx) / count;
            }

            break;

        case TWO_PASS:
            for (size_t i = 0; i < data.capacity(); i++)
            {
                m += data[i];
            }

            m /= static_cast<T>(data.capacity());

            for (size_t j = 0; j < data.capacity(); j++)
            {
                dx += pow((data[j] - m), 2);
            }

            dx /= static_cast<T>(data.capacity());
            break;

        default:
            return 1;
    }

    return dx;
}

template<typename T> std::vector<T> generate_selection(int n, T mean, T std_deviation)
{
    std::vector<T> output_data;

    std::random_device seed;
    std::mt19937 generator(seed());
    std::normal_distribution<T> distr(mean, std_deviation);

    for (int i = 0; i < n; i++)
    {
        output_data.push_back(distr(generator));
    }

    return output_data;
}

int main()
{
    std::vector<float>  sel1  = generate_selection(10, 1.0f, 1.0f);
    std::vector<double> sel1d(sel1.begin(), sel1.end());  

    for (size_t k = 0; k < 10; k++)
    {
        std::cout << sel1[k] << " ";
    }

    std::cout << std::endl;

    float dx = variance(sel1, TWO_PASS);

    std::cout << "dx = " << dx << std::endl;

    double etalon_dx = variance(sel1d, ONE_PASS);

    std::cout << "etalon_dx = " << etalon_dx << std::endl;

    double rel_error = abs(dx - etalon_dx) / etalon_dx;

    std::cout << "Relative error: " << rel_error << std::endl;
}