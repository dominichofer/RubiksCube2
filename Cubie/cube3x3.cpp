#include "cube3x3.h"
#include "twister.h"

Cube3x3::Cube3x3(uint16_t c_prm, uint16_t c_ori, uint32_t e_prm, uint16_t e_slice_loc, uint16_t e_ori) noexcept
	: c_prm(c_prm), c_ori(c_ori), e_prm(e_prm), e_slice_loc(e_slice_loc), e_ori(e_ori)
{
}

Cube3x3::Cube3x3(const Corners& c, const EdgesCenter& e) noexcept
	: c_prm(c.prm_index())
	, c_ori(c.ori_index())
	, e_prm(e.prm_index())
	, e_slice_loc(e.slice_loc_index())
	, e_ori(e.ori_index())
{}

Cube3x3::Cube3x3() noexcept
	: Cube3x3(Corners{}, EdgesCenter{})
{}

Cube3x3 Cube3x3::twisted(Twist t) const
{
	static AllTwister<Corners, uint16_t> c_prm_table(
		all_twists,
		&Corners::prm_index,
		[](uint16_t i) { return Corners::from_index(i, 0); },
		Corners::prm_size
	);
	static AllTwister<Corners, uint16_t> c_ori_table(
		all_twists,
		&Corners::ori_index,
		[](uint16_t i) { return Corners::from_index(0, i); },
		Corners::ori_size
	);
	static AllTwister<EdgesCenter, uint32_t> e_prm_table(
		all_twists,
		&EdgesCenter::prm_index,
		[](uint32_t i) { return EdgesCenter::from_index(i, 0, 0); },
		EdgesCenter::prm_size
	);
	static AllTwister<EdgesCenter, uint16_t> e_slice_loc_table(
		all_twists,
		&EdgesCenter::slice_loc_index,
		[](uint16_t i) { return EdgesCenter::from_index(0, i, 0); },
		EdgesCenter::slice_loc_size
	);
	static AllTwister<EdgesCenter, uint16_t> e_ori_table(
		all_twists,
		&EdgesCenter::ori_index,
		[](uint16_t i) { return EdgesCenter::from_index(0, 0, i); },
		EdgesCenter::ori_size
	);
	static bool initialized = false;
	if (!initialized)
	{
		c_prm_table.fill();
		c_ori_table.fill();
		e_prm_table.fill();
		e_slice_loc_table.fill();
		e_ori_table.fill();
		initialized = true;
	}
	return Cube3x3{
		c_prm_table(c_prm, t),
		c_ori_table(c_ori, t),
		e_prm_table(e_prm, t),
		e_slice_loc_table(e_slice_loc, t),
		e_ori_table(e_ori, t)
	};
}

Cube3x3 Cube3x3::from_index(uint64_t coset_number, uint64_t coset_index)
{
	uint64_t e_slice_loc = coset_number % EdgesCenter::slice_loc_size;
	coset_number /= EdgesCenter::slice_loc_size;
	uint64_t e_ori = coset_number % EdgesCenter::ori_size;
	coset_number /= EdgesCenter::ori_size;
	uint64_t c_ori = coset_number;

	uint64_t e_prm = coset_index % EdgesCenter::prm_size;
	coset_index /= EdgesCenter::prm_size;
	uint64_t c_prm = coset_index * 2;

}

uint64_t Cube3x3::coset_number() const
{
	uint64_t number = c_ori;
	number = number * EdgesCenter::ori_size + e_ori;
	number = number * EdgesCenter::slice_loc_size + e_slice_loc;
	return number;
}

uint64_t Cube3x3::coset_index() const
{
	return c_prm / 2 * EdgesCenter::prm_size + e_prm;
}

std::string to_string(const Cube3x3& c)
{
	return "c_prm: " + std::to_string(c.c_prm) +
		", c_ori: " + std::to_string(c.c_ori) +
		", e_prm: " + std::to_string(c.e_prm) +
		", e_slice_loc: " + std::to_string(c.e_slice_loc) +
		", e_ori: " + std::to_string(c.e_ori);
}
