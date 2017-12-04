#include "Halide.h"


namespace {
	using namespace Halide;
	using namespace Halide::ConciseCasts;

	class RGGB2Bayer : public Halide::Generator<RGGB2Bayer> {
	public:
		Input <Buffer<uint16_t>> input{"rggbInput", 3};
		Output <Buffer<uint16_t>> output{"bayerOutput", 2};

		void generate() {
			Var x{"x"}, y{"y"}, c{"c"};

			auto input_m = BoundaryConditions::mirror_interior(input, 0, input.width(), 0 , input.height());

			output(x, y) = u16_sat(input_m(x / 2, y / 2, x % 2 + 2 * (y % 2)));

			input.dim(0).set_stride(4);
			input.dim(2).set_bounds(0, 4);
		}

	};

}  // namespace

HALIDE_REGISTER_GENERATOR(RGGB2Bayer, rggb_to_bayer)
