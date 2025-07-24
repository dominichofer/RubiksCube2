#include "cube3x3.h"
#include "twister.h"
#include <limits>

static const AllTwister<Corners, uint16_t> c_ori_table(
	all_twists,
	&Corners::ori_index,
	[](uint16_t i) { return Corners::from_index(0, i); },
	Corners::ori_size
);

static const AllTwister<Corners, uint16_t> c_prm_table(
	all_twists,
	&Corners::prm_index,
	[](uint16_t i) { return Corners::from_index(i, 0); },
	Corners::prm_size
);

static const AllTwister<EdgesCenter, uint16_t> e_ori_table(
	all_twists,
	&EdgesCenter::ori_index,
	[](uint16_t i) { return EdgesCenter::from_index(0, 0, 0, i); },
	EdgesCenter::ori_size
);

static const AllTwister<EdgesCenter, uint8_t> e_slice_prm_table(
	all_twists,
	&EdgesCenter::slice_prm_index,
	[](uint16_t i) { return EdgesCenter::from_index(i / EdgesCenter::slice_loc_size, 0, i % EdgesCenter::slice_loc_size, 0); },
	EdgesCenter::slice_prm_size * EdgesCenter::slice_loc_size
);

static const AllTwister<EdgesCenter, uint16_t> e_non_slice_prm_table(
	all_twists,
	&EdgesCenter::non_slice_prm_index,
	[](uint32_t i) { return EdgesCenter::from_index(0, i / EdgesCenter::slice_loc_size, i % EdgesCenter::slice_loc_size, 0); },
	EdgesCenter::non_slice_prm_size * EdgesCenter::slice_loc_size
);

static const AllTwister<EdgesCenter, uint16_t> e_slice_loc_table(
	all_twists,
	&EdgesCenter::slice_loc_index,
	[](uint16_t i) { return EdgesCenter::from_index(0, 0, i, 0); },
	EdgesCenter::slice_loc_size
);

Cube3x3::Cube3x3(
	uint16_t c_ori,
	uint16_t c_prm,
	uint16_t e_ori,
	uint8_t e_slice_prm,
	uint16_t e_non_slice_prm,
	uint16_t e_slice_loc) noexcept
	: c_ori(c_ori)
	, c_prm(c_prm)
	, e_ori(e_ori)
	, e_slice_prm(e_slice_prm)
	, e_non_slice_prm(e_non_slice_prm)
	, e_slice_loc(e_slice_loc)
{
}

Cube3x3::Cube3x3() noexcept
	: Cube3x3(
		Corners{}.ori_index(),
		Corners{}.prm_index(),
		EdgesCenter{}.ori_index(),
		EdgesCenter{}.slice_prm_index(),
		EdgesCenter{}.non_slice_prm_index(),
		EdgesCenter{}.slice_loc_index())
{
}

Cube3x3 Cube3x3::impossible() noexcept
{
	return Cube3x3{
		std::numeric_limits<uint16_t>::max(),
		std::numeric_limits<uint16_t>::max(),
		std::numeric_limits<uint16_t>::max(),
		std::numeric_limits<uint8_t>::max(),
		std::numeric_limits<uint16_t>::max(),
		std::numeric_limits<uint16_t>::max()
	};
}

Cube3x3 Cube3x3::twisted(Twist t) const
{
	return Cube3x3{
		c_ori_table(c_ori, t),
		c_prm_table(c_prm, t),
		e_ori_table(e_ori, t),
		e_slice_prm_table(e_slice_prm * EdgesCenter::slice_loc_size + e_slice_loc, t),
		e_non_slice_prm_table(e_non_slice_prm * EdgesCenter::slice_loc_size + e_slice_loc, t),
		e_slice_loc_table(e_slice_loc, t)
	};
}

uint64_t Cube3x3::coset_index() const
{
	uint64_t index = c_prm / 2;
	index = index * EdgesCenter::slice_prm_size + e_slice_prm;
	index = index * EdgesCenter::non_slice_prm_size + e_non_slice_prm;
	return index;
}

uint64_t Cube3x3::coset_number() const
{
	uint32_t number = c_ori;
	number = number * EdgesCenter::ori_size + e_ori;
	number = number * EdgesCenter::slice_loc_size + e_slice_loc;
	return number;
}

bool Cube3x3::in_subset() const
{
	return c_ori == 0 and e_ori == 0 and e_slice_loc == 494;
}

bool Cube3x3::is_solved() const
{
	return in_subset() and c_prm == 0 and e_slice_prm == 0 and e_non_slice_prm == 0;
}

uint64_t Cube3x3::hash() const
{
	return ::hash(c_ori, c_prm, e_ori, e_slice_prm, e_non_slice_prm, e_slice_loc);
}
