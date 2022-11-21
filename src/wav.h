#pragma once

#include <fstream>

namespace smail
{
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

    template <typename data_t>
    void write_wav(const audio_buffer_t<data_t>& buf, const std::string& filename)
    {
        std::ofstream myfile(filename, std::ios::out | std::ios::binary);
        int sample_rate = buf.sampling_rate;
        int bits_per_sample = 32; //32, 24, 16
        int channels = 1;
        std::vector<int> data;
        data.resize(buf.size());
        // int mask = 0xffffff00; // we remove the least significant few bits
        int mask = 0xffffffff; // not for 32 bits!
        for (int i = 0; i < data.size(); ++i)
        {
            int intVal = (int)(buf[i] * 2147483647.0) & mask;
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
    
    template <typename data_t>
    void write_csv(const audio_buffer_t<data_t>& buf, const std::string& filename)
    {
        std::ofstream myfile(filename);
        for (std::size_t i = 0; i < buf.size(); ++i)
        {
            myfile << buf.time(i) << ", " << buf[i] << "\n";
        }
    }
}