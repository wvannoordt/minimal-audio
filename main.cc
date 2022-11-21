#include <print.h>
#include <cmath>
#include "smail.h"

int main(int argc, char** argv)
{
    float duration = 1.0;
    smail::audio_buffer_t buf(duration);
    for (std::size_t i = 0; i < buf.size(); ++i)
    {
        float theta = float(i)/(buf.size()-1);
        theta = smail::sin(10*smail::pi*theta);
        buf[i]  = 0.0;
        float f0 = 160.0;
        buf[i] += theta*smail::sqr(f0*2*smail::pi*buf.time(i));
        buf[i] += (1.0-theta)*smail::sin(f0*2*smail::pi*buf.time(i));
    }
    smail::write_wav(buf, "tone.wav");
    smail::write_csv(buf, "raw.csv");
    return 0;
}