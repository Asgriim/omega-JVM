//
// Created by asgrim on 25.11.23.
//
#include "util/binary_io.h"

void read_big_endian(std::istream &is, char *buf, size_t size) {
    char *t_buf = new char[size];
    is.read(t_buf,size);
    for (int i = size - 1; i >= 0; i--) {
        buf[size - i - 1] = t_buf[i];
    }
    delete[] t_buf;
}