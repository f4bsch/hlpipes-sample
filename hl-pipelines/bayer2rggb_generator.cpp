#include "Halide.h"


namespace {
	using namespace Halide;
	using namespace Halide::ConciseCasts;

	class Bayer2RGGB : public Halide::Generator<Bayer2RGGB> {
	public:
		Input <Buffer<uint16_t>> input{"bayerInput", 2};
		Output <Buffer<uint16_t>> output{"rggbOutput", 3};

		void generate() {
			Var x{"x"},y{"y"},c{"c"};

			auto input_m = BoundaryConditions::mirror_interior(input, 0, input.width(), 0 , input.height());

			output(x, y, c) = cast(output.type(), input_m(x * 2 + (c % 2), y * 2 + (c / 2)));

			output.dim(0).set_stride(4);
			output.bound(c, 0, 4);
		}

	};

}  // namespace

HALIDE_REGISTER_GENERATOR(Bayer2RGGB, bayer2rggb)
