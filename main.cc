#include <print.h>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

std::ofstream& strm_write(std::ofstream& ofstr, const std::string& content)
{
    ofstr.write(content.c_str(), content.length());
    return ofstr;
}

std::ofstream& strm_write(std::ofstream& ofstr, const char* content)
{
    std::string cc(content);
    ofstr.write(cc.c_str(), cc.length());
    return ofstr;
}

template <typename data_t> 
std::ofstream& strm_write(std::ofstream& ofstr, const data_t& data)
{
    ofstr.write((const char*)(&data), sizeof(data_t));
    return ofstr;
}
template <typename data_t> 
std::ofstream& strm_write(std::ofstream& ofstr, const std::vector<data_t>& data)
{
    ofstr.write((const char*)(data.data()), sizeof(data_t)*data.size());
    return ofstr;
}

struct tone_t
{
    float frequency, duration;
    tone_t(const float& frequency_in, const float& duration_in)
    : frequency{frequency_in}, duration{duration_in}
    {}
    
    void output(const std::string& filename)
    {
        std::ofstream myfile(filename, std::ios::out | std::ios::binary);
        int sample_rate = 44100;
        int bits_per_sample = 32; //32, 24, 16
        int channels = 1;
        std::vector<int> data;
        data.resize(44100, 0);
        // int mask = 0xffffff00; // we remove the least significant few bits
        int mask = 0xffffffff; // not for 32 bits!
        for (int i = 0; i < data.size(); ++i)
        {
            const double pi = 3.14159265359;
            double tmp = sin(frequency * (2 * pi) * i / sample_rate); 
            if (tmp < 0) tmp = -tmp;
            int intVal = (int)(tmp * 2147483647.0) & mask;
            data[i] = intVal;
        }
        //output the file
        int file_size = 36 + data.size()*sizeof(int);
        strm_write(myfile, "RIFF");
        strm_write(myfile, file_size);
        strm_write(myfile, "WAVE");
        strm_write(myfile, "fmt ");
        strm_write(myfile, int(16));
        strm_write(myfile, uint16_t(1));
        strm_write(myfile, uint16_t(channels));
        strm_write(myfile, sample_rate); //sample rate
        strm_write(myfile, sample_rate * bits_per_sample * channels / 8);
        strm_write(myfile, uint16_t(bits_per_sample * channels / 8));
        strm_write(myfile, uint16_t(bits_per_sample));
        strm_write(myfile, "data");
        strm_write(myfile, data.size() * sizeof(int));
        strm_write(myfile, data);
    }
};

int main(int argc, char** argv)
{
    tone_t a440(440.0, 1.0);
    a440.output("a440.wav");
    
    tone_t a880(880.0, 1.0);
    a880.output("a880.wav");
    return 0;
}