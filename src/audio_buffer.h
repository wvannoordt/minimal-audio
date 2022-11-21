#pragma once

#include <vector>

namespace smail
{
    template <typename data_t = float>
    struct audio_buffer_t
    {
        int sampling_rate;
        std::vector<data_t> samples; //floating point, between -1, 1
        data_t duration;
        audio_buffer_t(const data_t& duration_in, const int& sampling_rate_in = 44100) : sampling_rate{sampling_rate_in}
        {
            set_duration(duration_in);
        }
        std::size_t set_duration(const data_t& duration_in)
        {
            duration = duration_in;
            std::size_t vec_size = std::size_t(sampling_rate * duration);
            samples.resize(vec_size);
            return vec_size;
        }
        auto get_sampling_rate() const {return sampling_rate;}
        std::size_t size() const {return samples.size();}
        data_t time(const std::size_t& i) const {return duration*((data_t)i)/(this->size());}
        data_t& operator [] (const std::size_t& i) {return samples[i];}
        const data_t& operator [] (const std::size_t& i) const {return samples[i];}
    };
}