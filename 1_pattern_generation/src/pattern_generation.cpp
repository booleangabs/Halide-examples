#include "Halide.h"
#include "halide_image_io.h"
#include <iostream>

#define PI 3.14159265358f
#define IMAGE_HEIGHT 480
#define IMAGE_WIDTH 480

using std::cout;
using std::endl;
using namespace Halide;
using namespace Halide::Tools;
using namespace Halide::ConciseCasts;

inline Expr mod(const Expr& x) {
    return x - floor(x);
}

int main(int argc, char ** argv) {
    if (argc < 2) {
        cout << "Usage: bin/patter_generation <output_filename>" << endl;
    }

    const std::string output_filename = argv[1];

    Var x, y;
    Func pattern_x, pattern_y, pattern;
    Expr x_norm, y_norm, scale, color;

    scale = 5.f;
    x_norm = f32(x) / IMAGE_WIDTH;
    y_norm = f32(y) / IMAGE_HEIGHT;

    pattern_x(x, y) = sin(x_norm * 2.f * PI * scale);
    pattern_y(x, y) = cos((1 - y_norm) * 2.f * PI * scale);

    pattern(x, y) = u8(127.5f * (pattern_x(x, y) * pattern_y(x, y)));

    Buffer<uint8_t>  output = pattern.realize({IMAGE_WIDTH, IMAGE_HEIGHT});

    save_image(output, output_filename);

    return 0;
}